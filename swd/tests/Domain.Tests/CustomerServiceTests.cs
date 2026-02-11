using Xunit;
using Moq;
using Domain;
using Domain.OutputPorts;
using Domain.Models;

public class CustomerServiceTests
{
    private readonly Mock<ICustomerRepository> _customerRepoMock;
    private readonly CustomerService _service;

    public CustomerServiceTests()
    {
        _customerRepoMock = new Mock<ICustomerRepository>();
        _service = new CustomerService(_customerRepoMock.Object);
    }

    [Fact]
    public void Create_ShouldCreateCustomer()
    {
        var customerInfo = new CustomerInfo(
            "Ivan",
            "Ivanov",
            "+123456789",
            "ivanov@example.com",
            new DateTime(1990, 1, 1)
        );
        _customerRepoMock.Setup(r => r.Create(It.IsAny<Customer>())).Returns((Customer c) => c);

        var result = _service.Create(customerInfo);

        _customerRepoMock.Verify(
            r => r.Create(It.Is<Customer>(c => c.FirstName == "Ivan" && c.LastName == "Ivanov")),
            Times.Once
        );
        Assert.Equal("Ivan", result.FirstName);
        Assert.Equal("Ivanov", result.LastName);
    }

    [Fact]
    public void GetById_ShouldReturnCustomer()
    {
        var id = Guid.NewGuid();
        var customer = Customer.Create(
            id,
            "Petr",
            "Petrov",
            "+987654321",
            "petrov@example.com",
            new DateTime(1990, 1, 1),
            DateTime.UtcNow,
            10
        );
        var customerId = new CustomerId(id);
        _customerRepoMock.Setup(r => r.GetById(customerId)).Returns(customer);

        var result = _service.GetById(customerId);

        Assert.Equal(customer, result);
    }

    [Fact]
    public void GetById_WhenCustomerNotFound_ShouldThrow()
    {
        var id = Guid.NewGuid();
        var customer = Customer.Create(
            id,
            "Petr",
            "Petrov",
            "+987654321",
            "petrov@example.com",
            new DateTime(1990, 1, 1),
            DateTime.UtcNow,
            10
        );
        var customerId = new CustomerId(id);
        _customerRepoMock.Setup(r => r.GetById(customerId)).Returns((Customer?)null);

        Assert.Throws<IdNotFoundException>(() => _service.GetById(customerId));
    }

    [Fact]
    public void EarnPoints_ShouldIncreasePoints()
    {
        var id = Guid.NewGuid();
        var customer = Customer.Create(
            id,
            "Ivan",
            "Ivanov",
            "+123456789",
            "ivanov@example.com",
            new DateTime(1990, 1, 1),
            DateTime.UtcNow,
            10
        );
        var points = new CustomerPoints(5);
        _customerRepoMock.Setup(r => r.Update(It.IsAny<Customer>())).Returns((Customer c) => c);

        var result = _service.EarnPoints(customer, points);

        _customerRepoMock.Verify(
            r => r.Update(It.Is<Customer>(c => c.Id == id && c.Points == 15)),
            Times.Once
        );
        Assert.Equal(15, result.Points);
    }
}
