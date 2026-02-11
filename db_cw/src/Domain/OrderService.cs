using Domain.InputPorts;
using Domain.OutputPorts;
using Domain.Models;

namespace Domain;

public sealed class OrderService(IOrderRepository orderRepository) : IOrderService
{
    private readonly IOrderRepository _orderRepository = orderRepository;

    public Order Create(Order order)
    {
        ValidateOrder(order);
        return _orderRepository.Create(order);
    }

    public Order GetById(OrderId orderId)
    {
        var order = _orderRepository.GetById(orderId);
        if (order is null)
            throw new IdNotFoundException($"Order with ID {orderId.Id} was not found.");

        return order;
    }

    public Order SetStatusPayed(Order order)
    {
        order.Status = OrderStatus.Payed;
        order = _orderRepository.Update(order);

        return order;
    }

    public Order SetStatusCancelled(Order order)
    {
        order.Status = OrderStatus.Cancelled;
        order = _orderRepository.Update(order);

        return order;
    }

    public List<Order> GetByCustomerId(CustomerId customerId)
    {
        return _orderRepository.GetByCustomerId(customerId);
    }

    private void ValidateOrder(Order order)
    {
        if (order.CustomerId == Guid.Empty)
            throw new ValidationException("CustomerId не может быть пустым");
        if (order.OfferId == Guid.Empty)
            throw new ValidationException("OfferId не может быть пустым");
        if (order.Quantity <= 0)
            throw new ValidationException("Количество должно быть больше нуля");
    }
    public List<OrderDetailsDto> GetOrderDetailsByCustomerId(CustomerId customerId)
    {
        return _orderRepository.GetOrderDetailsByCustomerId(customerId);
    }
}
