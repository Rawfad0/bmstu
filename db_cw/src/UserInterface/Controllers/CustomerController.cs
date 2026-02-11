using System;
using Domain.InputPorts;
using Domain.OutputPorts;
using Domain;
using Domain.Models;
using UserInterface;
using Microsoft.Extensions.Logging;
using DataAccess.Repositories;

namespace UserInterface.Controllers;

public class CustomerController
{
    private readonly ICustomerService _customerService;
    private readonly IFavoriteService _favoriteService;
    private readonly IOfferService _offerService;
    private readonly IOrderService _orderService;
    private readonly IProductService _productService;
    private readonly IStoreService _storeService;
    private readonly IRecSysUseCase _recSysUseCase;
    private readonly IPaymentUseCase _paymentUseCase;
    private readonly IReviewService _reviewService;
    private readonly ILogger _logger;

    public CustomerController(
        ICustomerService customerService,
        IFavoriteService favoriteService,
        IOfferService offerService,
        IOrderService orderService,
        IProductService productService,
        IStoreService storeService,
        IRecSysUseCase recSysUseCase,
        IPaymentUseCase paymentUseCase,
        IReviewService reviewService,
        ILogger logger)
    {
        _customerService = customerService;
        _favoriteService = favoriteService;
        _offerService = offerService;
        _orderService = orderService;
        _productService = productService;
        _storeService = storeService;
        _recSysUseCase = recSysUseCase;
        _paymentUseCase = paymentUseCase;
        _reviewService = reviewService;
        _logger = logger;
    }

    public void ShowProfile(UserSession session)
    {
        try
        {
            var customer = _customerService.GetById(new CustomerId(session.UserId));
            Console.Clear();
            Console.WriteLine("=== Профиль покупателя ===");
            Console.WriteLine($"Имя: {customer.FirstName}");
            Console.WriteLine($"Фамилия: {customer.LastName}");
            Console.WriteLine($"Email: {customer.Email}");
            Console.WriteLine($"Телефон: {customer.Phone}");
            Console.WriteLine($"Баллы: {customer.Points}");
            _logger.LogInformation("Пользователь {UserId} просмотрел профиль", session.UserId);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при получении профиля: {ex.Message}");
            _logger.LogInformation("Ошибка при получении профиля пользователя {UserId}", session.UserId);
        }
    }

