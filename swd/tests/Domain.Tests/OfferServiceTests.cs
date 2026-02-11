using Xunit;
using Moq;
using Domain;
using Domain.OutputPorts;
using Domain.Models;

public class OfferServiceTests
{
    private readonly Mock<IOfferRepository> _offerRepoMock;
    private readonly OfferService _service;

    public OfferServiceTests()
    {
        _offerRepoMock = new Mock<IOfferRepository>();
        _service = new OfferService(_offerRepoMock.Object);
    }

    [Fact]
    public void Create_ShouldCreateOffer()
    {
        _offerRepoMock.Setup(r => r.Create(It.IsAny<Offer>())).Returns((Offer o) => o);
        var productId = Guid.NewGuid();
        var storeId = Guid.NewGuid();
        var offerInfo = new OfferInfo(productId, storeId, 100m, 10, 3);

        var result = _service.Create(offerInfo);

        _offerRepoMock.Verify(
            r => r.Create(It.Is<Offer>(o => o.ProductId == productId && o.StoreId == storeId && o.Price == 100m && o.Quantity == 10 && o.DeliveryTime == 3)),
            Times.Once
        );
        Assert.Equal(productId, result.ProductId);
        Assert.Equal(storeId, result.StoreId);
    }

    [Fact]
    public void GetById_WhenExists_ShouldReturnOffer()
    {
        var id = Guid.NewGuid();
        var offer = Offer.Create(id, Guid.NewGuid(), Guid.NewGuid(), 50m, 5, 2);
        var offerId = new OfferId(id);
        _offerRepoMock.Setup(r => r.GetById(offerId)).Returns(offer);

        var result = _service.GetById(offerId);

        Assert.Equal(offer, result);
    }

    [Fact]
    public void GetById_WhenNotExists_ShouldThrow()
    {
        var id = Guid.NewGuid();
        var offerId = new OfferId(id);
        _offerRepoMock.Setup(r => r.GetById(offerId)).Returns((Offer?)null);

        Assert.Throws<IdNotFoundException>(() => _service.GetById(offerId));
    }

    [Fact]
    public void GetByProductId_ShouldReturnOffersList()
    {
        var productId = Guid.NewGuid();
        var offers = new List<Offer>
        {
            Offer.Create(Guid.NewGuid(), productId, Guid.NewGuid(), 10, 5, 1),
            Offer.Create(Guid.NewGuid(), productId, Guid.NewGuid(), 20, 3, 2)
        };
        var productIdDto = new ProductId(productId);
        _offerRepoMock.Setup(r => r.GetByProductId(productIdDto)).Returns(offers);

        var result = _service.GetByProductId(productIdDto);

        Assert.Equal(2, result.Count);
        Assert.All(result, o => Assert.Equal(productId, o.ProductId));
    }

    [Fact]
    public void GetByStoreId_ShouldReturnOffersList()
    {
        var storeId = Guid.NewGuid();
        var offers = new List<Offer>
        {
            Offer.Create(Guid.NewGuid(), Guid.NewGuid(), storeId, 30, 8, 4),
            Offer.Create(Guid.NewGuid(), Guid.NewGuid(), storeId, 40, 6, 5)
        };
        var storeIdDto = new StoreId(storeId);
        _offerRepoMock.Setup(r => r.GetByStoreId(storeIdDto)).Returns(offers);

        var result = _service.GetByStoreId(storeIdDto);

        Assert.Equal(2, result.Count);
        Assert.All(result, o => Assert.Equal(storeId, o.StoreId));
    }

    [Fact]
    public void UpdatePrice_ShouldUpdateAndReturnOffer()
    {
        var id = Guid.NewGuid();
        var offer = Offer.Create(id, Guid.NewGuid(), Guid.NewGuid(), 10, 5, 2);
        var offerId = new OfferId(id);
        _offerRepoMock.Setup(r => r.GetById(offerId)).Returns(offer);
        _offerRepoMock.Setup(r => r.Update(offer)).Returns(offer);

        var result = _service.UpdatePrice(offer, 99m);

        Assert.Equal(99m, result.Price);
        _offerRepoMock.Verify(r => r.Update(offer), Times.Once);
    }

