using Domain;
using Domain.OutputPorts;
using Moq;
using Xunit;
using Domain.Models;

public class ProductServiceTests
{
    private readonly Mock<IProductRepository> _repoMock;
    private readonly ProductService _service;

    public ProductServiceTests()
    {
        _repoMock = new Mock<IProductRepository>();
        _service = new ProductService(_repoMock.Object);
    }

    [Fact]
    public void Create_ShouldCreateProduct()
    {
        var productInfo = new ProductInfo(
            "Product",
            "Category",
            "Product description"
        );
        _repoMock.Setup(r => r.Create(It.IsAny<Product>())).Returns<Product>(p => p);

        var result = _service.Create(productInfo);

        Assert.Equal(productInfo.Name, result.Name);
        Assert.Equal(productInfo.Category, result.Category);
        Assert.Equal(productInfo.Description, result.Description);
        _repoMock.Verify(r => r.Create(It.IsAny<Product>()), Times.Once);
    }

    [Fact]
    public void GetById_ShouldReturnProduct_WhenExists()
    {
        var id = Guid.NewGuid();
        var product = Product.Create(id, "Name", "Category", "Desc");
        var productId = new ProductId(id);
        _repoMock.Setup(r => r.GetById(productId)).Returns(product);

        var result = _service.GetById(productId);

        Assert.Equal(product, result);
    }

    [Fact]
    public void GetById_ShouldThrow_WhenNotFound()
    {
        var id = Guid.NewGuid();
        var productId = new ProductId(id);
        _repoMock.Setup(r => r.GetById(productId)).Returns(default(Product));

        Assert.Throws<IdNotFoundException>(() => _service.GetById(productId));
    }

    [Fact]
    public void UpdateName_ShouldUpdateAndReturnProduct()
    {
        var id = Guid.NewGuid();
        var product = Product.Create(id, "OldName", "Category", "Desc");
        var productId = new ProductId(id);
        _repoMock.Setup(r => r.GetById(productId)).Returns(product);
        _repoMock.Setup(r => r.Update(It.IsAny<Product>())).Returns<Product>(p => p);

        var updated = _service.UpdateName(product, "NewName");

        Assert.Equal("NewName", updated.Name);
        _repoMock.Verify(r => r.Update(product), Times.Once);
    }

    [Fact]
    public void AddReview_ShouldUpdateRating()
    {
        var id = Guid.NewGuid();
        var product = Product.Create(id, "Name", "Category", "Desc");
        var productId = new ProductId(id);
        _repoMock.Setup(r => r.GetById(productId)).Returns(product);
        _repoMock.Setup(r => r.Update(It.IsAny<Product>())).Returns<Product>(p => p);

        var updated = _service.AddReview(product, 5);
        updated = _service.AddReview(product, 3);
        updated = _service.AddReview(product, 4);

        Assert.Equal(3, updated.RatingCount);
        Assert.True(updated.AvgRating > 4 - 0.001 && updated.AvgRating < 4 + 0.001);
        _repoMock.Verify(r => r.Update(product), Times.Exactly(3));
    }

    [Fact]
    public void AddReview_ShouldThrow_WhenValueOutOfRange()
    {
        var id = Guid.NewGuid();
        var product = Product.Create(id, "Name", "Category", "Desc");
        var productId = new ProductId(id);

        Assert.Throws<ArgumentOutOfRangeException>(() => _service.AddReview(product, 0));
        Assert.Throws<ArgumentOutOfRangeException>(() => _service.AddReview(product, 6));
    }
}
