using Domain.Models;

namespace Domain.InputPorts;

public interface IOfferService
{
    public Offer Create(Offer offer);
    public Offer GetById(OfferId offerId);
    public List<Offer> GetByProductId(ProductId productId);
    public List<Offer> GetByStoreId(StoreId storeId);
    public List<OfferDetailsDto> GetOfferDetailsByProductId(ProductId productId);
    public Offer UpdatePrice(Offer offer, decimal price);
    public Offer UpdateQuantity(Offer offer, int quantity);
    public Offer UpdateDeliveryTime(Offer offer, int deliveryTime);
    public Offer IncrQuantity(Offer offer, int increment);
    public Offer DecrQuantity(Offer offer, int decrement);
    public Offer DeleteById(OfferId offerId);
}
