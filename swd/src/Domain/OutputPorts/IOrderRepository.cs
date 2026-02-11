using Domain.Models;

namespace Domain.OutputPorts;

public interface IOrderRepository
{
    public Order Create(Order order);
    public Order? GetById(OrderId orderId);
    public List<Order> GetByCustomerId(CustomerId customerId);
    public List<OrderDetailsDto> GetOrderDetailsByCustomerId(CustomerId customerId);
    public Order Update(Order order);
}
