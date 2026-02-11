namespace Domain.Models;

public class Favorite
{
    public Guid Id { get; set; }
    public Guid CustomerId { get; set; }
    public Guid ProductId { get; set; }

    public Favorite() { }

    internal Favorite(Guid id, Guid customerId, Guid productId)
    {
        Id = id;
        CustomerId = customerId;
        ProductId = productId;
    }

    public static Favorite Create(Guid id, Guid customerId, Guid productId) =>
        new(id, customerId, productId);
}

public class FavoriteId(Guid id)
{
    public Guid Id { get; init; } = id;
}

public class FavoriteDetailsDto
{
    public Guid FavoriteId { get; set; }
    public Guid CustomerId { get; set; }
    public Guid ProductId { get; set; }
    public string ProductName { get; set; } = string.Empty;
    public string ProductDescription { get; set; } = string.Empty;
}
