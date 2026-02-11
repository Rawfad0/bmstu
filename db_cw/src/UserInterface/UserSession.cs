namespace UserInterface;

public class UserSession
{
    public Guid UserId { get; private set; }
    public Role Role { get; private set; }

    public void Login(Role role, Guid userId = default)
    {
        Role = role;
        UserId = userId;
    }

    public void Logout()
    {
        Role = Role.Guest;
        UserId = Guid.Empty;
    }
}

public enum Role
{
    Guest,
    Admin,
    Customer,
    Seller
}
