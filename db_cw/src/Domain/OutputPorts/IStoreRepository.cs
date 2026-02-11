using Domain.Models;

namespace Domain.OutputPorts;

public interface IStoreRepository
{
    public Store Create(Store store);
    public Store? GetById(StoreId storeId);
    public List<Store> GetBySellerId(SellerId sellerId);
    public Store Update(Store store);
}
