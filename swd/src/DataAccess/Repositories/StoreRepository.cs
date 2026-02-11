using Dapper;
using Domain.Models;
using Domain.OutputPorts;
using Domain;
using Npgsql;

namespace DataAccess.Repositories;

public class StoreRepository : IStoreRepository
{
    private readonly NpgsqlConnection _connection;

    public StoreRepository(DapperContext context)
    {
        _connection = context.Connection;
    }

    public Store Create(Store store)
    {
        try
        {
            var sql = @"
                INSERT INTO stores (id, owner_seller_id, name, ogrn, rating_count, avg_rating)
                VALUES (@Id, @OwnerSellerId, @Name, @Ogrn, @RatingCount, @AvgRating)";
            _connection.Execute(sql, store);
            return store;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при добавлении магазина", ex);
        }
    }

    public Store? GetById(StoreId storeId)
    {
        try
        {
            var sql = @"
                SELECT id, 
                    owner_seller_id AS OwnerSellerId, 
                    name AS Name, 
                    ogrn AS Ogrn, 
                    rating_count AS RatingCount, 
                    avg_rating AS AvgRating
                FROM stores 
                WHERE id=@Id";
            return _connection.QuerySingleOrDefault<Store>(sql, new { Id = storeId.Id });
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении магазина", ex);
        }
    }

    public List<Store> GetBySellerId(SellerId sellerId)
    {
        try
        {
            var sql = @"
                SELECT id,
                    owner_seller_id AS OwnerSellerId, 
                    name AS Name, 
                    ogrn AS Ogrn, 
                    rating_count AS RatingCount, 
                    avg_rating AS AvgRating
                FROM stores
                WHERE owner_seller_id = @SellerId";
            return _connection.Query<Store>(sql, new { SellerId = sellerId.Id }).ToList();
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении списка магазинов продавца", ex);
        }
    }

    public Store Update(Store store)
    {
        try
        {
            var sql = @"
                UPDATE stores
                SET name=@Name, 
                    ogrn=@Ogrn, 
                    rating_count=@RatingCount, 
                    avg_rating=@AvgRating
                WHERE id=@Id";
            var rows = _connection.Execute(sql, store);
            if (rows == 0)
                throw new RepositoryException($"Магазин с id {store.Id} не найден");
            return store;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при обновлении магазина", ex);
        }
    }
}
