using Xunit;
using Moq;
using Domain.InputPorts;
using Domain.OutputPorts;
using Domain.Models;
using Domain;

namespace Domain.Tests;

public class SellerServiceTests
{
    private readonly Mock<ISellerRepository> _sellerRepoMock;
    private readonly SellerService _service;

    public SellerServiceTests()
    {
        _sellerRepoMock = new Mock<ISellerRepository>();
        _service = new SellerService(_sellerRepoMock.Object);
    }

    [Fact]
    public void Create_ShouldCallRepository()
    {
        var id = Guid.NewGuid();
        var seller = Seller.Create(
            id: id,
            firstName: "Ivan",
            lastName: "Ivanov",
            phone: "+123456789",
            email: "ivan@example.com",
            birthDate: new DateTime(1990, 1, 1)
        );
        _sellerRepoMock.Setup(r => r.Create(It.IsAny<Seller>())).Returns((Seller s) => s);

        var result = _service.Create(seller);

        _sellerRepoMock.Verify(
            r => r.Create(It.Is<Seller>(s => s.FirstName == "Ivan")),
            Times.Once
        );
    }

    [Fact]
    public void GetById_ShouldReturnSeller()
    {
        var id = Guid.NewGuid();
        var seller = Seller.Create(
            id: id,
            firstName: "Ivan",
            lastName: "Ivanov",
            phone: "+123456789",
            email: "ivan@example.com",
            birthDate: new DateTime(1990, 1, 1)
        );
        var sellerId = new SellerId(id);
        _sellerRepoMock.Setup(r => r.GetById(sellerId)).Returns(seller);

        var result = _service.GetById(sellerId);

        Assert.Equal("Ivan", result.FirstName);
    }
}
