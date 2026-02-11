using System;
using System.Collections.Generic;
using Domain.InputPorts;
using Domain.OutputPorts;
using Domain;
using Domain.Models;
using UserInterface;

namespace UserInterface.Controllers;
using Microsoft.Extensions.Logging;

public class SellerController
{
    private readonly ISellerService _sellerService;
    private readonly IStoreService _storeService;
    private readonly IOfferService _offerService;
    private readonly IProductService _productService;
    private readonly ILogger _logger;

    public SellerController(
        ISellerService sellerService,
        IStoreService storeService,
        IOfferService offerService,
        IProductService productService,
        ILogger logger)
    {
        _sellerService = sellerService;
        _storeService = storeService;
        _offerService = offerService;
        _productService = productService;
        _logger = logger;
    }

    public void ShowProfile(UserSession session)
    {
        try
        {
            var seller = _sellerService.GetById(new SellerId(session.UserId));
            _logger.LogInformation("Просмотр профиля продавца {SellerId}", session.UserId);

            Console.WriteLine("=== Профиль продавца ===");
            Console.WriteLine($"Имя: {seller.FirstName}");
            Console.WriteLine($"Фамилия: {seller.LastName}");
            Console.WriteLine($"Email: {seller.Email}");
            Console.WriteLine($"Телефон: {seller.Phone}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при получении профиля: {ex.Message}");
            _logger.LogError(ex, "Ошибка при получении профиля продавца {SellerId}", session.UserId);
        }
    }

