using Domain.Models;

namespace Domain.OutputPorts;

public interface ISellerRepository
{
    public Seller Create(Seller seller);
    public Seller? GetById(SellerId sellerId);
    public Seller? GetByEmail(string email);
    public Seller Update(Seller seller);
}
