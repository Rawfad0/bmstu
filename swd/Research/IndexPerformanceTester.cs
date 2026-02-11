using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Threading.Tasks;
using Dapper;
using Npgsql;
using Microsoft.Extensions.Logging;

namespace Research;

public class IndexPerformanceTester
{
    private readonly string _connectionString;
    private readonly ILogger _logger;

    public IndexPerformanceTester(string connectionString, ILogger logger)
    {
        _connectionString = connectionString;
        _logger = logger;
    }

    public void Run()
    {
        var outputFile = "index_performance_results.csv";
        var rowCounts = new[] { 10000, 30000, 50000, 75000, 100000, 150000, 200000, 250000, 300000, 400000 };
        var results = new List<(int Rows, double WithIndex, double WithoutIndex)>();

        _logger.LogInformation("Запуск исследования производительности индексов...");
        _logger.LogInformation("Результаты будут сохранены в {File}", outputFile);

        var sw = Stopwatch.StartNew();
        foreach (var count in rowCounts)
        {
            try
            {
                _logger.LogInformation("▶ Тестирование с {Count} строк...", count);

                PrepareData(count);

                _logger.LogDebug("Удаляем индексы...");
                DropIndexes();
                var withoutIndex = MeasureQueryTime(false);
                _logger.LogInformation("⏱ Без индекса: {Time:F3} мс", withoutIndex);

                _logger.LogDebug("Создаём индексы...");
                CreateIndexes();
                var withIndex = MeasureQueryTime(true);
                _logger.LogInformation("⏱ С индексом: {Time:F3} мс", withIndex);

                results.Add((count, withIndex, withoutIndex));

                _logger.LogInformation("✔ {Count} строк | WithIndex: {WithIndex:F3} ms | WithoutIndex: {WithoutIndex:F3} ms",
                    count, withIndex, withoutIndex);
                
                Console.WriteLine();
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Ошибка при тестировании с {Count} строками", count);
            }
        }
        sw.Stop();
        Console.WriteLine($"TOTAL: {sw.Elapsed.TotalMilliseconds}");

        SaveResults(outputFile, results);
        _logger.LogInformation("✅ Исследование завершено. Результаты сохранены в {Path}", outputFile);
    }

