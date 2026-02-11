using Domain.InputPorts;
using Domain.OutputPorts;
using Domain.Models;

namespace Domain;

public sealed class ProductService(IProductRepository productRepository) : IProductService
{
    private readonly IProductRepository _productRepository = productRepository;

    public Product Create(ProductInfo productInfo)
    {
        var product = new Product
        {
            Id = Guid.NewGuid(),
            Name = productInfo.Name,
            Category = productInfo.Category,
            Description = productInfo.Description,
            RatingCount = 0,
            AvgRating = 0.0
        };
        ValidateProduct(product);
        return _productRepository.Create(product);
    }

    public Product GetById(ProductId productId)
    {
        var product = _productRepository.GetById(productId);

        if (product is null)
            throw new IdNotFoundException($"Product with ID {productId.Id} not found.");

        return product;
    }

    public List<Product> GetByName(string name)
    {
        return _productRepository.GetByName(name);
    }

    public Product UpdateName(Product product, string name)
    {
        product.Name = name;
        ValidateProduct(product);
        return _productRepository.Update(product);
    }

    public Product UpdateCategory(Product product, string category)
    {
        product.Category = category;
        ValidateProduct(product);
        return _productRepository.Update(product);
    }

    public Product UpdateDescription(Product product, string description)
    {
        product.Description = description;
        ValidateProduct(product);
        return _productRepository.Update(product);
    }

    public Product AddReview(Product product, int value)
    {
        if (value < 1 || value > 5)
            throw new ArgumentOutOfRangeException(nameof(value), "Rating must be between 1 and 5.");

        var newCount = product.RatingCount + 1;
        var newAvg = ((product.AvgRating * product.RatingCount) + value) / (double)newCount;    // мб стоит хранить не среднее значение а сумму оценок
        product.RatingCount = newCount;
        product.AvgRating = newAvg;

        return _productRepository.Update(product);
    }

    private void ValidateProduct(Product product)
    {
        if (string.IsNullOrWhiteSpace(product.Name))
            throw new ValidationException("Имя продукта не может быть пустым");
        if (string.IsNullOrWhiteSpace(product.Category))
            throw new ValidationException("Категория продукта не может быть пустой");
        if (string.IsNullOrWhiteSpace(product.Description))
            throw new ValidationException("Описание продукта не может быть пустым");
    }
}
