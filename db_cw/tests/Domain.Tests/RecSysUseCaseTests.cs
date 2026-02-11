using System;
using System.Collections.Generic;
using Xunit;
using Moq;
using Domain;
using Domain.InputPorts;
using Domain.OutputPorts;
using Domain.Models;

public class RecSysUseCaseTests
{
    private readonly Mock<IOfferRepository> _offerRepoMock;
    private readonly Mock<IFavoriteRepository> _favoriteRepoMock;
    private readonly OfferService _offerService;
    private readonly FavoriteService _favoriteService;
    private readonly RecSysUseCase _useCase;
    private readonly double _priceCoef = 1.0;
    private readonly double _deliveryTimeCoef = 100.0;

    public RecSysUseCaseTests()
    {
        _offerRepoMock = new Mock<IOfferRepository>();
        _favoriteRepoMock = new Mock<IFavoriteRepository>();
        _offerService = new OfferService(_offerRepoMock.Object);
        _favoriteService = new FavoriteService(_favoriteRepoMock.Object);

        _useCase = new RecSysUseCase(
            _offerService,
            _favoriteService,
            _priceCoef,
            _deliveryTimeCoef
        );
    }

    [Fact]
    public void Recommend_ShouldGetRecList()
    {
        var customerId = Guid.NewGuid();
        var productId = Guid.NewGuid();

        var offers = new List<Offer>
        {
            Offer.Create(Guid.NewGuid(), Guid.NewGuid(), productId, 500m, 100, 7),
            Offer.Create(Guid.NewGuid(), Guid.NewGuid(), productId, 550m, 100, 6),
            Offer.Create(Guid.NewGuid(), Guid.NewGuid(), productId, 650m, 100, 5),
            Offer.Create(Guid.NewGuid(), Guid.NewGuid(), productId, 800m, 100, 4),
            Offer.Create(Guid.NewGuid(), Guid.NewGuid(), productId, 1100m, 100, 3)
        };

        for (int i = 0; i < offers.Count; i++)
        {
            var offerId = new OfferId(offers[i].Id);
            _offerRepoMock.Setup(r => r.GetById(offerId)).Returns(offers[i]);
        }

        var favorites = new List<Favorite>
        {
            Favorite.Create(Guid.NewGuid(), customerId, productId)
        };

        _favoriteRepoMock
            .Setup(r => r.GetByCustomerId(It.Is<CustomerId>(id => id.Id == customerId)))
            .Returns(favorites);

        _offerRepoMock
            .Setup(r => r.GetByProductId(It.Is<ProductId>(id => id.Id == productId)))
            .Returns(offers);

        var result = _useCase.Recommend(new CustomerId(customerId));

        // offers[0] => 500 + 700 = 1200
        // offers[1] => 550 + 600 = 1150
        // offers[2] => 650 + 500 = 1150
        // offers[3] => 800 + 400 = 1200
        // offers[4] => 1100 + 300 = 1400

        Assert.Equal(new List<Offer> { offers[0], offers[4], offers[1] }, result);
    }
}
