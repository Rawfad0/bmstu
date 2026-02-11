using Xunit;
using Domain.Models;
using DataAccess.Repositories;
using Domain;
using System;
using Dapper;

public class CustomerRepositoryTests : IDisposable
{
    private readonly DapperContext _context;
    private readonly CustomerRepository _repository;

    public CustomerRepositoryTests()
    {
        _context = new TestDapperContext();
        _repository = new CustomerRepository(_context);

        _context.Connection.Execute("DELETE FROM favorites;");
        _context.Connection.Execute("DELETE FROM products;");
        _context.Connection.Execute("DELETE FROM customers;");
    }

    [Fact]
    public void Create_ShouldInsertCustomer_WhenValid()
    {
        var id = Guid.NewGuid();
        var customerId = new CustomerId(id);
        var customer = Customer.Create(
            id, 
            "Ivanov", 
            "Ivan", 
            "+79991112233", 
            "ivanov@example.com", 
            new DateTime(1990,1,1), 
            DateTime.UtcNow, 
            0
        );

        var result = _repository.Create(customer);

        Assert.NotNull(result);
        var fromDb = _repository.GetById(customerId);
        Assert.NotNull(fromDb);
        Assert.Equal(customer.Id, fromDb.Id);
    }

    [Fact]
    public void Update_ShouldInsertCustomer_WhenValid()
    {
        var id = Guid.NewGuid();
        var customerId = new CustomerId(id);
        var customer = Customer.Create(
            id, 
            "Ivanov", 
            "Ivan", 
            "+79991112233", 
            "ivanov@example.com", 
            new DateTime(1990,1,1), 
            DateTime.UtcNow, 
            0
        );
        var created = _repository.Create(customer);

        customer.LastName = "Petrov";
        var result = _repository.Update(customer);

        Assert.NotNull(result);
        var fromDb = _repository.GetById(customerId);
        Assert.NotNull(fromDb);
        Assert.Equal("Petrov", fromDb.LastName);
        Assert.Equal(result.LastName, fromDb.LastName);
    }

    public void Dispose()
    {
        _context.Connection.Execute("DELETE FROM favorites;");
        _context.Connection.Execute("DELETE FROM products;");
        _context.Connection.Execute("DELETE FROM customers;");
    }
}
