using System;
using Xunit;
using Moq;
using Domain;
using Domain.InputPorts;
using Domain.OutputPorts;
using Domain.Models;

public class PaymentUseCaseTests
{
    private readonly Mock<ICustomerRepository> _customerRepoMock;
    private readonly Mock<IOrderRepository> _orderRepoMock;
    private readonly Mock<IOfferRepository> _offerRepoMock;
    private readonly Mock<IPayment> _paymentMock;
    private readonly CustomerService _customerService;
    private readonly OrderService _orderService;
    private readonly OfferService _offerService;
    private readonly PaymentUseCase _useCase;


    public PaymentUseCaseTests()
    {
        _customerRepoMock = new Mock<ICustomerRepository>();
        _orderRepoMock = new Mock<IOrderRepository>();
        _offerRepoMock = new Mock<IOfferRepository>();
        _paymentMock = new Mock<IPayment>();
        _customerService = new CustomerService(_customerRepoMock.Object);
        _orderService = new OrderService(_orderRepoMock.Object);
        _offerService = new OfferService(_offerRepoMock.Object);
        _useCase = new PaymentUseCase(
            _customerService,
            _orderService,
            _offerService,
            _paymentMock.Object
        );
    }

    [Fact]
    public void ProcessPayment_ShouldSucceed()
    {
        var customerId = Guid.NewGuid();
        var orderId = Guid.NewGuid();
        var offerId = Guid.NewGuid();
        var customer = Customer.Create(
            customerId,
            "Ivan",
            "Ivanov",
            "+123456789",
            "ivanov@example.com",
            new DateTime(1990, 1, 1),
            DateTime.UtcNow,
            10
        );
        var order = Order.Create(orderId, customerId, offerId, 3);
        var offer = Offer.Create(offerId, Guid.NewGuid(), Guid.NewGuid(), 100m, 5, 2);
        var paymentInfo = new PaymentInfo
        (
            totalAmount: 100m,
            points: new CustomerPoints(3),
            cardNumber: "1234567890123456",
            expirationDate: "12/30",
            cvc: "123",
            paymentMethod: "VISA"
        );
        var paymentResult = new PaymentResult(isSuccess: true, transactionId: "123");
        var customerIdDto = new CustomerId(customerId);
        var orderIdDto = new OrderId(orderId);
        var offerIdDto = new OfferId(offerId);
        _customerRepoMock.Setup(r => r.GetById(customerIdDto)).Returns(customer);
        _customerRepoMock.Setup(r => r.Update(It.IsAny<Customer>())).Returns((Customer c) => c);
        _orderRepoMock.Setup(r => r.GetById(orderIdDto)).Returns(order);
        _orderRepoMock.Setup(r => r.Update(It.IsAny<Order>())).Returns((Order o) => o);
        _offerRepoMock.Setup(r => r.GetById(offerIdDto)).Returns(offer);
        _offerRepoMock.Setup(r => r.Update(It.IsAny<Offer>())).Returns((Offer o) => o);
        _paymentMock.Setup(p => p.ProcessPayment(paymentInfo)).Returns(paymentResult);

        var result = _useCase.ProcessPayment(customer, order, offer, paymentInfo);

        Assert.True(result.IsSuccess);
        Assert.Equal("123", result.TransactionId);
        _paymentMock.Verify(p => p.ProcessPayment(paymentInfo), Times.Once);
        _customerRepoMock.Verify(r => r.Update(It.Is<Customer>(c => c.Points == 8)), Times.Exactly(2));
        _orderRepoMock.Verify(r => r.Update(It.Is<Order>(o => o.Status == OrderStatus.Payed)), Times.Once);
        _offerRepoMock.Verify(r => r.Update(It.Is<Offer>(o => o.Quantity == 2)), Times.Once);
    }

    [Fact]
    public void ProcessPayment_WhenHasNotEnoughPoints_ShouldThrow()
    {
        var customerId = Guid.NewGuid();
        var orderId = Guid.NewGuid();
        var offerId = Guid.NewGuid();
        var customer = Customer.Create(
            customerId,
            "Ivan",
            "Ivanov",
            "+123456789",
            "ivanov@example.com",
            new DateTime(1990, 1, 1),
            DateTime.UtcNow,
            10
        );
        var order = Order.Create(orderId, customerId, offerId, 2);
        var offer = Offer.Create(offerId, Guid.NewGuid(), Guid.NewGuid(), 100m, 5, 2);
        var paymentInfo = new PaymentInfo
        (
            totalAmount: 100m,
            points: new CustomerPoints(15),
            cardNumber: "1234567890123456",
            expirationDate: "12/30",
            cvc: "123",
            paymentMethod: "VISA"
        );
        var customerIdDto = new CustomerId(customerId);
        var orderIdDto = new OrderId(orderId);
        var offerIdDto = new OfferId(offerId);
        _customerRepoMock.Setup(r => r.GetById(customerIdDto)).Returns(customer);
        _orderRepoMock.Setup(r => r.GetById(orderIdDto)).Returns(order);

        Assert.Throws<ArgumentException>(() =>
            _useCase.ProcessPayment(customer, order, offer, paymentInfo)
        );

        _paymentMock.Verify(p => p.ProcessPayment(It.IsAny<PaymentInfo>()), Times.Never);
        _customerRepoMock.Verify(r => r.Update(It.IsAny<Customer>()), Times.Never);
        _orderRepoMock.Verify(r => r.Update(It.IsAny<Order>()), Times.Never);
        _offerRepoMock.Verify(r => r.Update(It.IsAny<Offer>()), Times.Never);
    }

