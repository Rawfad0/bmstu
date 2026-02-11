using Dapper;
using Domain.Models;
using Domain.OutputPorts;
using Domain;
using Npgsql;

namespace DataAccess.Repositories;

public class SellerRepository : ISellerRepository
{
    private readonly NpgsqlConnection _connection;

    public SellerRepository(DapperContext context)
    {
        _connection = context.Connection;
    }

    public Seller Create(Seller seller)
    {
        try
        {
            var sql = @"
                INSERT INTO sellers (id, first_name, last_name, phone, email, birth_date)
                VALUES (@Id, @FirstName, @LastName, @Phone, @Email, @BirthDate)";
            _connection.Execute(sql, seller);
            return seller;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при добавлении продавца", ex);
        }
    }

    public Seller? GetById(SellerId sellerId)
    {
        try
        {
            var sql = @"
                SELECT id, 
                    first_name AS FirstName, 
                    last_name AS LastName, 
                    phone AS Phone, 
                    email AS Email,
                    birth_date AS BirthDate
                FROM sellers 
                WHERE id=@Id";
            return _connection.QuerySingleOrDefault<Seller>(sql, new { Id = sellerId.Id });
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении продавца", ex);
        }
    }

    public Seller? GetByEmail(string email)
    {
        try
        {
            var sql = @"
                SELECT id,  
                    first_name AS FirstName, 
                    last_name AS LastName, 
                    phone AS Phone, 
                    email AS Email,
                    birth_date AS BirthDate
                FROM sellers 
                WHERE email=@email";
            return _connection.QuerySingleOrDefault<Seller>(sql, new { email });
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении продавца", ex);
        }
    }

    public Seller Update(Seller seller)
    {
        try
        {
            var sql = @"
                UPDATE sellers
                SET first_name=@FirstName, 
                    last_name=@LastName, 
                    phone=@Phone, 
                    email=@Email, 
                    birth_date=@BirthDate
                WHERE id=@Id";
            var rows = _connection.Execute(sql, seller);
            if (rows == 0)
                throw new RepositoryException($"Продавец с id {seller.Id} не найден");
            return seller;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при обновлении продавца", ex);
        }
    }
}
