using Xunit;
using Domain.Models;
using DataAccess.Repositories;
using Domain;
using System;
using System.Linq;
using Dapper;

public class ProductRepositoryTests : IDisposable
{
    private readonly DapperContext _context;
    private readonly ProductRepository _productRepository;

    public ProductRepositoryTests()
    {
        _context = new TestDapperContext();
        _productRepository = new ProductRepository(_context);

        _context.Connection.Execute("DELETE FROM products;");
    }

    [Fact]
    public void GetByName_ReturnsMatchingProducts()
    {
        var product1 = Product.Create(Guid.NewGuid(), "Apple", "Fruit", "Red Apple");
        var product2 = Product.Create(Guid.NewGuid(), "Apple Pie", "Dessert", "Delicious Pie");
        var product3 = Product.Create(Guid.NewGuid(), "Orange", "Fruit", "Juicy Orange");
        _productRepository.Create(product1);
        _productRepository.Create(product2);
        _productRepository.Create(product3);

        var results = _productRepository.GetByName("Apple");

        Assert.Equal(2, results.Count);
        Assert.Contains(results, p => p.Id == product1.Id);
        Assert.Contains(results, p => p.Id == product2.Id);
    }


    public void Dispose()
    {
        _context.Connection.Execute("DELETE FROM products;");
    }
}

