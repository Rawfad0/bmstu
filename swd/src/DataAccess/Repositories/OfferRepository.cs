using Dapper;
using Domain.Models;
using Domain.OutputPorts;
using Domain;
using Npgsql;

namespace DataAccess.Repositories;

public class OfferRepository : IOfferRepository
{
    private readonly NpgsqlConnection _connection;

    public OfferRepository(DapperContext context)
    {
        _connection = context.Connection;
    }

    public Offer Create(Offer offer)
    {
        try
        {
            var sql = @"
                INSERT INTO offers (id, product_id, store_id, price, quantity, delivery_time)
                VALUES (@Id, @ProductId, @StoreId, @Price, @Quantity, @DeliveryTime)";
            _connection.Execute(sql, offer);
            return offer;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при добавлении предложения", ex);
        }
    }

    public Offer? GetById(OfferId offerId)
    {
        try
        {
            var sql = @"
                SELECT id, 
                    product_id AS ProductId, 
                    store_id AS StoreId, 
                    price AS Price, 
                    quantity AS Quantity, 
                    delivery_time AS DeliveryTime
                FROM offers 
                WHERE id=@Id";
            return _connection.QuerySingleOrDefault<Offer>(sql, new { Id = offerId.Id });
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении предложения", ex);
        }
    }

    public List<Offer> GetByProductId(ProductId productId)
    {
        try
        {
            var sql = @"
                SELECT id, 
                    product_id AS ProductId, 
                    store_id AS StoreId, 
                    price AS Price, 
                    quantity AS Quantity, 
                    delivery_time AS DeliveryTime
                FROM offers 
                WHERE product_id=@ProductId";
            return _connection.Query<Offer>(sql, new { ProductId = productId.Id }).ToList();
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении предложений по продукту", ex);
        }
    }

    public List<Offer> GetByStoreId(StoreId storeId)
    {
        try
        {
            var sql = @"
                SELECT id, 
                    product_id AS ProductId, 
                    store_id AS StoreId, 
                    price AS Price, 
                    quantity AS Quantity, 
                    delivery_time AS DeliveryTime 
                FROM offers 
                WHERE store_id=@StoreId";
            return _connection.Query<Offer>(sql, new { StoreId = storeId.Id }).ToList();
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении предложений по магазину", ex);
        }
    }

    public List<OfferDetailsDto> GetOfferDetailsByProductId(ProductId productId)
    {
        try
        {
            var sql = @"
                SELECT o.id AS OfferId,
                    o.price AS Price, 
                    o.quantity AS Quantity, 
                    o.delivery_time AS DeliveryTime, 
                    o.product_id AS ProductId,
                    p.name AS ProductName,
                    o.store_id AS StoreId,
                    s.name AS StoreName,
                    s.rating_count AS RatingCount,
                    s.avg_rating AS AvgRating
                FROM offers o
                JOIN products p ON o.product_id = p.id
                JOIN stores s ON o.store_id = s.id
                WHERE o.product_id = @ProductId;
            ";

            return _connection.Query<OfferDetailsDto>(sql, new { ProductId = productId.Id }).ToList();
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении предложений по продукту", ex);
        }
    }

    public Offer Update(Offer offer)
    {
        try
        {
            var sql = @"
                UPDATE offers
                SET price=@Price, 
                    quantity=@Quantity, 
                    delivery_time=@DeliveryTime
                WHERE id=@Id";
            var rows = _connection.Execute(sql, offer);
            if (rows == 0)
                throw new RepositoryException($"Предложение с id {offer.Id} не найдено");
            return offer;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при обновлении предложения", ex);
        }
    }

    public Offer? DeleteById(OfferId offerId)
    {
        var offer = GetById(offerId);
        if (offer == null) return null;
        try
        {
            var sql = "DELETE FROM offers WHERE id=@Id";
            _connection.Execute(sql, new { Id = offerId.Id });
            return offer;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при удалении предложения", ex);
        }
    }
}
