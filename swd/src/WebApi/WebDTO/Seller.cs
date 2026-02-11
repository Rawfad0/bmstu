using Domain.Models;

namespace WebApi.WebDTO;

public class SellerInfoWDTO(string firstName, string lastName, string phone, string email, DateTime birthDate)
{
    public string FirstName { get; init; } = firstName;
    public string LastName { get; init; } = lastName;
    public string Phone { get; init; } = phone;
    public string Email { get; init; } = email;
    public DateTime BirthDate { get; init; } = birthDate;

    public SellerInfo WDTOtoDDTO()
    {
        var sellerInfo = new SellerInfo(FirstName, LastName, Phone, Email, BirthDate);
        return sellerInfo;
    }
}