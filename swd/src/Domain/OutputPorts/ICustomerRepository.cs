using Domain.Models;

namespace Domain.OutputPorts;

public interface ICustomerRepository
{
    public Customer Create(Customer customer);
    public Customer? GetById(CustomerId customerId);
    public Customer? GetByEmail(string email);
    public Customer Update(Customer customer);
}
