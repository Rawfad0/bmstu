using Domain.Models;

namespace Domain.InputPorts;

public interface IProductService
{
    public Product Create(ProductInfo productInfo);
    public Product GetById(ProductId productId);
    public List<Product> GetByName(string name);
    public Product UpdateName(Product product, string name);
    public Product UpdateCategory(Product product, string category);
    public Product UpdateDescription(Product product, string description);
    public Product AddReview(Product product, int value);
}
