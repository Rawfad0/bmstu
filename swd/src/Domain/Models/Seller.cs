namespace Domain.Models;

public class Seller
{
    public Guid Id { get; set; }
    public string FirstName { get; set; } = string.Empty;
    public string LastName { get; set; } = string.Empty;
    public string Phone { get; set; } = string.Empty;
    public string Email { get; set; } = string.Empty;
    public DateTime BirthDate { get; set; }

    public Seller() { }

    internal Seller(Guid id, string firstName, string lastName, string phone, string email, DateTime birthDate)
    {
        Id = id;
        FirstName = firstName;
        LastName = lastName;
        Phone = phone;
        Email = email;
        BirthDate = birthDate;
    }

    public static Seller Create(Guid id, string firstName, string lastName, string phone, string email, DateTime birthDate) =>
        new(id, firstName, lastName, phone, email, birthDate);
}

public class SellerId(Guid id)
{
    public Guid Id { get; init; } = id;
}

public class SellerInfo(string firstName, string lastName, string phone, string email, DateTime birthDate)
{
    public string FirstName { get; init; } = firstName;
    public string LastName { get; init; } = lastName;
    public string Phone { get; init; } = phone;
    public string Email { get; init; } = email;
    public DateTime BirthDate { get; init; } = birthDate;
}
