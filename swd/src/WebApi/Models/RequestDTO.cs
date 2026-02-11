namespace WebApi.Models;

public record LoginRequest(string Email, string Role);
public record CreateOrderRequest(Guid OfferId, int Quantity);
public record PaymentRequest(
    string PaymentMethod, 
    string? CardNumber = null, 
    string? ExpirationDate = null, 
    string? Cvc = null,
    PointsInfo? Points = null);

public record PointsInfo(int Used);
public record CreateReviewRequest(Guid OrderId, int Rating, string ReviewText);
public record CreateFavoriteRequest(Guid ProductId);