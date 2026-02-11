namespace Domain;

public class IdNotFoundException : System.Exception
{
    public IdNotFoundException() { }
    public IdNotFoundException(string message) : base(message) { }
    public IdNotFoundException(string message, System.Exception inner) : base(message, inner) { }
}

public class PaymentFailedException : System.Exception
{
    public PaymentFailedException() { }
    public PaymentFailedException(string message) : base(message) { }
    public PaymentFailedException(string message, System.Exception inner) : base(message, inner) { }
}

public class RepositoryException : System.Exception
{
    public RepositoryException() { }
    public RepositoryException(string message) : base(message) { }
    public RepositoryException(string message, System.Exception inner) : base(message, inner) { }
}

public class ValidationException : System.Exception
{
    public ValidationException() { }
    public ValidationException(string message) : base(message) { }
    public ValidationException(string message, System.Exception inner) : base(message, inner) { }
}