    private void PrepareData(int rows)
    {
        using var conn = new NpgsqlConnection(_connectionString);
        conn.Open();

        conn.Execute(@"
            TRUNCATE TABLE offers RESTART IDENTITY CASCADE;
            TRUNCATE TABLE products RESTART IDENTITY CASCADE;
            TRUNCATE TABLE stores RESTART IDENTITY CASCADE;
            TRUNCATE TABLE sellers RESTART IDENTITY CASCADE;
        ");

        conn.Execute(@"
            INSERT INTO sellers (id, first_name, last_name, phone, email, birth_date)
            SELECT gen_random_uuid(),
                'SellerFirst' || i,
                'SellerLast' || i,
                '+7-999-' || lpad(i::text, 4, '0'),
                'seller' || i || '@example.com',
                (CURRENT_DATE - (i % 1000))::date
            FROM generate_series(1, @Rows) AS s(i);
        ", new { Rows = rows });

        conn.Execute(@"
            INSERT INTO stores (id, owner_seller_id, name, ogrn, rating_count, avg_rating)
            SELECT gen_random_uuid(),
                sel.id,
                'Store ' || i,
                'OGRN-' || i,
                (random() * 100)::int,
                (random() * 5)
            FROM (
                SELECT i, row_number() OVER () AS rn
                FROM generate_series(1, @Rows) AS s(i)
            ) g
            JOIN (
                SELECT id, row_number() OVER () AS rn
                FROM sellers
                LIMIT @Rows
            ) sel ON sel.rn = g.rn;
        ", new { Rows = rows });

        conn.Execute(@"
            INSERT INTO products (id, name, category, description, rating_count, avg_rating)
            SELECT gen_random_uuid(),
                'Product ' || i,
                'Category ' || ((i % 5) + 1),
                'Description ' || i,
                (random() * 100)::int,
                (random() * 5)
            FROM generate_series(1, @Rows) AS s(i);
        ", new { Rows = rows });

        conn.Execute(@"
            WITH prod AS (SELECT array_agg(id) AS ids FROM products),
                str AS (SELECT array_agg(id) AS ids FROM stores)
            INSERT INTO offers (id, product_id, store_id, price, quantity, delivery_time)
            SELECT gen_random_uuid(),
                prod.ids[1 + floor(random() * array_length(prod.ids,1))::int],
                str.ids[1 + floor(random() * array_length(str.ids,1))::int],
                (random() * 1000)::int,
                (random() * 100)::int,
                (random() * 10)::int
            FROM generate_series(1, @Rows), prod, str;
        ", new { Rows = rows });
    }

    private void CreateIndexes()
    {
        using var conn = new NpgsqlConnection(_connectionString);
        conn.Open();

        conn.Execute("CREATE INDEX IF NOT EXISTS idx_offers_product_id ON offers (product_id);");
        conn.Execute("CREATE INDEX IF NOT EXISTS idx_offers_store_id ON offers (store_id);");

        _logger.LogDebug("Созданы индексы idx_offers_product_id и idx_offers_store_id");
    }

    private void DropIndexes()
    {
        using var conn = new NpgsqlConnection(_connectionString);
        conn.Open();

        conn.Execute("DROP INDEX IF EXISTS idx_offers_product_id;");
        conn.Execute("DROP INDEX IF EXISTS idx_offers_store_id;");

        _logger.LogDebug("Удалены индексы idx_offers_product_id и idx_offers_store_id");
    }

    private double MeasureQueryTime(bool useIndex)
    {
        const int repeats = 30;
        var times = new List<double>(repeats);

        Guid productId;
        using (var conn = new NpgsqlConnection(_connectionString))
        {
            conn.Open();
            productId = conn.ExecuteScalar<Guid>("SELECT product_id FROM offers LIMIT 1;");
        }

        var sql = @"
            SELECT o.id AS OfferId,
                o.price AS Price, 
                o.quantity AS Quantity, 
                o.delivery_time AS DeliveryTime, 
                o.product_id AS ProductId,
                p.name AS ProductName,
                o.store_id AS StoreId,
                s.name AS StoreName
            FROM offers o
            JOIN products p ON o.product_id = p.id
            JOIN stores s ON o.store_id = s.id
            WHERE o.product_id = @ProductId;";

        for (int i = 0; i < repeats; i++)
        {
            using var conn = new NpgsqlConnection(_connectionString);
            conn.Open();

            conn.Execute("DISCARD ALL;");
            conn.Execute("ANALYZE offers;");

            if (useIndex)
            {
                conn.Execute("SET enable_seqscan = off; SET enable_indexscan = on; SET enable_bitmapscan = off;");
            }
            else
            {
                conn.Execute("SET enable_seqscan = on; SET enable_indexscan = off; SET enable_bitmapscan = off;");
            }

            var sw = Stopwatch.StartNew();
            conn.Query(sql, new { ProductId = productId });
            sw.Stop();

            times.Add(sw.Elapsed.TotalMilliseconds);
            Console.Write($"{sw.Elapsed.TotalMilliseconds}, ");

            Thread.Sleep(100);
        }

        Console.WriteLine();

        // times.Sort();
        // double median;
        // int mid = times.Count / 2;
        // if (times.Count % 2 == 0)
        //     median = (times[mid - 1] + times[mid]) / 2.0;
        // else
        //     median = times[mid];

        // return median;

        // Отбрасываем выбросы (% с каждой стороны)
        times.Sort();
        int skip = repeats / 4;
        var filtered = times.Skip(skip).Take(repeats - 2 * skip);

        return filtered.Average();
    }

    private static void SaveResults(string path, IEnumerable<(int Rows, double WithIndex, double WithoutIndex)> results)
    {
        using var writer = new StreamWriter(path);
        writer.WriteLine("Rows,WithIndex(ms),WithoutIndex(ms)");
        foreach (var r in results)
        {
            writer.WriteLine($"{r.Rows},{r.WithIndex.ToString(CultureInfo.InvariantCulture)},{r.WithoutIndex.ToString(CultureInfo.InvariantCulture)}");
        }
    }
}
