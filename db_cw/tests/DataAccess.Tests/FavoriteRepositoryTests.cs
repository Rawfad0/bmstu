using Xunit;
using Domain.Models;
using DataAccess.Repositories;
using Domain;
using System;
using Dapper;

public class FavoriteRepositoryTests : IDisposable
{
    private readonly DapperContext _context;
    private readonly FavoriteRepository _favoriteRepository;
    private readonly CustomerRepository _customerRepository;
    private readonly ProductRepository _productRepository;

    public FavoriteRepositoryTests()
    {
        _context = new TestDapperContext();
        _favoriteRepository = new FavoriteRepository(_context);
        _customerRepository = new CustomerRepository(_context);
        _productRepository = new ProductRepository(_context);

        _context.Connection.Execute("DELETE FROM favorites;");
        _context.Connection.Execute("DELETE FROM products;");
        _context.Connection.Execute("DELETE FROM customers;");
    }

    [Fact]
    public void GetById_ReturnsFavorite()
    {
        var customer = Customer.Create(
            Guid.NewGuid(),
            "John",
            "Doe",
            "1234567890",
            "john@example.com",
            new DateTime(1990,1,1), 
            DateTime.UtcNow,
            0
        );
        _customerRepository.Create(customer);
        var product = Product.Create(
            Guid.NewGuid(), 
            "Test Product", 
            "Category", 
            "Description"
        );
        _productRepository.Create(product);
        var id = Guid.NewGuid();
        var favoriteId = new FavoriteId(id);
        var favorite = Favorite.Create(id, customer.Id, product.Id);
        _favoriteRepository.Create(favorite);

        var result = _favoriteRepository.GetById(favoriteId);

        Assert.NotNull(result);
        Assert.Equal(favorite.Id, result.Id);
    }

    [Fact]
    public void GetByCustomerId_ReturnsOnlyThatCustomersFavorites()
    {
        var customer = Customer.Create(
            Guid.NewGuid(),
            "John",
            "Doe",
            "1234567890",
            "john@example.com",
            new DateTime(1990,1,1), 
            DateTime.UtcNow,
            0
        );
        _customerRepository.Create(customer);
        var product = Product.Create(
            Guid.NewGuid(), 
            "Test Product", 
            "Category", 
            "Description"
        );
        _productRepository.Create(product);
        var favorite = Favorite.Create(Guid.NewGuid(), customer.Id, product.Id);
        _favoriteRepository.Create(favorite);

        var result = _favoriteRepository.GetByCustomerId(new CustomerId(customer.Id));

        Assert.Single(result);
        Assert.Equal(customer.Id, result.First().CustomerId);
        Assert.Equal(product.Id, result.First().ProductId);
    }

    [Fact]
    public void DeleteById_ReturnsDeleteedFavorite()
    {
        var customer = Customer.Create(
            Guid.NewGuid(),
            "John",
            "Doe",
            "1234567890",
            "john@example.com",
            new DateTime(1990,1,1), 
            DateTime.UtcNow,
            0
        );
        _customerRepository.Create(customer);
        var product = Product.Create(
            Guid.NewGuid(), 
            "Test Product", 
            "Category", 
            "Description"
        );
        _productRepository.Create(product);
        var id = Guid.NewGuid();
        var favoriteId = new FavoriteId(id);
        var favorite = Favorite.Create(id, customer.Id, product.Id);
        _favoriteRepository.Create(favorite);

        var result = _favoriteRepository.DeleteById(favoriteId);

        var fromDb = _favoriteRepository.GetById(favoriteId);
        Assert.Null(fromDb);
    }

    public void Dispose()
    {
        _context.Connection.Execute("DELETE FROM favorites;");
        _context.Connection.Execute("DELETE FROM products;");
        _context.Connection.Execute("DELETE FROM customers;");
    }
}
