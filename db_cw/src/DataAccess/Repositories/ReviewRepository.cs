using Dapper;
using Domain.Models;
using Domain.OutputPorts;
using Domain;
using Npgsql;

namespace DataAccess.Repositories;

public class ReviewRepository : IReviewRepository
{
    private readonly NpgsqlConnection _connection;

    public ReviewRepository(DapperContext context)
    {
        _connection = context.Connection;
    }

    public Review Create(Review review)
    {
        try
        {
            var sql = @"
                INSERT INTO reviews (id, customer_id, order_id, rating, review_text)
                VALUES (@Id, @CustomerId, @OrderId, @Rating, @ReviewText)";
            _connection.Execute(sql, review);
            return review;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при добавлении отзыва", ex);
        }
    }

    public Review? GetById(ReviewId reviewId)
    {
        try
        {
            var sql = @"
                SELECT id,
                    customer_id AS CustomerId,
                    order_id AS OrderId,
                    rating AS Rating,
                    review_text AS ReviewText
                FROM reviews
                WHERE id = @Id";
            return _connection.QuerySingleOrDefault<Review>(sql, new { Id = reviewId.Id });
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении отзыва", ex);
        }
    }

    public List<Review> GetByCustomerId(CustomerId customerId)
    {
        try
        {
            var sql = @"
                SELECT id,
                    customer_id AS CustomerId,
                    order_id AS OrderId,
                    rating AS Rating,
                    review_text AS ReviewText
                FROM reviews
                WHERE customer_id = @CustomerId";
            return _connection.Query<Review>(sql, new { CustomerId = customerId.Id }).ToList();
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении отзывов клиента", ex);
        }
    }

    public Review? GetByOrderId(OrderId orderId)
    {
        try
        {
            var sql = @"
                SELECT id,
                    customer_id AS CustomerId,
                    order_id AS OrderId,
                    rating AS Rating,
                    review_text AS ReviewText
                FROM reviews
                WHERE order_id = @OrderId";
            return _connection.QuerySingleOrDefault<Review>(sql, new { OrderId = orderId.Id });
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении отзывов заказа", ex);
        }
    }

    public Review? DeleteById(ReviewId reviewId)
    {
        var review = GetById(reviewId);
        if (review == null) return null;
        try
        {
            var sql = "DELETE FROM reviews WHERE id=@Id";
            _connection.Execute(sql, new { Id = reviewId.Id });
            return review;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при удалении отзыва", ex);
        }
    }
}
