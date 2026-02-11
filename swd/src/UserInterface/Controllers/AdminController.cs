using System;
using System.Collections.Generic;
using Domain.InputPorts;
using Domain.OutputPorts;
using Domain;
using Domain.Models;
using Microsoft.Extensions.Logging;

namespace UserInterface.Controllers;

public class AdminController
{
    private readonly IProductService _productService;
    private readonly IOfferService _offerService;
    private readonly IStoreService _storeService;
    private readonly ILogger _logger;

    public AdminController(
        IProductService productService,
        IOfferService offerService,
        IStoreService storeService,
        ILogger logger)
    {
        _productService = productService;
        _offerService = offerService;
        _storeService = storeService;
        _logger = logger;
    }

    public void AddProduct()
    {
        try
        {
            _logger.LogInformation("Начало добавления нового товара.");

            Console.WriteLine("=== Добавление нового товара ===");

            Console.Write("Название: ");
            var nameInput = Console.ReadLine();
            if (string.IsNullOrWhiteSpace(nameInput))
            {
                Console.WriteLine("Название не может быть пустым.");
                _logger.LogWarning("Попытка добавить товар с пустым названием.");
                return;
            }

            Console.Write("Категория: ");
            var categoryInput = Console.ReadLine();
            if (string.IsNullOrWhiteSpace(categoryInput))
            {
                Console.WriteLine("Категория не может быть пустой.");
                _logger.LogWarning("Попытка добавить товар с пустой категорией.");
                return;
            }

            Console.Write("Описание: ");
            var descriptionInput = Console.ReadLine();
            if (string.IsNullOrWhiteSpace(descriptionInput))
            {
                Console.WriteLine("Описание не может быть пустым.");
                _logger.LogWarning("Попытка добавить товар с пустым описанием.");
                return;
            }

            var productInfo = new ProductInfo(                
                nameInput.Trim(),
                categoryInput.Trim(),
                descriptionInput.Trim()
            );

            _productService.Create(productInfo);
            Console.WriteLine("Товар успешно добавлен.");
            _logger.LogInformation("Товар {ProductName} успешно добавлен.", productInfo.Name);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при добавлении товара: {ex.Message}");
            _logger.LogError(ex, "Ошибка при добавлении товара.");
        }
    }

    public void EditProduct()
    {
        try
        {
            _logger.LogInformation("Начало редактирования товара.");

            Console.WriteLine("=== Редактирование товара ===");
            Console.Write("Введите наименование товара для поиска: ");
            var nameInput = Console.ReadLine();
            if (string.IsNullOrWhiteSpace(nameInput))
            {
                _logger.LogWarning("Введено пустое название при поиске товара.");
                Console.WriteLine("Наименование не может быть пустым.");
                return;
            }
            var products = _productService.GetByName(nameInput.Trim());

            if (products.Count == 0)
            {
                Console.WriteLine("Товары не найдены.");
                _logger.LogInformation("Товары с названием {ProductName} не найдены.", nameInput);
                return;
            }

            for (int i = 0; i < products.Count; i++)
            {
                Console.WriteLine($"{i + 1}. {products[i].Name} - {products[i].Category}");
            }

            Console.Write("Выберите номер товара для редактирования: ");
            if (!int.TryParse(Console.ReadLine(), out int index) || index < 1 || index > products.Count)
            {
                Console.WriteLine("Некорректный номер.");
                _logger.LogWarning("Некорректный выбор номера товара при редактировании.");
                return;
            }

            var product = products[index - 1];
            _logger.LogInformation("Редактирование товара {ProductId}, текущее название: {ProductName}", product.Id, product.Name);

            Console.Write("Новое наименование (Enter чтобы оставить): ");
            var newName = Console.ReadLine();
            if (!string.IsNullOrWhiteSpace(newName))
            {
                _productService.UpdateName(product, newName);
                _logger.LogInformation("Название товара обновлено: {NewName}", newName);
            }

            Console.Write("Новая категория (Enter чтобы оставить): ");
            var newCategory = Console.ReadLine();
            if (!string.IsNullOrWhiteSpace(newCategory))
            {
                _productService.UpdateCategory(product, newCategory);
                _logger.LogInformation("Категория товара обновлена: {NewCategory}", newCategory);
            }

            Console.Write("Новое описание (Enter чтобы оставить): ");
            var newDesc = Console.ReadLine();
            if (!string.IsNullOrWhiteSpace(newDesc))
            {
                _productService.UpdateDescription(product, newDesc);
                _logger.LogInformation("Описание товара обновлено.");
            }

            Console.WriteLine("Товар обновлен.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при редактировании товара: {ex.Message}");
            _logger.LogError(ex, "Ошибка при редактировании товара.");
        }
    }

