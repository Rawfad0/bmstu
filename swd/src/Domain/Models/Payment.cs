namespace Domain.Models;

public class PaymentInfo(decimal totalAmount, CustomerPoints points, string cardNumber, string expirationDate, string cvc, string paymentMethod)
{
    public decimal TotalAmount { get; init; } = totalAmount;
    public CustomerPoints Points { get; init; } = points;
    public string CardNumber { get; init; } = cardNumber;
    public string ExpirationDate { get; init; } = expirationDate;
    public string Cvc { get; init; } = cvc;
    public string PaymentMethod { get; init; } = paymentMethod;
}

public class PaymentResult(bool isSuccess, string transactionId)
{
    public bool IsSuccess { get; set; } = isSuccess;
    public string TransactionId { get; set; } = transactionId;
}

public class RefundResult(bool isSuccess, string transactionId)
{
    public bool IsSuccess { get; set; } = isSuccess;
    public string TransactionId { get; set; } = transactionId;
}
