using Xunit;
using Moq;
using Domain;
using Domain.OutputPorts;
using Domain.Models;

public class FavoriteServiceTests
{
    private readonly Mock<IFavoriteRepository> _favoriteRepoMock;
    private readonly FavoriteService _service;

    public FavoriteServiceTests()
    {
        _favoriteRepoMock = new Mock<IFavoriteRepository>();
        _service = new FavoriteService(_favoriteRepoMock.Object);
    }

    [Fact]
    public void Create_ShouldCreateFavorite()
    {
        var customerId = Guid.NewGuid();
        var productId = Guid.NewGuid();
        var favorite = Favorite.Create(Guid.NewGuid(), customerId, productId);
        _favoriteRepoMock.Setup(r => r.Create(It.IsAny<Favorite>())).Returns((Favorite f) => f);

        var result = _service.Create(favorite);

        _favoriteRepoMock.Verify(
            r => r.Create(It.Is<Favorite>(f => f.CustomerId == customerId && f.ProductId == productId)),
            Times.Once
        );
        Assert.Equal(customerId, result.CustomerId);
        Assert.Equal(productId, result.ProductId);
    }

    [Fact]
    public void GetById_WhenExists_ShouldReturnFavorite()
    {
        var id = Guid.NewGuid();
        var favorite = Favorite.Create(id, Guid.NewGuid(), Guid.NewGuid());
        var favoriteId = new FavoriteId(id);
        _favoriteRepoMock.Setup(r => r.GetById(favoriteId)).Returns(favorite);

        var result = _service.GetById(favoriteId);

        Assert.Equal(favorite, result);
    }

    [Fact]
    public void GetById_WhenNotExists_ShouldThrow()
    {
        var id = Guid.NewGuid();
        var favoriteId = new FavoriteId(id);
        _favoriteRepoMock.Setup(r => r.GetById(favoriteId)).Returns((Favorite?)null);

        Assert.Throws<IdNotFoundException>(() => _service.GetById(favoriteId));
    }

    [Fact]
    public void GetByCustomerId_ShouldReturnFavoritesList()
    {
        var customerId = Guid.NewGuid();
        var favorites = new List<Favorite>
        {
            Favorite.Create(Guid.NewGuid(), customerId, Guid.NewGuid()),
            Favorite.Create(Guid.NewGuid(), customerId, Guid.NewGuid())
        };
        var customerIdDto = new CustomerId(customerId);
        _favoriteRepoMock.Setup(r => r.GetByCustomerId(customerIdDto)).Returns(favorites);

        var result = _service.GetByCustomerId(customerIdDto);

        Assert.Equal(2, result.Count);
        Assert.All(result, f => Assert.Equal(customerId, f.CustomerId));
    }

    [Fact]
    public void DeleteById_WhenExists_ShouldDeleteAndReturn()
    {
        var id = Guid.NewGuid();
        var favorite = Favorite.Create(id, Guid.NewGuid(), Guid.NewGuid());
        var favoriteId = new FavoriteId(id);
        _favoriteRepoMock.Setup(r => r.DeleteById(favoriteId)).Returns(favorite);

        var result = _service.DeleteById(favoriteId);

        _favoriteRepoMock.Verify(r => r.DeleteById(favoriteId), Times.Once);
        Assert.Equal(favorite, result);
    }

    [Fact]
    public void DeleteById_WhenNotExists_ShouldThrow()
    {
        var id = Guid.NewGuid();
        var favoriteId = new FavoriteId(id);
        _favoriteRepoMock.Setup(r => r.DeleteById(favoriteId)).Returns((Favorite?)null);

        Assert.Throws<IdNotFoundException>(() => _service.DeleteById(favoriteId));
    }
}
