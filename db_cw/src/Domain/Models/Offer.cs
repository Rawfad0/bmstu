using System.Net;

namespace Domain.Models;

public class Offer
{
    public Guid Id { get; set; }
    public Guid ProductId { get; set; }
    public Guid StoreId { get; set; }
    public decimal Price { get; set; }
    public int Quantity { get; set; }
    public int DeliveryTime { get; set; }

    public Offer() { }

    internal Offer(Guid id, Guid productId, Guid storeId, decimal price, int quantity, int deliveryTime)
    {
        Id = id;
        ProductId = productId;
        StoreId = storeId;
        Price = price;
        Quantity = quantity;
        DeliveryTime = deliveryTime;
    }

    public static Offer Create(Guid id, Guid productId, Guid storeId, decimal price, int quantity, int deliveryTime) =>
        new(id, productId, storeId, price, quantity, deliveryTime);
}

public class OfferId(Guid id)
{
    public Guid Id { get; init; } = id;
}

public class OfferDetailsDto
{
    public Guid OfferId { get; set; }
    public decimal Price { get; set; }
    public int Quantity { get; set; }
    public int DeliveryTime { get; set; }

    public Guid ProductId { get; set; }
    public string ProductName { get; set; } = string.Empty;

    public Guid StoreId { get; set; }
    public string StoreName { get; set; } = string.Empty;
    public int RatingCount { get; set; }
    public double AvgRating { get; set; }

    public static Offer CreateOffer(OfferDetailsDto offerDetails)
    {
        return Offer.Create(
            offerDetails.OfferId,
            offerDetails.ProductId,
            offerDetails.StoreId,
            offerDetails.Price,
            offerDetails.Quantity,
            offerDetails.DeliveryTime
        );
    }
}
