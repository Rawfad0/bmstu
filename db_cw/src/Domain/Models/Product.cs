namespace Domain.Models;

public class Product
{
    public Guid Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Category { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public int RatingCount { get; set; }
    public double AvgRating { get; set; }
    
    public Product() { }
    
    internal Product(Guid id, string name, string category, string description)
    {
        Id = id;
        Name = name;
        Category = category;
        Description = description;
        RatingCount = 0;
        AvgRating = 0.0;
    }

    public static Product Create(Guid id, string name, string category, string description) =>
        new(id, name, category, description);
}

public class ProductId(Guid id)
{
    public Guid Id { get; init; } = id;
}
