using Domain.Models;

namespace Domain.OutputPorts;

public interface IReviewRepository
{
    public Review Create(Review review);
    public Review? GetById(ReviewId review);
    public List<Review> GetByCustomerId(CustomerId customerId);
    public Review? GetByOrderId(OrderId orderId);
    public Review? DeleteById(ReviewId review);
}
