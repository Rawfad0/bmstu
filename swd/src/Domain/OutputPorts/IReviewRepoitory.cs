using Domain.Models;

namespace Domain.OutputPorts;

public interface IReviewRepository
{
    public Review Create(Review review);
    public Review? GetById(ReviewId review);
    public List<Review> GetByCustomerId(CustomerId customerId);
    public Review? GetByOrderId(OrderId orderId);
    public Review Update(Review review);
    public Review? DeleteById(ReviewId review);
}
