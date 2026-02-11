using Domain.InputPorts;
using Domain.OutputPorts;
using Domain.Models;

namespace Domain;

public sealed class ReviewService(IReviewRepository reviewRepository) : IReviewService
{
    private readonly IReviewRepository _reviewRepository = reviewRepository;

    public Review Create(Review review)
    {
        return _reviewRepository.Create(review);
    }

    public List<Review> GetByCustomerId(CustomerId customerId)
    {
        return _reviewRepository.GetByCustomerId(customerId);
    }

    public Review? GetByOrderId(OrderId orderId)
    {
        return _reviewRepository.GetByOrderId(orderId);
    }

    public Review DeleteById(ReviewId reviewId)
    {
        var deleted = _reviewRepository.DeleteById(reviewId);
        if (deleted is null)
            throw new IdNotFoundException($"Review with ID {reviewId.Id} could not be deleted because it does not exist.");

        return deleted;
    }
}
