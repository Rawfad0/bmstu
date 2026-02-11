using Xunit;
using Moq;
using Domain.InputPorts;
using Domain.OutputPorts;
using Domain.Models;
using Domain;

namespace Domain.Tests;

public class StoreServiceTests
{
    private readonly Mock<IStoreRepository> _storeRepoMock;
    private readonly StoreService _service;

    public StoreServiceTests()
    {
        _storeRepoMock = new Mock<IStoreRepository>();
        _service = new StoreService(_storeRepoMock.Object);
    }

    [Fact]
    public void Create_ShouldCallRepository()
    {
        var sellerId = Guid.NewGuid();
        var sellerIdDto = new SellerId(sellerId);
        var storeInfo = new StoreInfo(
            name: "StoreName",
            ogrn: "1234567890123"
        );
        _storeRepoMock.Setup(r => r.Create(It.IsAny<Store>())).Returns((Store s) => s);

        var result = _service.Create(storeInfo, sellerIdDto);

        _storeRepoMock.Verify(r => r.Create(It.Is<Store>(s => s.Name == "StoreName")), Times.Once);
        Assert.Equal("StoreName", result.Name);
    }

    [Fact]
    public void GetById_ShouldReturnStore_WhenExists()
    {
        var storeId = Guid.NewGuid();
        var storeIdDto= new StoreId(storeId);
        var sellerId = Guid.NewGuid();
        var sellerIdDto = new SellerId(sellerId);
        var store = Store.Create(
            id: storeId,
            ownerSellerId: sellerId,
            name: "StoreName",
            ogrn: "1234567890123"
        );
        _storeRepoMock.Setup(r => r.GetById(storeIdDto)).Returns(store);

        var result = _service.GetById(storeIdDto);

        Assert.Equal("StoreName", result.Name);
    }

    [Fact]
    public void GetById_ShouldThrow_WhenNotFound()
    {
        var id = new StoreId(Guid.NewGuid());
        _storeRepoMock.Setup(r => r.GetById(id)).Returns((Store?)null);

        Assert.Throws<IdNotFoundException>(() => _service.GetById(id));
    }

    [Fact]
    public void Update_ShouldModifyAndCallRepository()
    {
        var storeId = Guid.NewGuid();
        var storeIdDto= new StoreId(storeId);
        var sellerId = Guid.NewGuid();
        var sellerIdDto = new SellerId(sellerId);
        var store = Store.Create(
            id: storeId,
            ownerSellerId: sellerId,
            name: "StoreName",
            ogrn: "1234567890123"
        );
        var info = new StoreInfo("NewName", "111");
        _storeRepoMock.Setup(r => r.Update(It.IsAny<Store>())).Returns((Store s) => s);

        var result = _service.Update(store, info);

        _storeRepoMock.Verify(r => r.Update(It.Is<Store>(s => s.Name == "NewName" && s.Ogrn == "111")), Times.Once);
        Assert.Equal("NewName", result.Name);
        Assert.Equal("111", result.Ogrn);
    }

    [Fact]
    public void AddReview_ShouldUpdateRatingCorrectly()
    {
        var storeId = Guid.NewGuid();
        var storeIdDto= new StoreId(storeId);
        var sellerId = Guid.NewGuid();
        var sellerIdDto = new SellerId(sellerId);
        var store = Store.Create(
            id: storeId,
            ownerSellerId: sellerId,
            name: "StoreName",
            ogrn: "1234567890123"
        );
        _storeRepoMock.Setup(r => r.Update(It.IsAny<Store>())).Returns((Store s) => s);

        var result = _service.AddReview(store, 5);
        result = _service.AddReview(store, 3);
        result = _service.AddReview(store, 4);

        _storeRepoMock.Verify(r => r.Update(It.IsAny<Store>()), Times.Exactly(3));
        Assert.Equal(3, result.RatingCount);
        Assert.Equal((5 + 3 + 4) / 3, result.AvgRating, precision: 3);
    }

    [Fact]
    public void AddReview_ShouldThrow_WhenValueOutOfRange()
    {
        var storeId = Guid.NewGuid();
        var storeIdDto= new StoreId(storeId);
        var sellerId = Guid.NewGuid();
        var sellerIdDto = new SellerId(sellerId);
        var store = Store.Create(
            id: storeId,
            ownerSellerId: sellerId,
            name: "StoreName",
            ogrn: "1234567890123"
        );

        Assert.Throws<ArgumentOutOfRangeException>(() => _service.AddReview(store, 0));
        Assert.Throws<ArgumentOutOfRangeException>(() => _service.AddReview(store, 6));
    }
}
