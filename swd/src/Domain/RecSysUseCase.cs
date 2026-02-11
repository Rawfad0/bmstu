using Domain.InputPorts;
using Domain.OutputPorts;
using Domain.Models;
using System.Collections.Generic;

namespace Domain;

public class RecSysUseCase : IRecSysUseCase
{
    private readonly IOfferService _offerService;
    private readonly IFavoriteService _favoriteService;

    private readonly double _priceCoef;
    private readonly double _deliveryTimeCoef;

    public RecSysUseCase(
        IOfferService offerService,
        IFavoriteService favoriteService,
        double priceCoef,
        double deliveryTimeCoef)
    {
        _offerService = offerService;
        _favoriteService = favoriteService;
        _priceCoef = priceCoef;
        _deliveryTimeCoef = deliveryTimeCoef;
    }

    public List<Offer> Recommend(CustomerId customerId)
    {
        var favorites = _favoriteService.GetByCustomerId(customerId);
        var recommendedOffers = new List<Offer>();

        foreach (var favorite in favorites)
        {
            var productId = new ProductId(favorite.ProductId);
            var offers = _offerService.GetByProductId(productId);

            if (offers.Count == 0)
                continue;
            if (offers.Count <= 2)
            {
                recommendedOffers.AddRange(offers);
                continue;
            }

            Offer bestByPrice = offers[0];
            Offer bestByDelivery = offers[0];
            Offer optimal = offers[0];

            foreach (var offer in offers)
            {
                if (offer.Price < bestByPrice.Price)
                    bestByPrice = offer;
                if (offer.DeliveryTime < bestByDelivery.DeliveryTime)
                    bestByDelivery = offer;

                var currentScore = _priceCoef * (double)offer.Price + _deliveryTimeCoef * offer.DeliveryTime;
                var optimalScore = _priceCoef * (double)optimal.Price + _deliveryTimeCoef * optimal.DeliveryTime;
                if (currentScore < optimalScore)
                    optimal = offer;
            }
            recommendedOffers.Add(bestByPrice);
            if (bestByDelivery != bestByPrice)
                recommendedOffers.Add(bestByDelivery);
            if (optimal != bestByPrice && optimal != bestByDelivery)
                recommendedOffers.Add(optimal);
        }
        return recommendedOffers;
    }
}
