using Domain.Models;

namespace WebApi.WebDTO;

public class ReviewInfoWDTO(int rating, string reviewText)
{
    public int Rating { get; init; } = rating;
    public string ReviewText { get; init; } = reviewText;

    public ReviewInfo WDTOtoDDTO()
    {
        var reviewInfo = new ReviewInfo(Rating, ReviewText);
        return reviewInfo;
    }
}