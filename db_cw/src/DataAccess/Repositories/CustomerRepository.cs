using Dapper;
using Domain.Models;
using Domain.OutputPorts;
using Domain;
using Npgsql;

namespace DataAccess.Repositories;

public class CustomerRepository : ICustomerRepository
{
    private readonly NpgsqlConnection _connection;

    public CustomerRepository(DapperContext context)
    {
        _connection = context.Connection;
    }

    public Customer Create(Customer customer)
    {
        try
        {
            var sql = @"
                INSERT INTO customers (id, first_name, last_name, phone, email, birth_date, registered_at, points)
                VALUES (@Id, @FirstName, @LastName, @Phone, @Email, @BirthDate, @RegisteredAt, @Points)";
            _connection.Execute(sql, customer);
            return customer;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при добавлении клиента в базу", ex);
        }
    }

    public Customer? GetById(CustomerId customerId)
    {
        try
        {
            var sql = @"
                SELECT id,
                    first_name AS FirstName,
                    last_name AS LastName,
                    phone AS Phone,
                    email AS Email,
                    birth_date AS BirthDate,
                    registered_at AS RegisteredAt,
                    points AS Points
                FROM customers 
                WHERE id = @Id";
            return _connection.QuerySingleOrDefault<Customer>(sql, new { Id = customerId.Id });
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении клиента из базы", ex);
        }
    }

    public Customer? GetByEmail(string email)
    {
        try
        {
            var sql = @"
                SELECT id,
                    first_name AS FirstName,
                    last_name AS LastName,
                    phone AS Phone,
                    email AS Email,
                    birth_date AS BirthDate,
                    registered_at AS RegisteredAt,
                    points AS Points
                FROM customers 
                WHERE email = @email";
            return _connection.QuerySingleOrDefault<Customer>(sql, new { email });
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при получении клиента из базы", ex);
        }
    }

    public Customer Update(Customer customer)
    {
        try
        {
            var sql = @"
                UPDATE customers
                SET first_name=@FirstName, 
                    last_name=@LastName, 
                    phone=@Phone, 
                    email=@Email, 
                    birth_date=@BirthDate, 
                    points=@Points
                WHERE id=@Id";
            var rows = _connection.Execute(sql, customer);
            if (rows == 0)
                throw new RepositoryException($"Клиент с id {customer.Id} не найден для обновления");

            return customer;
        }
        catch (NpgsqlException ex)
        {
            throw new RepositoryException("Ошибка при обновлении клиента в базе", ex);
        }
    }
}
