using Dapper;
using Domain.Models;
using Domain.OutputPorts;
using Domain;
using Npgsql;

namespace DataAccess.Repositories;

public class ProductRepository : IProductRepository
{
    private readonly NpgsqlConnection _connection;

    public ProductRepository(DapperContext context)
    {
        _connection = context.Connection;
    }

    public Product Create(Product product)
    {
        try
        {
            var sql = @"
                INSERT INTO products (id, name, category, description, rating_count, avg_rating)
                VALUES (@Id, @Name, @Category, @Description, @RatingCount, @AvgRating)";
            _connection.Execute(sql, product);
            return product;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при добавлении продукта", ex);
        }
    }

    public Product? GetById(ProductId productId)
    {
        try
        {
            var sql = @"
                SELECT id, 
                    name AS Name, 
                    category AS Category, 
                    description AS Description, 
                    rating_count AS RatingCount, 
                    avg_rating AS AvgRating
                FROM products 
                WHERE id=@Id";
            return _connection.QuerySingleOrDefault<Product>(sql, new { Id = productId.Id });
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении продукта", ex);
        }
    }

    public List<Product> GetByName(string name)
    {
        if (string.IsNullOrWhiteSpace(name))
            throw new ValidationException("Имя продукта для поиска не может быть пустым");

        try
        {
            var sql = @"
                SELECT id, 
                    name AS Name, 
                    category AS Category, 
                    description AS Description, 
                    rating_count AS RatingCount, 
                    avg_rating AS AvgRating
                FROM products 
                WHERE name ILIKE @Name";
            return _connection.Query<Product>(sql, new { Name = $"%{name}%" }).ToList();
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при поиске продукта по имени", ex);
        }
    }

    public Product Update(Product product)
    {
        try
        {
            var sql = @"
                UPDATE products
                SET name=@Name, 
                    category=@Category, 
                    description=@Description, 
                    rating_count=@RatingCount, 
                    avg_rating=@AvgRating
                WHERE id=@Id";
            var rows = _connection.Execute(sql, product);
            if (rows == 0)
                throw new RepositoryException($"Продукт с id {product.Id} не найден");
            return product;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при обновлении продукта", ex);
        }
    }
}
