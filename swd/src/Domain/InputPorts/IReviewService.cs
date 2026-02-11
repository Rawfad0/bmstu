using Domain.Models;

namespace Domain.InputPorts;

public interface IReviewService
{
    public Review Create(Review review);
    public List<Review> GetByCustomerId(CustomerId customerId);
    public Review? GetByOrderId(OrderId orderId);
    public Review UpdateInfo(Review review, ReviewInfo reviewInfo);
    public Review DeleteById(ReviewId reviewId);
}