    [Fact]
    public void UpdateQuantity_ShouldUpdateAndReturnOffer()
    {
        var id = Guid.NewGuid();
        var offer = Offer.Create(id, Guid.NewGuid(), Guid.NewGuid(), 10, 5, 2);
        var offerId = new OfferId(id);
        _offerRepoMock.Setup(r => r.GetById(offerId)).Returns(offer);
        _offerRepoMock.Setup(r => r.Update(offer)).Returns(offer);

        var result = _service.UpdateQuantity(offer, 42);

        Assert.Equal(42, result.Quantity);
        _offerRepoMock.Verify(r => r.Update(offer), Times.Once);
    }

    [Fact]
    public void UpdateDeliveryTime_ShouldUpdateAndReturnOffer()
    {
        var id = Guid.NewGuid();
        var offer = Offer.Create(id, Guid.NewGuid(), Guid.NewGuid(), 10, 5, 2);
        var offerId = new OfferId(id);
        _offerRepoMock.Setup(r => r.GetById(offerId)).Returns(offer);
        _offerRepoMock.Setup(r => r.Update(offer)).Returns(offer);

        var result = _service.UpdateDeliveryTime(offer, 7);

        Assert.Equal(7, result.DeliveryTime);
        _offerRepoMock.Verify(r => r.Update(offer), Times.Once);
    }

    [Fact]
    public void IncrQuantity_WhenValid_ShouldIncreaseQuantity()
    {
        var id = Guid.NewGuid();
        var offer = Offer.Create(id, Guid.NewGuid(), Guid.NewGuid(), 10, 5, 2);
        var offerId = new OfferId(id);
        _offerRepoMock.Setup(r => r.GetById(offerId)).Returns(offer);
        _offerRepoMock.Setup(r => r.Update(offer)).Returns(offer);

        var result = _service.IncrQuantity(offer, 3);

        Assert.Equal(8, result.Quantity);
    }

    [Fact]
    public void IncrQuantity_WhenNonPositive_ShouldThrow()
    {
        var id = Guid.NewGuid();
        var offer = Offer.Create(id, Guid.NewGuid(), Guid.NewGuid(), 10, 5, 2);
        Assert.Throws<ArgumentException>(() => _service.IncrQuantity(offer, 0));
        Assert.Throws<ArgumentException>(() => _service.IncrQuantity(offer, -1));
    }

    [Fact]
    public void DecrQuantity_WhenValid_ShouldDecreaseQuantity()
    {
        var id = Guid.NewGuid();
        var offer = Offer.Create(id, Guid.NewGuid(), Guid.NewGuid(), 10, 5, 2);
        var offerId = new OfferId(id);
        _offerRepoMock.Setup(r => r.GetById(offerId)).Returns(offer);
        _offerRepoMock.Setup(r => r.Update(offer)).Returns(offer);

        var result = _service.DecrQuantity(offer, 3);

        Assert.Equal(2, result.Quantity);
    }

    [Fact]
    public void DecrQuantity_WhenNonPositive_ShouldThrow()
    {
        var id = Guid.NewGuid();
        var offer = Offer.Create(id, Guid.NewGuid(), Guid.NewGuid(), 10, 5, 2);

        Assert.Throws<ArgumentException>(() => _service.DecrQuantity(offer, 0));
        Assert.Throws<ArgumentException>(() => _service.DecrQuantity(offer, -1));
    }

    [Fact]
    public void DecrQuantity_WhenGreaterThanQuantity_ShouldThrow()
    {
        var id = Guid.NewGuid();
        var offer = Offer.Create(id, Guid.NewGuid(), Guid.NewGuid(), 10, 2, 1);
        var offerId = new OfferId(id);
        _offerRepoMock.Setup(r => r.GetById(offerId)).Returns(offer);

        Assert.Throws<ArgumentException>(() => _service.DecrQuantity(offer, 3));
    }

    [Fact]
    public void Delete_WhenExists_ShouldReturnDeletedOffer()
    {
        var id = Guid.NewGuid();
        var offer = Offer.Create(id, Guid.NewGuid(), Guid.NewGuid(), 10, 5, 2);
        var offerId = new OfferId(id);
        _offerRepoMock.Setup(r => r.DeleteById(offerId)).Returns(offer);

        var result = _service.DeleteById(offerId);

        Assert.Equal(offer, result);
    }

    [Fact]
    public void Delete_WhenNotExists_ShouldThrow()
    {
        var id = Guid.NewGuid();
        var offerId = new OfferId(id);
        _offerRepoMock.Setup(r => r.DeleteById(offerId)).Returns((Offer?)null);

        Assert.Throws<IdNotFoundException>(() => _service.DeleteById(offerId));
    }
}
