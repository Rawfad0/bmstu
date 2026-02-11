using Domain.Models;

namespace WebApi.WebDTO;

public class OfferInfoWDTO(Guid productId, Guid storeId, decimal price, int quantity, int deliveryTime)
{
    public Guid ProductId { get; init; } = productId;
    public Guid StoreId { get; init; } = storeId;
    public decimal Price { get; init; } = price;
    public int Quantity { get; init; } = quantity;
    public int DeliveryTime { get; init; } = deliveryTime;

    public OfferInfo WDTOtoDDTO()
    {
        var offerInfo = new OfferInfo(ProductId, StoreId, Price, Quantity, DeliveryTime);
        return offerInfo;
    }
}

public class OfferUpdateInfoWDTO(decimal price, int quantity, int deliveryTime)
{
    public decimal Price { get; init; } = price;
    public int Quantity { get; init; } = quantity;
    public int DeliveryTime { get; init; } = deliveryTime;
}