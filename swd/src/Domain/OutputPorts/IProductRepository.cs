using Domain.Models;

namespace Domain.OutputPorts;

public interface IProductRepository
{
    public Product Create(Product product);
    public Product? GetById(ProductId productId);
    public List<Product> GetByName(string name);
    public Product Update(Product product);
}
