namespace Domain.Models;

public class Order
{
    public Guid Id { get; set; }
    public Guid CustomerId { get; set; }
    public Guid OfferId { get; set; }
    public int Quantity { get; set; }
    public OrderStatus Status { get; set; }

    public Order() { }

    internal Order(Guid id, Guid customerId, Guid offerId, int quantity)
    {
        Id = id;
        CustomerId = customerId;
        OfferId = offerId;
        Quantity = quantity;
        Status = OrderStatus.Created;
    }

    public static Order Create(Guid id, Guid customerId, Guid offerId, int quantity) =>
        new(id, customerId, offerId, quantity);
}

public enum OrderStatus
{
    Created,
    Payed,
    Cancelled,
}

public class OrderId(Guid id)
{
    public Guid Id { get; init; } = id;
}

public class OrderDetailsDto
{
    public Guid OrderId { get; set; }
    public OrderStatus Status { get; set; }
    public int Quantity { get; set; }

    public Guid ProductId { get; set; }
    public string ProductName { get; set; } = "";
    public string ProductDescription { get; set; } = "";

    public Guid OfferId { get; set; }
    public decimal OfferPrice { get; set; }
    public int OfferQuantity { get; set; }

    public Guid StoreId { get; set; }
    public string StoreName { get; set; } = "";

    public Guid? ReviewId { get; set; }
    public int? Rating { get; set; }
    public string? ReviewText { get; set; }
}
