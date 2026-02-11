using Domain.Models;

namespace Domain.InputPorts;

public interface IStoreService
{
    public Store Create(StoreInfo storeInfo, SellerId sellerId);
    public Store GetById(StoreId storeId);
    public List<Store> GetBySellerId(SellerId sellerId);
    public Store Update(Store store, StoreInfo storeInfo);
    public Store AddReview(Store store, int value);
}
