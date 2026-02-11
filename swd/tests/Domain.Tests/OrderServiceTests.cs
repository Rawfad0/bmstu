using System;
using Xunit;
using Moq;
using Domain;
using Domain.OutputPorts;
using Domain.Models;
using Microsoft.VisualBasic;

public class OrderServiceTests
{
    private readonly Mock<IOrderRepository> _orderRepoMock;
    private readonly OrderService _service;

    public OrderServiceTests()
    {
        _orderRepoMock = new Mock<IOrderRepository>();
        _service = new OrderService(_orderRepoMock.Object);
    }

    [Fact]
    public void Create_ShouldSaveOrder()
    {
        var customerId = Guid.NewGuid();
        var offerId = Guid.NewGuid();
        var order = Order.Create(Guid.NewGuid(), customerId, offerId, 2);
        _orderRepoMock.Setup(r => r.Create(It.IsAny<Order>())).Returns(order);

        var result = _service.Create(order);

        _orderRepoMock.Verify(
            r => r.Create(It.Is<Order>(o => o.CustomerId == customerId && o.OfferId == offerId && o.Quantity == 2 && o.Status == OrderStatus.Created)),
            Times.Once
        );
        Assert.Equal(order, result);
    }

    [Fact]
    public void GetById_WhenExists_ShouldReturnOrder()
    {
        var id = Guid.NewGuid();
        var order = Order.Create(id, Guid.NewGuid(), Guid.NewGuid(), 1);
        var orderId = new OrderId(id);
        _orderRepoMock.Setup(r => r.GetById(orderId)).Returns(order);

        var result = _service.GetById(orderId);

        Assert.Equal(order, result);
    }

    [Fact]
    public void GetById_WhenNotFound_ShouldThrow()
    {
        var id = Guid.NewGuid();
        var orderId = new OrderId(id);
        _orderRepoMock.Setup(r => r.GetById(orderId)).Returns((Order?)null);

        Assert.Throws<IdNotFoundException>(() => _service.GetById(orderId));
    }

    [Fact]
    public void SetStatusPayed_ShouldUpdateOrderStatus()
    {
        var id = Guid.NewGuid();
        var order = Order.Create(id, Guid.NewGuid(), Guid.NewGuid(), 3);
        var orderId = new OrderId(id);
        _orderRepoMock.Setup(r => r.GetById(orderId)).Returns(order);
        _orderRepoMock.Setup(r => r.Update(It.IsAny<Order>())).Returns((Order o) => o);

        var result = _service.SetStatusPayed(order);

        _orderRepoMock.Verify(
            r => r.Update(It.Is<Order>(o => o.Id == id && o.Status == OrderStatus.Payed)),
            Times.Once
        );
        Assert.Equal(OrderStatus.Payed, result.Status);
    }
}
