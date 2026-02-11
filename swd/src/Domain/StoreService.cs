using Domain.InputPorts;
using Domain.OutputPorts;
using Domain.Models;

namespace Domain;

public sealed class StoreService(IStoreRepository storeRepository) : IStoreService
{
    private readonly IStoreRepository _storeRepository = storeRepository;

    public Store Create(StoreInfo storeInfo, SellerId sellerId)
    {
        var store = new Store 
        {
            Id = Guid.NewGuid(),
            OwnerSellerId = sellerId.Id,
            Name = storeInfo.Name,
            Ogrn = storeInfo.Ogrn,
            RatingCount = 0,
            AvgRating = 0.0
        };
        ValidateStore(store);
        return _storeRepository.Create(store);
    }

    public Store GetById(StoreId storeId)
    {
        var store = _storeRepository.GetById(storeId);

        if (store is null)
            throw new IdNotFoundException($"Store with ID {storeId.Id} not found.");

        return store;
    }

    public List<Store> GetBySellerId(SellerId sellerId)
    {
        return _storeRepository.GetBySellerId(sellerId);
    }

    public Store Update(Store store, StoreInfo storeInfo)
    {
        store.Name = storeInfo.Name;
        store.Ogrn = storeInfo.Ogrn;
        ValidateStore(store);

        return _storeRepository.Update(store);
    }

    public Store AddReview(Store store, int value)
    {
        if (value < 1 || value > 5)
            throw new ArgumentOutOfRangeException(nameof(value), "Rating must be between 1 and 5.");

        int newCount = store.RatingCount + 1;
        double newAvg = ((store.AvgRating * store.RatingCount) + value) / (double)newCount;
        store.RatingCount = newCount;
        store.AvgRating = newAvg;

        return _storeRepository.Update(store);
    }
    
    private void ValidateStore(Store store)
    {
        if (store.OwnerSellerId == Guid.Empty)
            throw new ValidationException("OwnerSellerId не может быть пустым");
        if (string.IsNullOrWhiteSpace(store.Name))
            throw new ValidationException("Название магазина не может быть пустым");
        if (string.IsNullOrWhiteSpace(store.Ogrn))
            throw new ValidationException("ОГРН магазина не может быть пустым");
    }
}
