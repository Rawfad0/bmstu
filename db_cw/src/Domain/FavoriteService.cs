using Domain.InputPorts;
using Domain.OutputPorts;
using Domain.Models;

namespace Domain;

public sealed class FavoriteService(IFavoriteRepository favoriteRepository) : IFavoriteService
{
    private readonly IFavoriteRepository _favoriteRepository = favoriteRepository;

    public Favorite Create(Favorite favorite)
    {
        ValidateFavorite(favorite);
        return _favoriteRepository.Create(favorite);
    }

    public Favorite GetById(FavoriteId favoriteId)
    {
        var favorite = _favoriteRepository.GetById(favoriteId);
        if (favorite is null)
            throw new IdNotFoundException($"Favorite with ID {favoriteId.Id} was not found.");

        return favorite;
    }

    public List<Favorite> GetByCustomerId(CustomerId customerId)
    {
        return _favoriteRepository.GetByCustomerId(customerId);
    }

    public List<FavoriteDetailsDto> GetFavoriteDetailsByCustomerId(CustomerId customerId)
    {
        return _favoriteRepository.GetFavoriteDetailsByCustomerId(customerId);
    }

    public Favorite DeleteById(FavoriteId favoriteId)
    {
        var deleted = _favoriteRepository.DeleteById(favoriteId);
        if (deleted is null)
            throw new IdNotFoundException($"Favorite with ID {favoriteId.Id} could not be deleted because it does not exist.");

        return deleted;
    }
    
    private void ValidateFavorite(Favorite favorite)
    {
        if (favorite.CustomerId == Guid.Empty)
            throw new ValidationException("CustomerId не может быть пустым");
        if (favorite.ProductId == Guid.Empty)
            throw new ValidationException("ProductId не может быть пустым");
    }
}
