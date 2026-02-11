using Domain.Models;

namespace Domain.InputPorts;

public interface IOrderService
{
    public Order Create(Order order);
    public Order SetStatusPayed(Order order);
    public Order SetStatusCancelled(Order order);
    public Order GetById(OrderId orderId);
    public List<Order> GetByCustomerId(CustomerId customerId);
    public List<OrderDetailsDto> GetOrderDetailsByCustomerId(CustomerId customerId);
}
