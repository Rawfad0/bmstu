namespace Domain.Models;

public class Store
{
    public Guid Id { get; set; }
    public Guid OwnerSellerId { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Ogrn { get; set; } = string.Empty;
    public int RatingCount { get; set; }
    public double AvgRating { get; set; }

    public Store() { }

    internal Store(Guid id, Guid ownerSellerId, string name, string ogrn)
    {
        Id = id;
        OwnerSellerId = ownerSellerId;
        Name = name;
        Ogrn = ogrn;
        RatingCount = 0;
        AvgRating = 0.0;
    }

    public static Store Create(Guid id, Guid ownerSellerId, string name, string ogrn) =>
        new(id, ownerSellerId, name, ogrn);
}

public class StoreId(Guid id)
{
    public Guid Id { get; init; } = id;
}

public class StoreInfo(string name, string ogrn)
{
    public string Name { get; init; } = name;
    public string Ogrn { get; init; } = ogrn;
}
