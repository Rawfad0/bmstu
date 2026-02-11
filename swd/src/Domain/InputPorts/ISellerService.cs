using Domain.Models;

namespace Domain.InputPorts;

public interface ISellerService
{
    public Seller Create(SellerInfo sellerInfo);
    public Seller GetById(SellerId sellerId);
    public Seller GetByEmail(string email);
    public Seller Update(Seller seller, SellerInfo sellerInfo);
}