    public void ListFavorites(UserSession session)
    {
        try
        {
            var favorites = _favoriteService.GetFavoriteDetailsByCustomerId(new CustomerId(session.UserId));
            _logger.LogInformation("Покупатель {CustomerId} просматривает избранное, найдено {Count} элементов", session.UserId, favorites.Count);

            Console.Clear();
            Console.WriteLine("=== Избранное ===");
            if (favorites.Count == 0)
            {
                Console.WriteLine("Список избранного пока пуст");
                return;
            }

            for (int i = 0; i < favorites.Count; i++)
            {
                var f = favorites[i];
                Console.WriteLine($"{i + 1}. {f.ProductName} — {f.ProductDescription}");
            }

            Console.WriteLine();
            Console.WriteLine("1. Удалить из избранного");
            Console.WriteLine("0. Назад");
            Console.Write("Ваш выбор: ");
            var choice = Console.ReadLine();

            switch (choice)
            {
                case "1":
                    RemoveFromFavorites(session, favorites);
                    break;
                case "0":
                    return;
                default:
                    Console.WriteLine("Неверный выбор.");
                    break;
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при получении избранного: {ex.Message}");
            _logger.LogError(ex, "Ошибка при получении избранного покупателя {CustomerId}", session.UserId);
        }
    }

    private void RemoveFromFavorites(UserSession session, List<FavoriteDetailsDto> favorites)
    {
        Console.Write("Введите номер элемента для удаления: ");
        if (!int.TryParse(Console.ReadLine(), out int index) || index < 1 || index > favorites.Count)
        {
            Console.WriteLine("Некорректный номер.");
            _logger.LogWarning("Покупатель {CustomerId} ввел некорректный номер избранного для удаления", session.UserId);
            return;
        }

        var favorite = favorites[index - 1];

        try
        {
            _favoriteService.DeleteById(new FavoriteId(favorite.FavoriteId));
            Console.WriteLine("Элемент успешно удален из избранного.");
            _logger.LogInformation("Покупатель {CustomerId} удалил товар {ProductId} ({ProductName}) из избранного", session.UserId, favorite.ProductId, favorite.ProductName);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при удалении из избранного: {ex.Message}");
            _logger.LogError(ex, "Ошибка при удалении товара {ProductId} из избранного покупателем {CustomerId}", favorite.ProductId, session.UserId);
        }
    }

    public void SearchProducts(UserSession session)
    {
        Console.WriteLine("Введите название товара для поиска:");
        var nameInput = Console.ReadLine();

        if (string.IsNullOrWhiteSpace(nameInput))
        {
            Console.WriteLine("Название товара не может быть пустым.");
            _logger.LogWarning("Покупатель {CustomerId} ввел пустое название для поиска", session.UserId);
            return;
        }

        try
        {
            var products = _productService.GetByName(nameInput.Trim());
            _logger.LogInformation("Покупатель {CustomerId} ищет товары с названием '{SearchName}', найдено {Count}", session.UserId, nameInput.Trim(), products.Count);

            if (products.Count == 0)
            {
                Console.WriteLine("Товары не найдены.");
                return;
            }

            while (true)
            {
                Console.Clear();
                Console.WriteLine("=== Результаты поиска ===");
                for (int i = 0; i < products.Count; i++)
                    Console.WriteLine($"{i + 1}. {products[i].Name} - {products[i].Description}");

                Console.WriteLine("Меню:");
                Console.WriteLine("1. Перейти к товару");
                Console.WriteLine("2. Добавить товар в избранное");
                Console.WriteLine("3. Назад");

                var choice = Console.ReadLine();
                switch (choice)
                {
                    case "1":
                        _logger.LogInformation("Покупатель {CustomerId} выбрал просмотр товара из результатов поиска", session.UserId);
                        ShowProduct(session, products);
                        break;
                    case "2":
                        _logger.LogInformation("Покупатель {CustomerId} выбрал добавление товара в избранное из результатов поиска", session.UserId);
                        AddFavorite(session, products);
                        break;
                    case "3":
                        _logger.LogInformation("Покупатель {CustomerId} вышел из результатов поиска", session.UserId);
                        return;
                    default:
                        Console.WriteLine("Неверный выбор.");
                        _logger.LogWarning("Покупатель {CustomerId} ввел неверный выбор в меню поиска: {Choice}", session.UserId, choice);
                        break;
                }
                Console.WriteLine("Нажмите любую клавишу для продолжения...");
                Console.ReadKey();
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при поиске товаров: {ex.Message}");
            _logger.LogError(ex, "Ошибка при поиске товаров покупателем {CustomerId}", session.UserId);
        }
    }

    private void ShowProduct(UserSession session, List<Product> products)
    {
        Console.WriteLine("Введите номер товара:");
        if (!int.TryParse(Console.ReadLine(), out int index) || index < 1 || index > products.Count)
        {
            Console.WriteLine("Некорректный номер.");
            _logger.LogWarning("Покупатель {CustomerId} ввел некорректный номер товара для просмотра", session.UserId);
            return;
        }

        var product = products[index - 1];
        _logger.LogInformation("Покупатель {CustomerId} просматривает товар {ProductId}", session.UserId, product.Id);

        List<OfferDetailsDto> offers;
        try
        {
            offers = _offerService.GetOfferDetailsByProductId(new ProductId(product.Id));
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при получении предложений: {ex.Message}");
            _logger.LogError(ex, "Ошибка при получении предложений по товару {ProductId} для покупателя {CustomerId}", product.Id, session.UserId);
            return;
        }

        Console.Clear();
        Console.WriteLine($"=== {product.Name} ===");
        Console.WriteLine(product.Description);

        if (offers.Count == 0)
        {
            Console.WriteLine("Для этого товара пока нет предложений.");
            _logger.LogInformation("Для товара {ProductId} нет предложений", product.Id);
            return;
        }

        Console.WriteLine("Доступные предложения:");
        for (int i = 0; i < offers.Count; i++)
        {
            var offer = offers[i];
            Console.WriteLine($"{i + 1}. Магазин: {offer.StoreName} | Цена: {offer.Price} | " +
                            $"Срок доставки: {offer.DeliveryTime} дней | Кол-во: {offer.Quantity} | " +
                            $"Рейтинг: {offer.AvgRating:F1} (Оценок: {offer.RatingCount})");
        }

        Console.WriteLine("\nМеню:");
        Console.WriteLine("1. Заказать предложение");
        Console.WriteLine("2. Назад");

        var choice = Console.ReadLine();
        switch (choice)
        {
            case "1":
                _logger.LogInformation("Покупатель {CustomerId} выбрал создание заказа для товара {ProductId}", session.UserId, product.Id);
                MakeOrder(session, offers);
                break;
            case "2":
                _logger.LogInformation("Покупатель {CustomerId} вышел из просмотра товара {ProductId}", session.UserId, product.Id);
                return;
            default:
                _logger.LogWarning("Покупатель {CustomerId} ввел неверный выбор при просмотре товара {ProductId}: {Choice}", session.UserId, product.Id, choice);
                Console.WriteLine("Неверный выбор.");
                break;
        }
    }

    private void MakeOrder(UserSession session, List<OfferDetailsDto> offers)
    {
        Console.WriteLine("Введите номер предложения:");
        if (!int.TryParse(Console.ReadLine(), out int offerIndex) || offerIndex < 1 || offerIndex > offers.Count)
        {
            Console.WriteLine("Некорректный номер.");
            _logger.LogWarning("Покупатель {CustomerId} ввел некорректный номер предложения для заказа", session.UserId);
            return;
        }

        var offerDetails = offers[offerIndex - 1];
        var offer = OfferDetailsDto.CreateOffer(offerDetails);
        var customer = _customerService.GetById(new CustomerId(session.UserId));

        Console.WriteLine("Введите количество:");
        if (!int.TryParse(Console.ReadLine(), out int quantity) || quantity < 1 || quantity > offer.Quantity)
        {
            Console.WriteLine("Некорректное количество.");
            _logger.LogWarning("Покупатель {CustomerId} ввел некорректное количество для заказа предложения {OfferId}", session.UserId, offer.Id);
            return;
        }

        try
        {
            var order = Order.Create(Guid.NewGuid(), customer.Id, offer.Id, quantity);
            var createdOrder = _orderService.Create(order);

            _logger.LogInformation("Заказ {OrderId} создан покупателем {CustomerId} на предложение {OfferId}, количество {Quantity}",
                createdOrder.Id, session.UserId, offer.Id, quantity);

            Console.WriteLine($"Заказ {createdOrder.Id} создан. Оплатить сейчас? (y/n)");
            var payChoice = Console.ReadLine();
            if (payChoice?.ToLower() == "y")
            {
                _logger.LogInformation("Покупатель {CustomerId} выбрал оплату заказа {OrderId}", session.UserId, createdOrder.Id);
                ProcessPayment(session, customer, createdOrder, offer);
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при создании заказа: {ex.Message}");
            _logger.LogError(ex, "Ошибка при создании заказа покупателем {CustomerId}", session.UserId);
        }
    }

    private void ProcessPayment(UserSession session, Customer customer, Order order, Offer offer)
    {
        _logger.LogInformation("Начало оплаты заказа {OrderId} покупателем {CustomerId}", order.Id, session.UserId);

        Console.Write("Введите номер карты: ");
        var cardNumber = Console.ReadLine() ?? "";

        Console.Write("Введите срок действия карты (MM/YY): ");
        var expirationDate = Console.ReadLine() ?? "";

        Console.Write("Введите CVC: ");
        var cvc = Console.ReadLine() ?? "";

        Console.Write("Введите метод оплаты: ");
        var paymentMethod = Console.ReadLine() ?? "";

        var paymentInfo = new PaymentInfo(
            totalAmount: offer.Price * order.Quantity,
            points: new CustomerPoints(customer.Points),
            cardNumber: cardNumber,
            expirationDate: expirationDate,
            cvc: cvc,
            paymentMethod: paymentMethod
        );

        var paymentResult = _paymentUseCase.ProcessPayment(customer, order, offer, paymentInfo);

        if (paymentResult.IsSuccess)
        {
            _logger.LogInformation("Оплата заказа {OrderId} покупателем {CustomerId} прошла успешно", order.Id, session.UserId);
            Console.WriteLine("Оплата прошла успешно.");
        }
        else
        {
            _logger.LogWarning("Оплата заказа {OrderId} покупателем {CustomerId} не удалась", order.Id, session.UserId);
            Console.WriteLine("Ошибка оплаты.");
        }
    }

    private void AddFavorite(UserSession session, List<Product> products)
    {
        Console.WriteLine("Введите номер товара для добавления в избранное:");
        if (!int.TryParse(Console.ReadLine(), out int index) || index < 1 || index > products.Count)
        {
            Console.WriteLine("Некорректный номер.");
            _logger.LogWarning("Покупатель {CustomerId} ввел некорректный номер товара для добавления в избранное", session.UserId);
            return;
        }

        var product = products[index - 1];
        _logger.LogInformation("Покупатель {CustomerId} добавляет товар {ProductId} в избранное", session.UserId, product.Id);

        try
        {
            var favorite = Favorite.Create(Guid.NewGuid(), session.UserId, product.Id);
            _favoriteService.Create(favorite);
            Console.WriteLine("Товар добавлен в избранное.");
            _logger.LogInformation("Товар {ProductId} добавлен в избранное покупателем {CustomerId}", product.Id, session.UserId);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при добавлении в избранное: {ex.Message}");
            _logger.LogError(ex, "Ошибка при добавлении товара {ProductId} в избранное покупателем {CustomerId}", product.Id, session.UserId);
        }
    }

    public void ShowRecommendations(UserSession session)
    {
        try
        {
            var recommendedOffers = _recSysUseCase.Recommend(new CustomerId(session.UserId));
            Console.Clear();
            Console.WriteLine("=== Рекомендации ===");
            if (recommendedOffers.Count == 0)
                Console.WriteLine("Добавляйте товары в избранное, чтобы сформировать рекоммендации.");
            for (int i = 0; i < recommendedOffers.Count; i++)
            {
                var o = recommendedOffers[i];
                Console.WriteLine($"{i + 1}. {o.ProductId} - Цена: {o.Price} - Срок: {o.DeliveryTime} дней");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при получении рекомендаций: {ex.Message}");
        }
    }

    public void ListOrders(UserSession session)
    {
        try
        {
            _logger.LogInformation("Покупатель {CustomerId} запросил список заказов", session.UserId);
            Console.WriteLine("=== Список заказов пользователя ===");

            var customerId = new CustomerId(session.UserId);
            var orderDetails = _orderService.GetOrderDetailsByCustomerId(customerId);

            if (orderDetails.Count == 0)
            {
                Console.WriteLine("У вас пока нет заказов.");
                _logger.LogInformation("У покупателя {CustomerId} нет заказов", session.UserId);
                return;
            }

            for (int i = 0; i < orderDetails.Count; i++)
            {
                var o = orderDetails[i];
                Console.WriteLine($"{i + 1}. Заказ {o.OrderId}");
                Console.WriteLine($"   Статус: {o.Status}");
                Console.WriteLine($"   Товар: {o.ProductName} ({o.ProductDescription})");
                Console.WriteLine($"   Магазин: {o.StoreName}");
                Console.WriteLine($"   Кол-во: {o.Quantity}, Цена за шт: {o.OfferPrice}, Итого: {o.OfferPrice * o.Quantity}");
                Console.WriteLine($"   Отзыв: {(string.IsNullOrEmpty(o.ReviewText) ? "отсутствует" : o.ReviewText)}");
                Console.WriteLine();
            }

            Console.WriteLine("Меню:");
            Console.WriteLine("1. Оплатить заказ");
            Console.WriteLine("2. Написать отзыв");
            Console.WriteLine("3. Удалить отзыв");
            Console.WriteLine("0. Назад");
            Console.Write("Ваш выбор: ");
            var choice = Console.ReadLine();

            switch (choice)
            {
                case "1":
                    PayOrder(session, orderDetails);
                    break;
                case "2":
                    WriteReview(session, orderDetails);
                    break;
                case "3":
                    DeleteReview(session, orderDetails);
                    break;
                case "0":
                    return;
                default:
                    Console.WriteLine("Неверный выбор.");
                    _logger.LogWarning("Покупатель {CustomerId} ввел неверный выбор в меню заказов: {Choice}", session.UserId, choice);
                    break;
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при получении заказов: {ex.Message}");
            _logger.LogError(ex, "Ошибка при получении заказов для покупателя {CustomerId}", session.UserId);
        }
    }

    private PaymentInfo CollectPaymentData(Offer offer, int quantity, int customerPoints)
    {
        string cardNumber, expirationDate, cvc, paymentMethod;

        do
        {
            Console.Write("Введите номер карты: ");
            cardNumber = Console.ReadLine()?.Trim() ?? "";
        } while (string.IsNullOrEmpty(cardNumber));

        do
        {
            Console.Write("Введите срок действия карты (MM/YY): ");
            expirationDate = Console.ReadLine()?.Trim() ?? "";
        } while (string.IsNullOrEmpty(expirationDate));

        do
        {
            Console.Write("Введите CVC: ");
            cvc = Console.ReadLine()?.Trim() ?? "";
        } while (string.IsNullOrEmpty(cvc));

        do
        {
            Console.Write("Введите метод оплаты: ");
            paymentMethod = Console.ReadLine()?.Trim() ?? "";
        } while (string.IsNullOrEmpty(paymentMethod));

        return new PaymentInfo(
            totalAmount: offer.Price * quantity,
            points: new CustomerPoints(customerPoints),
            cardNumber: cardNumber,
            expirationDate: expirationDate,
            cvc: cvc,
            paymentMethod: paymentMethod
        );
    }

    private void PayOrder(UserSession session, List<OrderDetailsDto> orders)
    {
        Console.Write("Введите номер заказа для оплаты: ");
        if (!int.TryParse(Console.ReadLine(), out int index) || index < 1 || index > orders.Count)
        {
            Console.WriteLine("Некорректный номер заказа.");
            _logger.LogWarning("Покупатель {CustomerId} ввел некорректный номер заказа для оплаты", session.UserId);
            return;
        }

        var orderDetails = orders[index - 1];
        if (orderDetails.Status == OrderStatus.Payed)
        {
            Console.WriteLine("Этот заказ уже оплачен.");
            _logger.LogWarning("Покупатель {CustomerId} попытался оплатить уже оплаченный заказ {OrderId}", session.UserId, orderDetails.OrderId);
            return;
        }

        var order = _orderService.GetById(new OrderId(orderDetails.OrderId));
        var offer = _offerService.GetById(new OfferId(orderDetails.OfferId));
        var customer = _customerService.GetById(new CustomerId(session.UserId));

        var paymentInfo = CollectPaymentData(offer, orderDetails.Quantity, customer.Points);

        var paymentResult = _paymentUseCase.ProcessPayment(customer, order, offer, paymentInfo);

        if (paymentResult.IsSuccess)
        {
            Console.WriteLine("Оплата прошла успешно.");
            _logger.LogInformation("Оплата заказа {OrderId} покупателем {CustomerId} прошла успешно", orderDetails.OrderId, session.UserId);
        }
        else
        {
            Console.WriteLine("Ошибка оплаты.");
            _logger.LogWarning("Оплата заказа {OrderId} покупателем {CustomerId} не удалась", orderDetails.OrderId, session.UserId);
        }
    }
    
    private void WriteReview(UserSession session, List<OrderDetailsDto> orders)
    {
        Console.Write("Введите номер заказа для отзыва: ");
        if (!int.TryParse(Console.ReadLine(), out int index) || index < 1 || index > orders.Count)
        {
            Console.WriteLine("Некорректный номер заказа.");
            _logger.LogWarning("Покупатель {CustomerId} ввел некорректный номер заказа для отзыва", session.UserId);
            return;
        }

        var order = orders[index - 1];
        var existingReview = _reviewService.GetByOrderId(new OrderId(order.OrderId));
        if (existingReview != null)
        {
            Console.WriteLine("Для этого заказа уже оставлен отзыв.");
            _logger.LogWarning("Покупатель {CustomerId} попытался оставить повторный отзыв к заказу {OrderId}", session.UserId, order.OrderId);
            return;
        }

        Console.Write("Введите оценку (1-5): ");
        if (!int.TryParse(Console.ReadLine(), out int rating) || rating < 1 || rating > 5)
        {
            Console.WriteLine("Неверная оценка. Должно быть число от 1 до 5.");
            _logger.LogWarning("Покупатель {CustomerId} ввел неверную оценку {Rating} для заказа {OrderId}", session.UserId, rating, order.OrderId);
            return;
        }

        Console.Write("Введите текст отзыва (может быть пустым): ");
        var text = Console.ReadLine()?.Trim() ?? "";

        try
        {
            var review = Review.Create(Guid.NewGuid(), session.UserId, order.OrderId, rating, text);
            _reviewService.Create(review);
            _logger.LogInformation("Покупатель {CustomerId} оставил отзыв к заказу {OrderId} с оценкой {Rating}", session.UserId, order.OrderId, rating);

            var product = _productService.GetById(new ProductId(order.ProductId));
            _productService.AddReview(product, rating);

            var store = _storeService.GetById(new StoreId(order.StoreId));
            _storeService.AddReview(store, rating);

            Console.WriteLine("Отзыв успешно сохранен.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при сохранении отзыва: {ex.Message}");
            _logger.LogError(ex, "Ошибка при сохранении отзыва покупателем {CustomerId} для заказа {OrderId}", session.UserId, order.OrderId);
        }
    }

    private void DeleteReview(UserSession session, List<OrderDetailsDto> orders)
    {
        Console.Write("Введите номер заказа для удаления отзыва: ");
        if (!int.TryParse(Console.ReadLine(), out int index) || index < 1 || index > orders.Count)
        {
            Console.WriteLine("Некорректный номер заказа.");
            _logger.LogWarning("Покупатель {CustomerId} ввел некорректный номер заказа для удаления отзыва", session.UserId);
            return;
        }

        var order = orders[index - 1];
        var existingReview = _reviewService.GetByOrderId(new OrderId(order.OrderId));
        if (existingReview == null)
        {
            Console.WriteLine("Для этого заказа нет отзыва.");
            _logger.LogWarning("Покупатель {CustomerId} попытался удалить несуществующий отзыв для заказа {OrderId}", session.UserId, order.OrderId);
            return;
        }

        _reviewService.DeleteById(new ReviewId(existingReview.Id));
        _logger.LogInformation("Покупатель {CustomerId} удалил отзыв к заказу {OrderId}", session.UserId, order.OrderId);
        Console.WriteLine("Отзыв успешно удален.");
    }
}
