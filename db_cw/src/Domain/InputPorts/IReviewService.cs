using Domain.Models;

namespace Domain.InputPorts;

public interface IReviewService
{
    public Review Create(Review review);
    public List<Review> GetByCustomerId(CustomerId customerId);
    public Review? GetByOrderId(OrderId orderId);
    public Review DeleteById(ReviewId reviewId);
}
