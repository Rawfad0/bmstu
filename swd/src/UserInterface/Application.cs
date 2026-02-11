using System;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Logging;
using DataAccess;
using DataAccess.Repositories;
using Domain.InputPorts;
using Domain.OutputPorts;
using Domain;
using UserInterface.Controllers;

namespace UserInterface;

public class Application
{
    private Action _menu;
    private readonly UserSession _session;

    private readonly AuthController _authController;
    private readonly CustomerController _customerController;
    private readonly SellerController _sellerController;
    private readonly AdminController _adminController;

    public Application(string connectionString, IConfiguration configuration, ILogger logger, double priceCoef, double deliveryTimeCoef)
    {
        _session = new UserSession();

        var context = new DapperContext(connectionString);
        var customerRepo = new CustomerRepository(context);
        var favoriteRepo = new FavoriteRepository(context);
        var offerRepo = new OfferRepository(context);
        var orderRepo = new OrderRepository(context);
        var productRepo = new ProductRepository(context);
        var sellerRepo = new SellerRepository(context);
        var storeRepo = new StoreRepository(context);
        var reviewRepo = new ReviewRepository(context);
        var payment = new Payment();

        var customerService = new CustomerService(customerRepo);
        var favoriteService = new FavoriteService(favoriteRepo);
        var offerService = new OfferService(offerRepo);
        var orderService = new OrderService(orderRepo);
        var productService = new ProductService(productRepo);
        var sellerService = new SellerService(sellerRepo);
        var storeService = new StoreService(storeRepo);
        var recSysUseCase = new RecSysUseCase(offerService, favoriteService, priceCoef, deliveryTimeCoef);
        var paymentUseCase = new PaymentUseCase(customerService, orderService, offerService, payment);
        var reviewService = new ReviewService(reviewRepo);

        _authController = new AuthController(
            _session,
            customerService,
            sellerService,
            logger
        );
        _customerController = new CustomerController(
            customerService,
            favoriteService,
            offerService,
            orderService,
            productService,
            storeService,
            recSysUseCase,
            paymentUseCase,
            reviewService,
            logger
        );
        _sellerController = new SellerController(
            sellerService,
            storeService,
            offerService,
            productService,
            logger
        );
        _adminController = new AdminController(
            productService,
            offerService,
            storeService,
            logger
        );

        _menu = GuestMenu;
    }

    public void Run()
    {
        // Console.Clear();
        while (true)
        {
            Console.Clear();
            _menu = _session.Role switch
            {
                Role.Admin => AdminMenu,
                Role.Guest => GuestMenu,
                Role.Customer => CustomerMenu,
                Role.Seller => SellerMenu,
                _ => GuestMenu
            };
            _menu();
            Console.WriteLine("Нажмите любую клавишу для продолжения...");
            Console.ReadKey();
        }
    }

    private void GuestMenu()
    {
        Console.WriteLine("=== Гостевое меню ===");
        Console.WriteLine("1. Вход");
        Console.WriteLine("2. Регистрация");
        Console.WriteLine("0. Выход из программы");

        var choice = Console.ReadLine();
        switch (choice)
        {
            case "1":
                _authController.Login();
                break;
            case "2":
                _authController.Register();
                break;
            case "0":
                Environment.Exit(0);
                break;
        }
    }

    private void CustomerMenu()
    {
        Console.WriteLine("=== Меню покупателя ===");
        Console.WriteLine("1. Поиск товаров");
        Console.WriteLine("2. Рекомендации");
        Console.WriteLine("3. Заказы");
        Console.WriteLine("4. Избранное");
        Console.WriteLine("5. Профиль");
        Console.WriteLine("9. Выйти");
        Console.WriteLine("0. Выход из программы");

        var choice = Console.ReadLine();
        switch (choice)
        {
            case "1":
                _customerController.SearchProducts(_session);
                break;
            case "2":
                _customerController.ShowRecommendations(_session);
                break;
            case "3":
                _customerController.ListOrders(_session);
                break;
            case "4":
                _customerController.ListFavorites(_session);
                break;
            case "5":
                _customerController.ShowProfile(_session);
                break;
            case "9":
                _session.Logout();
                break;
            case "0":
                Environment.Exit(0);
                break;
            default:
                Console.WriteLine("Неверный выбор.");
                break;
        }
    }

    private void SellerMenu()
    {
        Console.WriteLine("=== Меню продавца ===");
        Console.WriteLine("1. Профиль");
        Console.WriteLine("2. Магазины");
        Console.WriteLine("3. Создать магазин");
        Console.WriteLine("9. Выйти");
        Console.WriteLine("0. Выход из программы");

        var choice = Console.ReadLine();
        switch (choice)
        {
            case "1":
                _sellerController.ShowProfile(_session);
                break;
            case "2":
                _sellerController.ListStores(_session);
                break;
            case "3":
                _sellerController.AddStore(_session);
                break;
            // case "3":
            //     _sellerController.EditStore(_session);
            //     break;
            case "9":
                _session.Logout();
                break;
            case "0":
                Environment.Exit(0);
                break;
            default:
                Console.WriteLine("Неверный выбор.");
                break;
        }
    }

    private void AdminMenu()
    {
        Console.WriteLine("=== Меню администратора ===");
        Console.WriteLine("1. Добавить товар");
        Console.WriteLine("2. Изменить информацию о товаре");
        Console.WriteLine("3. Изменить информацию о предложении");
        Console.WriteLine("4. Изменить информацию о магазине");
        Console.WriteLine("9. Выйти");
        Console.WriteLine("0. Выход из программы");

        var choice = Console.ReadLine();
        switch (choice)
        {
            case "1":
                _adminController.AddProduct();
                break;
            case "2":
                _adminController.EditProduct();
                break;
            case "3":
                _adminController.EditOffer();
                break;
            case "4":
                _adminController.EditStore();
                break;
            case "9":
                _session.Logout();
                break;
            case "0":
                Environment.Exit(0);
                break;
            default:
                Console.WriteLine("Неверный выбор.");
                break;
        }
    }
}