    public void EditOffer()
    {
        try
        {
            _logger.LogInformation("Начало редактирования предложения.");

            Console.WriteLine("=== Редактирование предложения ===");
            Console.Write("Введите ID предложения: ");
            if (!Guid.TryParse(Console.ReadLine(), out Guid offerId))
            {
                Console.WriteLine("Некорректный ID.");
                _logger.LogWarning("Введён некорректный ID при редактировании предложения.");
                return;
            }

            var offer = _offerService.GetById(new OfferId(offerId));
            _logger.LogInformation("Редактирование предложения {OfferId}", offer.Id);

            Console.Write($"Новая цена (текущая {offer.Price}, Enter чтобы оставить): ");
            var priceInput = Console.ReadLine();
            if (decimal.TryParse(priceInput, out decimal newPrice))
            {
                _offerService.UpdatePrice(offer, newPrice);
                _logger.LogInformation("Цена обновлена: {NewPrice}", newPrice);
            }

            Console.Write($"Новое количество (текущее {offer.Quantity}, Enter чтобы оставить): ");
            var qtyInput = Console.ReadLine();
            if (int.TryParse(qtyInput, out int newQty))
            {
                _offerService.UpdateQuantity(offer, newQty);
                _logger.LogInformation("Количество обновлено: {NewQuantity}", newQty);
            }

            Console.Write($"Новый срок доставки (текущий {offer.DeliveryTime} дней, Enter чтобы оставить): ");
            var deliveryInput = Console.ReadLine();
            if (int.TryParse(deliveryInput, out int newDelivery))
            {
                _offerService.UpdateDeliveryTime(offer, newDelivery);
                _logger.LogInformation("Срок доставки обновлён: {NewDelivery}", newDelivery);
            }

            Console.WriteLine("Предложение обновлено.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при редактировании предложения: {ex.Message}");
            _logger.LogError(ex, "Ошибка при редактировании предложения.");
        }
    }

    public void EditStore()
    {
        try
        {
            _logger.LogInformation("Начало редактирования магазина.");

            Console.WriteLine("=== Редактирование магазина ===");
            Console.Write("Введите ID магазина: ");
            if (!Guid.TryParse(Console.ReadLine(), out Guid storeId))
            {
                _logger.LogWarning("Введён некорректный ID при редактировании магазина.");
                Console.WriteLine("Некорректный ID.");
                return;
            }

            var store = _storeService.GetById(new StoreId(storeId));
            _logger.LogInformation("Редактирование магазина {StoreId}, текущее название: {StoreName}", store.Id, store.Name);

            Console.Write($"Новое название (текущее {store.Name}, Enter чтобы оставить): ");
            var newNameInput = Console.ReadLine();
            Console.Write($"Новое описание (текущее {store.Ogrn}, Enter чтобы оставить): ");
            var newOgrnInput = Console.ReadLine();
            
            var newName = string.IsNullOrWhiteSpace(newNameInput) ? store.Name : newNameInput.Trim();
            var newOgrn = string.IsNullOrWhiteSpace(newOgrnInput) ? store.Ogrn : newOgrnInput.Trim();
            var updatedInfo = new StoreInfo(newName, newOgrn);

            _storeService.Update(store, updatedInfo);
            _logger.LogInformation("Магазин {StoreId} обновлен. Новое название: {NewName}, новый ОГРН: {NewOgrn}", store.Id, newName, newOgrn);

            Console.WriteLine("Магазин обновлен.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при редактировании магазина: {ex.Message}");
            _logger.LogError(ex, "Ошибка при редактировании магазина.");
        }
    }

}
