using Domain.Models;

namespace Domain.InputPorts;

public interface IRecSysUseCase
{
    public List<Offer> Recommend(CustomerId customerId);
}
