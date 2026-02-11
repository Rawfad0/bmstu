using Domain.Models;

namespace Domain.InputPorts;

public interface IPaymentUseCase
{
    public PaymentResult ProcessPayment(Customer customer, Order order, Offer offer, PaymentInfo paymentInfo);
}