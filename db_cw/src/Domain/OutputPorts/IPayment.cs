using Domain.Models;

namespace Domain.OutputPorts;

public interface IPayment
{
    public PaymentResult ProcessPayment(PaymentInfo paymentInfo);
    public RefundResult RefundPayment(PaymentInfo paymentInfo);
}
