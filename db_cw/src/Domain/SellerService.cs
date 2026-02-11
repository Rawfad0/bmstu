using Domain.InputPorts;
using Domain.OutputPorts;
using Domain.Models;

namespace Domain;

public sealed class SellerService(ISellerRepository sellerRepository) : ISellerService
{
    private readonly ISellerRepository _sellerRepository = sellerRepository;

    public Seller Create(Seller seller)
    {
        ValidateSeller(seller);
        return _sellerRepository.Create(seller);
    }

    public Seller GetById(SellerId sellerId)
    {
        var seller = _sellerRepository.GetById(sellerId);

        if (seller is null)
            throw new IdNotFoundException($"Seller with ID {sellerId.Id} not found.");

        return seller;
    }

    public Seller GetByEmail(string email)
    {
        var seller = _sellerRepository.GetByEmail(email);
        if (seller is null)
            throw new IdNotFoundException($"Seller with Email {email} was not found.");
        return seller;
    }

    public Seller Update(Seller seller, SellerInfo sellerInfo)
    {
        seller.FirstName = sellerInfo.FirstName;
        seller.LastName = sellerInfo.LastName;
        seller.Phone = sellerInfo.Phone;
        seller.Email = sellerInfo.Email;
        seller.BirthDate = sellerInfo.BirthDate;

        ValidateSeller(seller);

        return _sellerRepository.Update(seller);
    }

    private void ValidateSeller(Seller seller)
    {
        if (string.IsNullOrWhiteSpace(seller.FirstName))
            throw new ValidationException("Имя продавца не может быть пустым");
        if (string.IsNullOrWhiteSpace(seller.LastName))
            throw new ValidationException("Фамилия продавца не может быть пустой");
        if (string.IsNullOrWhiteSpace(seller.Email) || !seller.Email.Contains("@"))
            throw new ValidationException("Email продавца некорректен");
        if (seller.BirthDate > DateTime.UtcNow)
            throw new ValidationException("Дата рождения продавца некорректна");
    }
}
