namespace Domain.Models;

public class Review
{
    public Guid Id { get; set; }
    public Guid CustomerId { get; set; }
    public Guid OrderId { get; set; }
    public int Rating { get; set; }
    public string ReviewText { get; set; } = string.Empty;

    public Review() { }

    internal Review(Guid id, Guid customerId, Guid orderId, int rating, string reviewText)
    {
        Id = id;
        CustomerId = customerId;
        OrderId = orderId;
        Rating = rating;
        ReviewText = reviewText;
    }

    public static Review Create(Guid id, Guid customerId, Guid orderId, int rating, string reviewText) =>
        new(id, customerId, orderId, rating, reviewText);
}

public class ReviewId(Guid id)
{
    public Guid Id { get; init; } = id;
}

public class ReviewInfo(int rating, string reviewText)
{
    public int Rating { get; init; } = rating;
    public string ReviewText { get; init; } = reviewText;
}