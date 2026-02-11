using Domain.Models;

namespace WebApi.WebDTO;

public class ProductInfoWDTO(string name, string category, string description)
{
    public string Name { get; init; } = name;
    public string Category { get; init; } = category;
    public string Description { get; init; } = description;

    public ProductInfo WDTOtoDDTO()
    {
        var productInfo = new ProductInfo(Name, Category, Description);
        return productInfo;
    }
}
