using Dapper;
using Domain.Models;
using Domain.OutputPorts;
using Domain;
using Npgsql;

namespace DataAccess.Repositories;

public class FavoriteRepository : IFavoriteRepository
{
    private readonly NpgsqlConnection _connection;

    public FavoriteRepository(DapperContext context)
    {
        _connection = context.Connection;
    }

    public Favorite Create(Favorite favorite)
    {
        try
        {
            var sql = @"
                INSERT INTO favorites (id, customer_id, product_id)
                VALUES (@Id, @CustomerId, @ProductId)";
            _connection.Execute(sql, favorite);
            return favorite;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при добавлении избранного", ex);
        }
    }

    public Favorite? GetById(FavoriteId favoriteId)
    {
        try
        {
            var sql = @"
                SELECT id,
                    customer_id AS CustomerId,
                    product_id AS ProductId 
                FROM favorites 
                WHERE id=@Id";
            return _connection.QuerySingleOrDefault<Favorite>(sql, new { Id = favoriteId.Id });
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении избранного", ex);
        }
    }

    public List<Favorite> GetByCustomerId(CustomerId customerId)
    {
        try
        {
            var sql = @"
                SELECT id,
                    customer_id AS CustomerId,
                    product_id AS ProductId
                FROM favorites
                WHERE customer_id = @CustomerId";
            return _connection.Query<Favorite>(sql, new { CustomerId = customerId.Id }).ToList();
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении избранных клиента", ex);
        }
    }

    public List<FavoriteDetailsDto> GetFavoriteDetailsByCustomerId(CustomerId customerId)
    {
        try
        {
            var sql = @"
                SELECT f.id as FavoriteId,
                    f.customer_id as CustomerId,
                    p.id as ProductId,
                    p.name as ProductName,
                    p.description as ProductDescription
                FROM favorites f
                JOIN products p ON f.product_id = p.id
                WHERE f.customer_id = @CustomerId";

            return _connection.Query<FavoriteDetailsDto>(sql, new { CustomerId = customerId.Id }).ToList();
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении деталей изранного клиента", ex);
        }
    }
    
    public Favorite? DeleteById(FavoriteId favoriteId)
    {
        var favorite = GetById(favoriteId);
        if (favorite == null) return null;
        try
        {
            var sql = "DELETE FROM favorites WHERE id=@Id";
            _connection.Execute(sql, new { Id = favoriteId.Id });
            return favorite;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при удалении избранного", ex);
        }
    }
}
