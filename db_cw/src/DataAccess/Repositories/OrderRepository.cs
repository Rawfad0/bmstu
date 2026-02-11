using Dapper;
using Domain.Models;
using Domain.OutputPorts;
using Domain;
using Npgsql;

namespace DataAccess.Repositories;

public class OrderRepository : IOrderRepository
{
    private readonly NpgsqlConnection _connection;

    public OrderRepository(DapperContext context)
    {
        _connection = context.Connection;
    }

    public Order Create(Order order)
    {
        try
        {
            var sql = @"
                INSERT INTO orders (id, customer_id, offer_id, quantity, status)
                VALUES (@Id, @CustomerId, @OfferId, @Quantity, @Status)";
            _connection.Execute(sql, order);
            return order;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при добавлении заказа", ex);
        }
    }

    public Order? GetById(OrderId orderId)
    {
        try
        {
            var sql = @"
                SELECT id, 
                    customer_id AS CustomerId, 
                    offer_id AS OfferId, 
                    quantity AS Quantity, 
                    status AS Status
                FROM orders 
                WHERE id=@Id";
            return _connection.QuerySingleOrDefault<Order>(sql, new { Id = orderId.Id });
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении заказа", ex);
        }
    }

    public List<Order> GetByCustomerId(CustomerId customerId)
    {
        try
        {
            var sql = @"
                SELECT id, 
                    customer_id AS CustomerId, 
                    offer_id AS OfferId, 
                    quantity AS Quantity, 
                    status AS Status
                FROM orders 
                WHERE customer_id=@Id";
            return _connection.Query<Order>(sql, new { Id = customerId.Id }).ToList();
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении заказа", ex);
        }
    }

    public Order Update(Order order)
    {
        try
        {
            var sql = @"
                UPDATE orders
                SET quantity=@Quantity, 
                    status=@Status
                WHERE id=@Id";
            var rows = _connection.Execute(sql, order);
            if (rows == 0)
                throw new RepositoryException($"Заказ с id {order.Id} не найден");
            return order;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при обновлении заказа", ex);
        }
    }

    public List<OrderDetailsDto> GetOrderDetailsByCustomerId(CustomerId customerId)
    {
        try
        {
            var sql = @"
                SELECT 
                    o.id AS OrderId,
                    o.status AS Status,
                    o.quantity AS Quantity,

                    p.id AS ProductId,
                    p.name AS ProductName,
                    p.description AS ProductDescription,

                    ofr.id AS OfferId,
                    ofr.price AS OfferPrice,
                    ofr.quantity AS OfferQuantity,

                    s.id AS StoreId,
                    s.name AS StoreName,

                    r.id AS ReviewId,
                    r.rating AS Rating,
                    r.review_text AS ReviewText

                FROM orders o
                JOIN offers ofr ON o.offer_id = ofr.id
                JOIN products p ON ofr.product_id = p.id
                JOIN stores s ON ofr.store_id = s.id
                LEFT JOIN reviews r ON o.id = r.order_id
                WHERE o.customer_id = @CustomerId;
            ";

            var result = _connection.Query<OrderDetailsDto>(sql, new { CustomerId = customerId.Id }).ToList();
            return result;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении деталей заказа", ex);
        }
    }
}