    public void ListStores(UserSession session)
    {
        try
        {
            var stores = _storeService.GetBySellerId(new SellerId(session.UserId));
            _logger.LogInformation("Получение списка магазинов продавца {SellerId}, найдено {Count}", session.UserId, stores.Count);

            if (stores.Count == 0)
            {
                Console.WriteLine("У вас нет магазинов.");
                _logger.LogInformation("У продавца {SellerId} нет магазинов", session.UserId);
                return;
            }

            while (true)
            {
                Console.Clear();
                Console.WriteLine("=== Мои магазины ===");
                for (int i = 0; i < stores.Count; i++)
                    Console.WriteLine($"{i + 1}. {stores[i].Name}");

                Console.WriteLine("Меню:");
                Console.WriteLine("1. Изменить магазин");
                Console.WriteLine("2. Просмотреть предложения магазина");
                Console.WriteLine("3. Назад");

                var choice = Console.ReadLine();
                switch (choice)
                {
                    case "1":
                        _logger.LogInformation("Выбран пункт меню 'Изменить магазин' для продавца {SellerId}", session.UserId);
                        EditStoreFromList(stores);
                        break;
                    case "2":
                        _logger.LogInformation("Выбран пункт меню 'Просмотреть предложения магазина' для продавца {SellerId}", session.UserId);
                        ShowStoreOffers(stores);
                        break;
                    case "3":
                        _logger.LogInformation("Выход из меню магазинов для продавца {SellerId}", session.UserId);
                        return;
                    default:
                        Console.WriteLine("Неверный выбор.");
                        _logger.LogWarning("Неверный выбор в меню магазинов продавца {SellerId}: {Choice}", session.UserId, choice);
                        break;
                }
                Console.WriteLine("Нажмите любую клавишу для продолжения...");
                Console.ReadKey();
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при получении магазинов: {ex.Message}");
            _logger.LogError(ex, "Ошибка при получении магазинов для продавца {SellerId}", session.UserId);
        }
    }

    private void EditStoreFromList(List<Store> stores)
    {
        Console.WriteLine("Введите номер магазина для редактирования:");
        if (!int.TryParse(Console.ReadLine(), out int index) || index < 1 || index > stores.Count)
        {
            Console.WriteLine("Некорректный номер.");
            _logger.LogWarning("Некорректный номер магазина при редактировании: {Input}", index);
            return;
        }

        var store = stores[index - 1];
        _logger.LogInformation("Начало редактирования магазина {StoreId}", store.Id);

        Console.WriteLine($"Редактирование магазина: {store.Name}");
        Console.WriteLine("Введите новое название (или Enter, чтобы оставить):");
        var nameInput = Console.ReadLine();

        Console.WriteLine("Введите новое ОГРН (или Enter, чтобы оставить):");
        var ogrnInput = Console.ReadLine();

        var name = string.IsNullOrWhiteSpace(nameInput) ? store.Name : nameInput.Trim();
        var ogrn = string.IsNullOrWhiteSpace(ogrnInput) ? store.Ogrn : ogrnInput.Trim();

        var storeInfo = new StoreInfo(name, ogrn);

        try
        {
            _storeService.Update(store, storeInfo);
            Console.WriteLine("Магазин обновлен.");
            _logger.LogInformation("Магазин {StoreId} обновлен. Новое название: {Name}, новый ОГРН: {Ogrn}", store.Id, name, ogrn);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при редактировании магазина: {ex.Message}");
            _logger.LogError(ex, "Ошибка при редактировании магазина {StoreId}", store.Id);
        }
    }

    private void ShowStoreOffers(List<Store> stores)
    {
        Console.WriteLine("Введите номер магазина для просмотра предложений:");
        if (!int.TryParse(Console.ReadLine(), out int index) || index < 1 || index > stores.Count)
        {
            Console.WriteLine("Некорректный номер.");
            _logger.LogWarning("Некорректный номер магазина при просмотре предложений: {Input}", index);
            return;
        }

        var store = stores[index - 1];
        _logger.LogInformation("Просмотр предложений магазина {StoreId}", store.Id);

        try
        {
            var offers = _offerService.GetByStoreId(new StoreId(store.Id));

            while (true)
            {
                Console.Clear();
                Console.WriteLine($"=== Предложения магазина {store.Name} ===");
                if (offers.Count == 0)
                {
                    Console.WriteLine("Предложений нет.");
                    _logger.LogInformation("В магазине {StoreId} нет предложений", store.Id);
                }
                for (int i = 0; i < offers.Count; i++)
                {
                    var o = offers[i];
                    Console.WriteLine($"{i + 1}. Товар: {o.ProductId}, Цена: {o.Price}, Кол-во: {o.Quantity}, Срок: {o.DeliveryTime} дней");
                }

                Console.WriteLine("Меню:");
                Console.WriteLine("1. Изменить предложение");
                Console.WriteLine("2. Добавить предложение");
                Console.WriteLine("3. Назад");

                var choice = Console.ReadLine();
                switch (choice)
                {
                    case "1":
                        _logger.LogInformation("Выбран пункт 'Изменить предложение' для магазина {StoreId}", store.Id);
                        EditOfferFromList(offers);
                        break;
                    case "2":
                        _logger.LogInformation("Выбран пункт 'Добавить предложение' для магазина {StoreId}", store.Id);
                        AddOfferToStore(store);
                        offers = _offerService.GetByStoreId(new StoreId(store.Id));
                        break;
                    case "3":
                        _logger.LogInformation("Выход из меню предложений магазина {StoreId}", store.Id);
                        return;
                    default:
                        Console.WriteLine("Неверный выбор.");
                        _logger.LogWarning("Неверный выбор в меню предложений магазина {StoreId}: {Choice}", store.Id, choice);
                        break;
                }
                Console.WriteLine("Нажмите любую клавишу для продолжения...");
                Console.ReadKey();
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при получении предложений: {ex.Message}");
            _logger.LogError(ex, "Ошибка при получении предложений магазина {StoreId}", store.Id);
        }
    }

    private void AddOfferToStore(Store store)
    {
        try
        {
            Console.WriteLine("=== Добавление нового предложения ===");

            Console.Write("Название товара: ");
            var productName = Console.ReadLine()?.Trim();
            if (string.IsNullOrWhiteSpace(productName))
            {
                Console.WriteLine("Название товара не может быть пустым.");
                _logger.LogWarning("Пустое название товара при добавлении предложения в магазин {StoreId}", store.Id);
                return;
            }

            var products = _productService.GetByName(productName);
            if (products.Count == 0)
            {
                Console.WriteLine("Товар не найден.");
                _logger.LogWarning("Товар с названием '{ProductName}' не найден при добавлении предложения в магазин {StoreId}", productName, store.Id);
                return;
            }

            Product selectedProduct;
            if (products.Count == 1)
            {
                selectedProduct = products[0];
            }
            else
            {
                Console.WriteLine("Найдено несколько товаров. Выберите номер:");
                for (int i = 0; i < products.Count; i++)
                    Console.WriteLine($"{i + 1}. {products[i].Name} - {products[i].Category}");
                if (!int.TryParse(Console.ReadLine(), out int index) || index < 1 || index > products.Count)
                {
                    Console.WriteLine("Некорректный выбор.");
                    _logger.LogWarning("Некорректный выбор товара при добавлении предложения в магазин {StoreId}", store.Id);
                    return;
                }
                selectedProduct = products[index - 1];
            }

            Console.Write("Цена: ");
            if (!decimal.TryParse(Console.ReadLine(), out decimal price))
            {
                Console.WriteLine("Некорректная цена.");
                _logger.LogWarning("Некорректная цена при добавлении предложения в магазин {StoreId}", store.Id);
                return;
            }

            Console.Write("Количество: ");
            if (!int.TryParse(Console.ReadLine(), out int quantity))
            {
                Console.WriteLine("Некорректное количество.");
                _logger.LogWarning("Некорректное количество при добавлении предложения в магазин {StoreId}", store.Id);
                return;
            }

            Console.Write("Срок доставки (дней): ");
            if (!int.TryParse(Console.ReadLine(), out int deliveryTime))
            {
                Console.WriteLine("Некорректный срок доставки.");
                _logger.LogWarning("Некорректный срок доставки при добавлении предложения в магазин {StoreId}", store.Id);
                return;
            }

            var offer = Offer.Create(Guid.NewGuid(), selectedProduct.Id, store.Id, price, quantity, deliveryTime);
            _offerService.Create(offer);

            Console.WriteLine("Предложение успешно добавлено.");
            _logger.LogInformation("Добавлено новое предложение {OfferId} для товара {ProductName} в магазин {StoreId}", offer.Id, selectedProduct.Name, store.Id);
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Ошибка при добавлении предложения в магазин {StoreId}", store.Id);
            Console.WriteLine($"Ошибка при добавлении предложения: {ex.Message}");
        }
    }

    private void EditOfferFromList(List<Offer> offers)
    {
        Console.WriteLine("Введите номер предложения для редактирования:");
        if (!int.TryParse(Console.ReadLine(), out int index) || index < 1 || index > offers.Count)
        {
            _logger.LogWarning("Некорректный номер предложения для редактирования: {Input}", index);
            Console.WriteLine("Некорректный номер.");
            return;
        }

        var offer = offers[index - 1];
        _logger.LogInformation("Начало редактирования предложения {OfferId}", offer.Id);

        try
        {
            Console.WriteLine($"Редактирование предложения товара {offer.ProductId}");
            Console.WriteLine("Введите новую цену (или Enter, чтобы оставить):");
            var priceInput = Console.ReadLine();
            if (decimal.TryParse(priceInput, out decimal newPrice))
            {
                _offerService.UpdatePrice(offer, newPrice);
                _logger.LogInformation("Цена предложения {OfferId} обновлена на {NewPrice}", offer.Id, newPrice);
            }

            Console.WriteLine("Введите новое количество (или Enter, чтобы оставить):");
            var qtyInput = Console.ReadLine();
            if (int.TryParse(qtyInput, out int newQty))
            {
                _offerService.UpdateQuantity(offer, newQty);
                _logger.LogInformation("Количество предложения {OfferId} обновлено на {NewQty}", offer.Id, newQty);
            }

            Console.WriteLine("Введите новый срок доставки (дней) (или Enter, чтобы оставить):");
            var deliveryInput = Console.ReadLine();
            if (int.TryParse(deliveryInput, out int newDelivery))
            {
                _offerService.UpdateDeliveryTime(offer, newDelivery);
                _logger.LogInformation("Срок доставки предложения {OfferId} обновлён на {NewDelivery}", offer.Id, newDelivery);
            }

            Console.WriteLine("Предложение обновлено.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при редактировании предложения: {ex.Message}");
            _logger.LogError(ex, "Ошибка при редактировании предложения {OfferId}", offer.Id);
        }
    }

    public void AddStore(UserSession session)
    {
        _logger.LogInformation("Продавец Id={SellerId} инициировал добавление магазина", session.UserId);

        Console.WriteLine("=== Добавление магазина ===");
        Console.Write("Введите название магазина: ");
        var name = Console.ReadLine();
        Console.Write("Введите ОГРН: ");
        var ogrn = Console.ReadLine();

        if (string.IsNullOrWhiteSpace(name) || string.IsNullOrWhiteSpace(ogrn))
        {
            Console.WriteLine("Название и ОГРН не могут быть пустыми.");
            _logger.LogWarning("Продавец Id={SellerId} ввёл некорректные данные при добавлении магазина", session.UserId);
            return;
        }

        try
        {
            var store = Store.Create(
                Guid.NewGuid(),
                session.UserId,
                name,
                ogrn
            );
            var createdStore = _storeService.Create(store);

            Console.WriteLine($"Магазин успешно создан.");
            _logger.LogInformation("Продавец Id={SellerId} успешно создал магазин Id={StoreId}, Название={StoreName}",
                session.UserId, createdStore.Id, createdStore.Name);

        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при создании магазина: {ex.Message}");
            _logger.LogError(ex, "Ошибка при создании магазина продавцом Id={SellerId}", session.UserId);
        }
    }
}
