using Domain.InputPorts;
using Domain.OutputPorts;
using Domain.Models;

namespace Domain;

public sealed class OfferService(IOfferRepository offerRepository) : IOfferService
{
    private readonly IOfferRepository _offerRepository = offerRepository;

    public Offer Create(OfferInfo offerInfo)
    {
        var offer = new Offer
        {
            Id = Guid.NewGuid(),
            ProductId = offerInfo.ProductId,
            StoreId = offerInfo.StoreId,
            Price = offerInfo.Price,
            Quantity = offerInfo.Quantity,
            DeliveryTime = offerInfo.DeliveryTime
        };
        ValidateOffer(offer);
        return _offerRepository.Create(offer);
    }

    public Offer GetById(OfferId offerId)
    {
        var offer = _offerRepository.GetById(offerId);

        if (offer is null)
            throw new IdNotFoundException($"Offer with ID {offerId.Id} was not found.");

        return offer;
    }

    public List<Offer> GetByProductId(ProductId productId)
    {
        return _offerRepository.GetByProductId(productId);
    }
    public List<Offer> GetByStoreId(StoreId storeId)
    {
        return _offerRepository.GetByStoreId(storeId);
    }

    public List<OfferDetailsDto> GetOfferDetailsByProductId(ProductId productId)
    {
        return _offerRepository.GetOfferDetailsByProductId(productId);
    }

    public Offer UpdatePrice(Offer offer, decimal price)
    {
        offer.Price = price;
        ValidateOffer(offer);
        return _offerRepository.Update(offer);
    }

    public Offer UpdateQuantity(Offer offer, int quantity)
    {
        offer.Quantity = quantity;
        ValidateOffer(offer);
        return _offerRepository.Update(offer);
    }

    public Offer UpdateDeliveryTime(Offer offer, int deliveryTime)
    {
        offer.DeliveryTime = deliveryTime;
        ValidateOffer(offer);
        return _offerRepository.Update(offer);
    }

    public Offer IncrQuantity(Offer offer, int increment)
    {
        if (increment <= 0)
            throw new ArgumentException("Increment must be positive.", nameof(increment));

        offer.Quantity += increment;
        return _offerRepository.Update(offer);
    }

    public Offer DecrQuantity(Offer offer, int decrement)
    {
        if (decrement <= 0)
            throw new ArgumentException("Decrement must be positive.", nameof(decrement));

        if (decrement > offer.Quantity)
            throw new ArgumentException("Decrement must be less than quantity", nameof(decrement));

        offer.Quantity -= decrement;

        return _offerRepository.Update(offer);
    }

    public Offer DeleteById(OfferId offerId)
    {
        var deleted = _offerRepository.DeleteById(offerId);

        if (deleted is null)
            throw new IdNotFoundException($"Offer could not be deleted because it does not exist.");

        return deleted;
    }

    private void ValidateOffer(Offer offer)
    {
        if (offer.ProductId == Guid.Empty)
            throw new ValidationException("ProductId не может быть пустым");
        if (offer.StoreId == Guid.Empty)
            throw new ValidationException("StoreId не может быть пустым");
        if (offer.Price <= 0)
            throw new ValidationException("Цена должна быть больше нуля");
        if (offer.Quantity < 0)
            throw new ValidationException("Количество не может быть отрицательным");
        if (offer.DeliveryTime < 0)
            throw new ValidationException("Время доставки не может быть отрицательным");
    }
}
