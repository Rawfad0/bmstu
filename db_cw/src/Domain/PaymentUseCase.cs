using Domain.InputPorts;
using Domain.OutputPorts;
using Domain.Models;

namespace Domain;

public class PaymentUseCase(ICustomerService customerService, IOrderService orderService, IOfferService offerService, IPayment payment) : IPaymentUseCase
{
    private readonly ICustomerService _customerService = customerService;
    private readonly IOrderService _orderService = orderService;
    private readonly IOfferService _offerService = offerService;
    private readonly IPayment _payment = payment;
    public PaymentResult ProcessPayment(Customer customer, Order order, Offer offer, PaymentInfo paymentInfo)
    {
        var compensationStack = new Stack<Action>();
        try
        {
            _customerService.SpendPoints(customer, paymentInfo.Points);
            compensationStack.Push(() => _customerService.CompensateSpendPoints(customer, paymentInfo.Points));

            _offerService.DecrQuantity(offer, order.Quantity);
            compensationStack.Push(() => _offerService.IncrQuantity(offer, order.Quantity));

            var paymentResult = _payment.ProcessPayment(paymentInfo);
            if (paymentResult.IsSuccess is false)
                throw new PaymentFailedException("Payment failed.");
            compensationStack.Push(() => _payment.RefundPayment(paymentInfo));

            _orderService.SetStatusPayed(order);
            compensationStack.Push(() => _orderService.SetStatusCancelled(order));

            var earnedPoints = new CustomerPoints((int)paymentInfo.TotalAmount / 100);
            _customerService.EarnPoints(customer, earnedPoints);
            compensationStack.Push(() => _customerService.CompensateEarnPoints(customer, earnedPoints));

            return paymentResult;
        }
        catch
        {
            while (compensationStack.Count > 0)
            {
                try
                {
                    compensationStack.Pop().Invoke();
                }
                catch
                {
                    // log (lab6?)
                }
            }
            throw;
        }
    }
}
