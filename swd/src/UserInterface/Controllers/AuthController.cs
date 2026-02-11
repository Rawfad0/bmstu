using UserInterface;
using Domain.InputPorts;
using Domain.OutputPorts;
using Domain;
using Domain.Models;
using Microsoft.Extensions.Logging;

namespace UserInterface.Controllers;

public class AuthController
{
    private readonly UserSession _session;
    private readonly ICustomerService _customerService;
    private readonly ISellerService _sellerService;
    private readonly ILogger _logger;

    public AuthController(
        UserSession session,
        ICustomerService customerService,
        ISellerService sellerService,
        ILogger loger)
    {
        _session = session;
        _customerService = customerService;
        _sellerService = sellerService;
        _logger = loger;
    }

    public void Login()
    {
        Console.Clear();
        Console.WriteLine("=== Вход ===");
        Console.WriteLine("1. Вход как покупатель");
        Console.WriteLine("2. Вход как продавец");
        Console.WriteLine("3. Вход как администратор");
        Console.WriteLine("9. Выйти");
        Console.WriteLine("0. Выход из программы");
        var choice = Console.ReadLine();
        switch (choice)
        {
            case "1":
                LoginAsCustomer();
                break;
            case "2":
                LoginAsSeller();
                break;
            case "3":
                LoginAsAdmin();
                break;
            case "9":
                break;
            case "0":
                Environment.Exit(0);
                break;
            default:
                Console.WriteLine("Неверный выбор.");
                break;
        }
    }

    public void LoginAsCustomer()
    {
        Console.WriteLine("Введите email:");
        var email = Console.ReadLine();

        if (string.IsNullOrWhiteSpace(email))
        {
            Console.WriteLine("Email не может быть пустым.");
            return;
        }

        try
        {
            var customer = _customerService.GetByEmail(email);
            _session.Login(Role.Customer, customer.Id);
            Console.WriteLine("Вы успешно вошли как покупатель");
            _logger.LogInformation("Успешный вход покупателя Id={CustomerId}", customer.Id);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка входа: {ex.Message}");
            _logger.LogError(ex, "Ошибка входа покупателя с email={Email}", email);
        }
    }

    public void LoginAsSeller()
    {
        Console.WriteLine("Введите email:");
        var email = Console.ReadLine();

        if (string.IsNullOrWhiteSpace(email))
        {
            Console.WriteLine("Email не может быть пустым.");
            return;
        }

        try
        {
            var seller = _sellerService.GetByEmail(email);
            _session.Login(Role.Seller, seller.Id);
            Console.WriteLine("Вы успешно вошли как продавец");
            _logger.LogInformation("Успешный вход продавца Id={SellerId}", seller.Id);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка входа: {ex.Message}");
            _logger.LogError(ex, "Ошибка входа продавца с email={Email}", email);
        }
    }

    public void LoginAsAdmin()
    {
        _session.Login(Role.Admin, Guid.Empty);
        Console.WriteLine("Вы успешно вошли как администратор");
        _logger.LogInformation("Успешный вход администратора");
    }

    public void Register()
    {
        Console.Clear();
        Console.WriteLine("=== Регистрация ===");
        Console.WriteLine("1. Регистрация покупателя");
        Console.WriteLine("2. Регистрация продавца");
        Console.WriteLine("9. Выйти");
        Console.WriteLine("0. Выход из программы");
        var choice = Console.ReadLine();
        switch (choice)
        {
            case "1":
                RegisterCustomer();
                break;
            case "2":
                RegisterSeller();
                break;
            case "9":
                break;
            case "0":
                Environment.Exit(0);
                break;
            default:
                Console.WriteLine("Неверный выбор.");
                break;
        }
    }

    private (string lastName, string firstName, string phone, string email, DateTime birthDate)? AskRegistrationData()
    {
        Console.WriteLine("Введите фамилию:");
        var lastName = Console.ReadLine();
        Console.WriteLine("Введите имя:");
        var firstName = Console.ReadLine();
        Console.WriteLine("Введите номер телефона:");
        var phone = Console.ReadLine();
        Console.WriteLine("Введите email:");
        var email = Console.ReadLine();

        if (string.IsNullOrWhiteSpace(lastName) ||
            string.IsNullOrWhiteSpace(firstName) ||
            string.IsNullOrWhiteSpace(phone) ||
            string.IsNullOrWhiteSpace(email))
        {
            Console.WriteLine("Все поля должны быть заполнены.");
            return null;
        }

        Console.WriteLine("Введите дату рождения (гггг-мм-дд):");
        if (!DateTime.TryParse(Console.ReadLine(), out var birthDate))
        {
            Console.WriteLine("Некорректная дата.");
            return null;
        }

        return (lastName, firstName, phone, email, birthDate);
    }

    public void RegisterCustomer()
    {
        var data = AskRegistrationData();
        if (data == null) return;

        try
        {
            var customerInfo = new CustomerInfo(
                data.Value.lastName,
                data.Value.firstName,
                data.Value.phone,
                data.Value.email,
                data.Value.birthDate
            );

            var createdCustomer = _customerService.Create(customerInfo);
            _session.Login(Role.Customer, createdCustomer.Id);
            Console.WriteLine("Регистрация успешна.");
            _logger.LogInformation("Успешная регистрация покупателя Id={CustomerId}", createdCustomer.Id);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка регистрации: {ex.Message}");
            _logger.LogError(ex, "Ошибка регистрации покупателя с email={Email}", data?.email);
        }

    }

    public void RegisterSeller()
    {
        var data = AskRegistrationData();
        if (data == null) return;

        try
        {
            var sellerInfo = new SellerInfo(
                data.Value.lastName,
                data.Value.firstName,
                data.Value.phone,
                data.Value.email,
                data.Value.birthDate
            );

            var createdSeller = _sellerService.Create(sellerInfo);
            _session.Login(Role.Seller, createdSeller.Id);
            Console.WriteLine("Регистрация успешна.");
            _logger.LogInformation("Успешная регистрация продавца Id={SellerId}", createdSeller.Id);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка регистрации: {ex.Message}");
            _logger.LogError(ex, "Ошибка регистрации продавца с email={Email}", data?.email);
        }
    }
}
