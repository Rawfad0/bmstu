using Domain.Models;

namespace Domain.OutputPorts;

public interface IOfferRepository
{
    public Offer Create(Offer offer);
    public Offer? GetById(OfferId offrId);
    public List<Offer> GetByProductId(ProductId productId);
    public List<Offer> GetByStoreId(StoreId storeId);
    public List<OfferDetailsDto> GetOfferDetailsByProductId(ProductId productId);
    public Offer Update(Offer offer);
    public Offer? DeleteById(OfferId offerId);
}
