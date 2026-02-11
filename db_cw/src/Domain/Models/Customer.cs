namespace Domain.Models;

public class Customer
{
    public Guid Id { get; set; }
    public string FirstName { get; set; } = string.Empty;
    public string LastName { get; set; } = string.Empty;
    public string Phone { get; set; } = string.Empty;
    public string Email { get; set; } = string.Empty;
    public DateTime BirthDate { get; set; }
    public DateTime RegisteredAt { get; set; }
    public int Points { get; set; }

    public Customer() { }

    internal Customer(Guid id, string firstName, string lastName, string phone, string email, DateTime birthDate, DateTime registeredAt, int points)
    {
        Id = id;
        FirstName = firstName;
        LastName = lastName;
        Phone = phone;
        Email = email;
        BirthDate = birthDate;
        RegisteredAt = registeredAt;
        Points = points;
    }

    public static Customer Create(Guid id, string firstName, string lastName, string phone, string email, DateTime birthDate, DateTime registeredAt, int points) =>
        new(id, firstName, lastName, phone, email, birthDate, registeredAt, points);
}

public class CustomerId(Guid id)
{
    public Guid Id { get; init; } = id;
}

public class CustomerInfo(string firstName, string lastName, string phone, string email, DateTime birthDate)
{
    public string FirstName { get; init; } = firstName;
    public string LastName { get; init; } = lastName;
    public string Phone { get; init; } = phone;
    public string Email { get; init; } = email;
    public DateTime BirthDate { get; init; } = birthDate;
}

public class CustomerPoints(int points)
{
    public int Points { get; init; } = points;
}
