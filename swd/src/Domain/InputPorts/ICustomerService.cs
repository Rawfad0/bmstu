using Domain.Models;

namespace Domain.InputPorts;

public interface ICustomerService
{
    public Customer Create(CustomerInfo customerInfo);
    public Customer GetById(CustomerId customerId);
    public Customer GetByEmail(string email);
    public Customer UpdateInfo(Customer customer, CustomerInfo customerInfo);
    public Customer EarnPoints(Customer customer, CustomerPoints customerPoints);
    public Customer SpendPoints(Customer customer, CustomerPoints customerPoints);
    public Customer CompensateSpendPoints(Customer customer, CustomerPoints customerPoints);
    public Customer CompensateEarnPoints(Customer customer, CustomerPoints customerPoints);
}