    [Fact]
    public void ProcessPayment_WhenNotEnoughOfferQuantity_ShouldThrow()
    {
        var customerId = Guid.NewGuid();
        var orderId = Guid.NewGuid();
        var offerId = Guid.NewGuid();
        var customer = Customer.Create(
            customerId,
            "Ivan",
            "Ivanov",
            "+123456789",
            "ivanov@example.com",
            new DateTime(1990, 1, 1),
            DateTime.UtcNow,
            10
        );
        var order = Order.Create(orderId, customerId, offerId, 5);
        var offer = Offer.Create(offerId, Guid.NewGuid(), Guid.NewGuid(), 100m, 2, 2);
        var paymentInfo = new PaymentInfo
        (
            totalAmount: 100m,
            points: new CustomerPoints(0),
            cardNumber: "1234567890123456",
            expirationDate: "12/30",
            cvc: "123",
            paymentMethod: "VISA"
        );
        var customerIdDto = new CustomerId(customerId);
        var orderIdDto = new OrderId(orderId);
        var offerIdDto = new OfferId(offerId);
        _customerRepoMock.Setup(r => r.GetById(customerIdDto)).Returns(customer);
        _orderRepoMock.Setup(r => r.GetById(orderIdDto)).Returns(order);

        Assert.Throws<ArgumentException>(() =>
            _useCase.ProcessPayment(customer, order, offer, paymentInfo)
        );

        _paymentMock.Verify(p => p.ProcessPayment(It.IsAny<PaymentInfo>()), Times.Never);
        _customerRepoMock.Verify(r => r.Update(It.IsAny<Customer>()), Times.Exactly(2));
        _orderRepoMock.Verify(r => r.Update(It.IsAny<Order>()), Times.Never);
        _offerRepoMock.Verify(r => r.Update(It.IsAny<Offer>()), Times.Never);
    }

    [Fact]
    public void ProcessPayment_WhenFailedPayment_ShouldThrow()
    {
        var customerId = Guid.NewGuid();
        var orderId = Guid.NewGuid();
        var offerId = Guid.NewGuid();
        var customer = Customer.Create(
            customerId,
            "Ivan",
            "Ivanov",
            "+123456789",
            "ivanov@example.com",
            new DateTime(1990, 1, 1),
            DateTime.UtcNow,
            10
        );
        var offer = Offer.Create(offerId, Guid.NewGuid(), Guid.NewGuid(), 100m, 5, 2);
        var order = Order.Create(orderId, customerId, offerId, 3);
        var paymentInfo = new PaymentInfo
        (
            totalAmount: 100m,
            points: new CustomerPoints(3),
            cardNumber: "1234567890123456",
            expirationDate: "12/30",
            cvc: "123",
            paymentMethod: "VISA"
        );
        var paymentResult = new PaymentResult(isSuccess: false, transactionId: "123");
        var customerIdDto = new CustomerId(customerId);
        var orderIdDto = new OrderId(orderId);
        var offerIdDto = new OfferId(offerId);
        _customerRepoMock.Setup(r => r.GetById(customerIdDto)).Returns(customer);
        _customerRepoMock.Setup(r => r.Update(It.IsAny<Customer>())).Returns((Customer c) => c);
        _orderRepoMock.Setup(r => r.GetById(orderIdDto)).Returns(order);
        _orderRepoMock.Setup(r => r.Update(It.IsAny<Order>())).Returns((Order o) => o);
        _offerRepoMock.Setup(r => r.GetById(offerIdDto)).Returns(offer);
        _offerRepoMock.Setup(r => r.Update(It.IsAny<Offer>())).Returns((Offer o) => o);
        _paymentMock.Setup(p => p.ProcessPayment(paymentInfo)).Returns(paymentResult);

        Assert.Throws<PaymentFailedException>(() => _useCase.ProcessPayment(customer, order, offer, paymentInfo));

        _paymentMock.Verify(p => p.ProcessPayment(paymentInfo), Times.Once);
        _customerRepoMock.Verify(r => r.Update(It.Is<Customer>(c => c.Points == 10)), Times.Exactly(2));
        _offerRepoMock.Verify(r => r.Update(It.Is<Offer>(o => o.Quantity == 5)), Times.Exactly(2));
        _orderRepoMock.Verify(r => r.Update(It.Is<Order>(o => o.Status == OrderStatus.Created)), Times.Never);
    }
}
