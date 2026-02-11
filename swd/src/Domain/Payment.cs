using Domain.Models;

namespace Domain.OutputPorts;

public class Payment: IPayment
{
    public PaymentResult ProcessPayment(PaymentInfo paymentInfo)
    {
        return new PaymentResult(true, "test payment");
    }
    public RefundResult RefundPayment(PaymentInfo paymentInfo)
    {
        return new RefundResult(true, "test payment");
    }
}
