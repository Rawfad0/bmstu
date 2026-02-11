using Domain.Models;

namespace Domain.InputPorts;

public interface IFavoriteService
{
    public Favorite Create(Favorite favorite);
    public Favorite GetById(FavoriteId favoriteId);
    public List<Favorite> GetByCustomerId(CustomerId customerId);
    public List<FavoriteDetailsDto> GetFavoriteDetailsByCustomerId(CustomerId customerId);
    public Favorite DeleteById(FavoriteId favoriteId);
}
