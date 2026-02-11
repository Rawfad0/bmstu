using Domain.InputPorts;
using Domain.OutputPorts;
using Domain.Models;

namespace Domain;

public sealed class CustomerService(ICustomerRepository customerRepository) : ICustomerService
{
    private readonly ICustomerRepository _customerRepository = customerRepository;

    public Customer Create(CustomerInfo customerInfo)
    {
        var customer = new Customer
        {
            Id = Guid.NewGuid(),
            FirstName = customerInfo.FirstName,
            LastName = customerInfo.LastName,
            Phone = customerInfo.Phone,
            Email = customerInfo.Email,
            BirthDate = customerInfo.BirthDate,
            RegisteredAt = DateTime.UtcNow,
            Points = 0
        };
        ValidateCustomer(customer);
        return _customerRepository.Create(customer);
    }

    public Customer GetById(CustomerId customerId)
    {
        var customer = _customerRepository.GetById(customerId);
        if (customer is null)
            throw new IdNotFoundException($"Customer with ID {customerId} was not found.");
        return customer;
    }

    public Customer GetByEmail(string email)
    {
        var customer = _customerRepository.GetByEmail(email);
        if (customer is null)
            throw new IdNotFoundException($"Customer with Email {email} was not found.");
        return customer;
    }

    public Customer UpdateInfo(Customer customer, CustomerInfo customerInfo)
    {
        customer.FirstName = customerInfo.FirstName;
        customer.LastName = customerInfo.LastName;
        customer.Phone = customerInfo.Phone;
        customer.Email = customerInfo.Email;
        customer.BirthDate = customerInfo.BirthDate;

        ValidateCustomer(customer);

        return _customerRepository.Update(customer);
    }

    public Customer EarnPoints(Customer customer, CustomerPoints customerPoints)
    {
        if (customerPoints.Points < 0)
            throw new ArgumentException("The number of points earned must be greater than zero.");
        customer.Points += customerPoints.Points;

        return _customerRepository.Update(customer);
    }

    public Customer SpendPoints(Customer customer, CustomerPoints customerPoints)
    {
        if (customer.Points < customerPoints.Points)
            throw new ArgumentException("The number of points spent must be less than the number of customer's points.");
        customer.Points -= customerPoints.Points;

        return _customerRepository.Update(customer);
    }

    public Customer CompensateSpendPoints(Customer customer, CustomerPoints customerPoints)
    {
        if (customerPoints.Points < 0)
            throw new ArgumentException("The number of points earned must be greater than zero.");
        customer.Points += customerPoints.Points;

        return _customerRepository.Update(customer);
    }

    public Customer CompensateEarnPoints(Customer customer, CustomerPoints customerPoints)
    {
        if (customer.Points < customerPoints.Points)
            throw new ArgumentException($"The number of points spent {customerPoints.Points} must be less than the number of customer's point {customer.Points}.");
        customer.Points -= customerPoints.Points;

        return _customerRepository.Update(customer);
    }

    private void ValidateCustomer(Customer customer)
    {
        if (string.IsNullOrWhiteSpace(customer.FirstName))
            throw new ValidationException("Имя клиента не может быть пустым");
        if (string.IsNullOrWhiteSpace(customer.LastName))
            throw new ValidationException("Фамилия клиента не может быть пустой");
        if (string.IsNullOrWhiteSpace(customer.Email) || !customer.Email.Contains("@"))
            throw new ValidationException("Email клиента некорректен");
        if (customer.BirthDate > DateTime.UtcNow)
            throw new ValidationException("Дата рождения клиента некорректна");
        if (customer.Points < 0)
            throw new ValidationException("Баллы клиента не могут быть отрицательными");
    }
}
