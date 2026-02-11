using Domain.Models;

namespace WebApi.WebDTO;

public class CustomerInfoWDTO(string firstName, string lastName, string phone, string email, DateTime birthDate)
{
    public string FirstName { get; init; } = firstName;
    public string LastName { get; init; } = lastName;
    public string Phone { get; init; } = phone;
    public string Email { get; init; } = email;
    public DateTime BirthDate { get; init; } = birthDate;

    public CustomerInfo WDTOtoDDTO()
    {
        var customerInfo = new CustomerInfo(FirstName, LastName, Phone, Email, BirthDate);
        return customerInfo;
    }
}