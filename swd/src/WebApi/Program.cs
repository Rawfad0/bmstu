using System.Reflection;
using DataAccess;
using DataAccess.Repositories;
using Domain;
using Domain.Models;
using Domain.InputPorts;
using Domain.OutputPorts;
using Microsoft.OpenApi.Models;
using Serilog;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using Microsoft.IdentityModel.Tokens;
using System.Text;
using WebApi.Models;
using WebApi.WebDTO;

var builder = WebApplication.CreateBuilder(args);

// Serilog 
Log.Logger = new LoggerConfiguration()
    .ReadFrom.Configuration(builder.Configuration)
    .CreateLogger();
builder.Host.UseSerilog();

// Configuration
var configuration = builder.Configuration;
var connectionString = configuration.GetConnectionString("MarketplaceDb")!;
var priceCoef = configuration.GetValue<double>("Business:RecommendationPriceCoef");
var deliveryTimeCoef = configuration.GetValue<double>("Business:RecommendationDeliveryTimeCoef");

// Dapper context
builder.Services.AddSingleton(new DapperContext(connectionString));

// Repositories
builder.Services.AddScoped<ICustomerRepository, CustomerRepository>();
builder.Services.AddScoped<IFavoriteRepository, FavoriteRepository>();
builder.Services.AddScoped<IOfferRepository, OfferRepository>();
builder.Services.AddScoped<IOrderRepository, OrderRepository>();
builder.Services.AddScoped<IProductRepository, ProductRepository>();
builder.Services.AddScoped<IReviewRepository, ReviewRepository>();
builder.Services.AddScoped<ISellerRepository, SellerRepository>();
builder.Services.AddScoped<IStoreRepository, StoreRepository>();
builder.Services.AddSingleton<IPayment, Payment>();

// Services and UseCases
builder.Services.AddScoped<ICustomerService, CustomerService>();
builder.Services.AddScoped<IFavoriteService, FavoriteService>();
builder.Services.AddScoped<IOfferService, OfferService>();
builder.Services.AddScoped<IOrderService, OrderService>();
builder.Services.AddScoped<IProductService, ProductService>();
builder.Services.AddScoped<IReviewService, ReviewService>();
builder.Services.AddScoped<ISellerService, SellerService>();
builder.Services.AddScoped<IStoreService, StoreService>();
builder.Services.AddScoped<IRecSysUseCase>(sp =>
{
    var offerService = sp.GetRequiredService<IOfferService>();
    var favoriteService = sp.GetRequiredService<IFavoriteService>();
    return new RecSysUseCase(offerService, favoriteService, priceCoef, deliveryTimeCoef);
});
builder.Services.AddScoped<IPaymentUseCase, PaymentUseCase>();

// Swagger
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen(c =>
{
    c.SwaggerDoc("v1", new OpenApiInfo
    {
        Title = "Marketplace API",
        Version = "v1",
        Description = "API для Marketplace"
    });

    c.AddSecurityDefinition("Bearer", new OpenApiSecurityScheme
    {
        Description = "JWT Authorization header using the Bearer scheme. Example: \"Authorization: Bearer {token}\"",
        Name = "Authorization",
        In = ParameterLocation.Header,
        Type = SecuritySchemeType.Http,
        Scheme = "bearer"
    });

    c.AddSecurityRequirement(new OpenApiSecurityRequirement
    {
        {
            new OpenApiSecurityScheme
            {
                Reference = new OpenApiReference
                {
                    Type = ReferenceType.SecurityScheme,
                    Id = "Bearer"
                }
            },
            new string[] {}
        }
    });
});

// JWT Authentication
var jwtSettings = configuration.GetSection("JwtSettings");
var key = Encoding.UTF8.GetBytes(jwtSettings["Key"]!);

builder.Services.AddAuthentication(options =>
    {
        options.DefaultAuthenticateScheme = JwtBearerDefaults.AuthenticationScheme;
        options.DefaultChallengeScheme = JwtBearerDefaults.AuthenticationScheme;
    })
    .AddJwtBearer(options =>
    {
        options.TokenValidationParameters = new TokenValidationParameters
        {
            ValidateIssuer = true,
            ValidateAudience = true,
            ValidateLifetime = true,
            ValidateIssuerSigningKey = true,
            ValidIssuer = jwtSettings["Issuer"],
            ValidAudience = jwtSettings["Audience"],
            IssuerSigningKey = new SymmetricSecurityKey(key)
        };
    }
);
// builder.Services.AddAuthorization();
builder.Services.AddAuthorization(options =>
{
    options.AddPolicy("CustomerOnly", policy => 
        policy.RequireClaim(ClaimTypes.Role, "customer"));
    
    options.AddPolicy("SellerOnly", policy => 
        policy.RequireClaim(ClaimTypes.Role, "seller"));
    
    options.AddPolicy("AdminOnly", policy => 
        policy.RequireClaim(ClaimTypes.Role, "admin"));
});

var app = builder.Build();

if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseSerilogRequestLogging();
app.UseHttpsRedirection();
app.UseAuthentication();
app.UseAuthorization();

// Auth endpoints
app.MapPost("/api/v1/auth/login", (
    LoginRequest request,
    ICustomerService customerService,
    ISellerService sellerService,
    IConfiguration config) =>
{
    try
    {
        Guid? userId = null;

        switch (request.Role.ToLower())
        {
            case "customer":
                var customer = customerService.GetByEmail(request.Email);
                userId = customer.Id;
                break;
            case "seller":
                var seller = sellerService.GetByEmail(request.Email);
                userId = seller.Id;
                break;
            default:
                return Results.BadRequest(new { message = "Invalid role" });
        }

        // --- Генерация JWT ---
        var jwtSettings = config.GetSection("JwtSettings");
        var key = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(jwtSettings["Key"]!));
        var creds = new SigningCredentials(key, SecurityAlgorithms.HmacSha256);

        var claims = new[]
        {
            new Claim(JwtRegisteredClaimNames.Sub, request.Email),
            new Claim(ClaimTypes.Role, request.Role),
            new Claim("user_id", userId.ToString()!)
        };

        var token = new JwtSecurityToken(
            issuer: jwtSettings["Issuer"],
            audience: jwtSettings["Audience"],
            claims: claims,
            expires: DateTime.UtcNow.AddMinutes(double.Parse(jwtSettings["ExpiresInMinutes"]!)),
            signingCredentials: creds
        );

        var jwt = new JwtSecurityTokenHandler().WriteToken(token);

        return Results.Ok(new
        {
            token = jwt,
            role = request.Role,
            user_id = userId
        });
    }
    catch (IdNotFoundException)
    {
        return Results.NotFound(new { message = "User not found" });
    }
})
.WithName("Login")
.WithOpenApi();

app.MapPost("/api/v1/auth/customer/register", (ICustomerService customerService, CustomerInfoWDTO customerInfo) =>
{
    try
    {
        var customer = customerService.GetByEmail(customerInfo.Email);
        return Results.BadRequest(new { message = "User with this email already exists" });
    }
    catch (IdNotFoundException)
    {

        var created = customerService.Create(customerInfo.WDTOtoDDTO());
        return Results.Created($"/api/v1/customers/{created.Id}", created);   
    }
})
.WithName("RegisterCustomer")
.WithOpenApi();

app.MapPost("/api/v1/auth/seller/register", (ISellerService sellerService, SellerInfoWDTO sellerInfo) =>
{
    try
    {
        var seller = sellerService.GetByEmail(sellerInfo.Email);
        return Results.BadRequest(new { message = "User with this email already exists" });
    }
    catch (IdNotFoundException)
    {
        var created = sellerService.Create(sellerInfo.WDTOtoDDTO());
        return Results.Created($"/api/v1/sellers/{created.Id}", created);  
    }
})
.WithName("RegisterSeller")
.WithOpenApi();

// Customer endpoints
app.MapGet("/api/v1/customers/{id}", (ICustomerService customerService, Guid id) =>
{
    try
    {
        var customer = customerService.GetById(new CustomerId(id));
        return Results.Ok(customer);
    }
    catch (IdNotFoundException)
    {
        return Results.NotFound(new { message = "Customer not found" });
    }
})
.RequireAuthorization("CustomerOnly")
.WithName("GetCustomerById")
.WithOpenApi();

// Order endpoints
app.MapGet("/api/v1/orders", (IOrderService orderService, HttpContext httpContext) =>
{
    var userId = httpContext.User.FindFirst("user_id")?.Value;
    var customerId = new CustomerId(Guid.Parse(userId!));
    var orders = orderService.GetOrderDetailsByCustomerId(customerId);
    return Results.Ok(orders);
})
.RequireAuthorization("CustomerOnly")
.WithName("GetCustomerOrders")
.WithOpenApi();

app.MapPost("/api/v1/orders", (
    IOrderService orderService,
    IOfferService offerService,
    ICustomerService customerService,
    HttpContext httpContext,
    CreateOrderRequest request) =>
{
    var userId = httpContext.User.FindFirst("user_id")?.Value;
    if (userId == null)
        return Results.Unauthorized();

    // Validate offer exists and has sufficient quantity
    try
    {
        var offer = offerService.GetById(new OfferId(request.OfferId));
        if (request.Quantity == 0)
            return Results.BadRequest(new { message = "Empty order" });
        if (offer.Quantity < request.Quantity)
            return Results.BadRequest(new { message = "Insufficient quantity" });

        var order = new Order
        {
            Id = Guid.NewGuid(),
            CustomerId = Guid.Parse(userId),
            OfferId = request.OfferId,
            Quantity = request.Quantity,
            Status = OrderStatus.Created
        };

        var created = orderService.Create(order);
        return Results.Created($"/api/v1/orders/{created.Id}", created);
    }
    catch (ValidationException)
    {
        return Results.BadRequest(new { message = "Invalid request" });
    }
    catch (IdNotFoundException)
    {
        return Results.BadRequest(new { message = "Offer not found" });
    }
})
.RequireAuthorization("CustomerOnly")
.WithName("CreateOrder")
.WithOpenApi();

app.MapPost("/api/v1/orders/{orderId}/pay", (
    Guid orderId,
    IPaymentUseCase paymentUseCase,
    IOrderService orderService,
    ICustomerService customerService,
    IOfferService offerService,
    HttpContext httpContext,
    PaymentRequest paymentRequest) =>
{
    var userId = httpContext.User.FindFirst("user_id")?.Value;
    if (userId == null)
        return Results.Unauthorized();

    try
    {
        var order = orderService.GetById(new OrderId(orderId));
        if (order.Status != OrderStatus.Created)
            return Results.BadRequest(new { message = "Order cannot be paid" });

        var customer = customerService.GetById(new CustomerId(Guid.Parse(userId)));
        var offer = offerService.GetById(new OfferId(order.OfferId));
        
        var orderTotalAmount = offer.Price * order.Quantity;
        var pointsUsed = paymentRequest.Points?.Used ?? 0;
        var amountToPay = orderTotalAmount - pointsUsed;
        if (amountToPay < 0)
            amountToPay = 0;

        var paymentInfo = new PaymentInfo(
            totalAmount: amountToPay,
            points: new CustomerPoints(paymentRequest.Points?.Used ?? 0),
            cardNumber: paymentRequest.CardNumber ?? string.Empty,
            expirationDate: paymentRequest.ExpirationDate ?? string.Empty,
            cvc: paymentRequest.Cvc ?? string.Empty,
            paymentMethod: paymentRequest.PaymentMethod
        );

        var paymentResult = paymentUseCase.ProcessPayment(customer, order, offer, paymentInfo);
        
        if (paymentResult.IsSuccess)
            return Results.Ok(new { status = "paid", transaction_id = paymentResult.TransactionId });
        else
            return Results.BadRequest(new { message = "Payment failed", transaction_id = paymentResult.TransactionId });
    }
    catch (IdNotFoundException)
    {
        return Results.NotFound(new { message = "Order not found" });
    }
})
.RequireAuthorization("CustomerOnly")
.WithName("PayOrder")
.WithOpenApi();

// Review endpoints
app.MapPost("/api/v1/reviews", (
    IReviewService reviewService,
    IOrderService orderService,
    IProductService productService,
    IStoreService storeService,
    HttpContext httpContext,
    CreateReviewRequest request) =>
{
    var userId = httpContext.User.FindFirst("user_id")?.Value;
    if (userId == null)
        return Results.Unauthorized();

    try
    {
        // Check if order exists and belongs to customer
        var order = orderService.GetById(new OrderId(request.OrderId));
        if (order.CustomerId != Guid.Parse(userId))
            return Results.BadRequest(new { message = "Invalid order" });
        if (order.Status != OrderStatus.Payed)
            return Results.BadRequest(new { message = "Order not payed" });

        // Check if review already exists for this order
        var existingReview = reviewService.GetByOrderId(new OrderId(request.OrderId));
        if (existingReview != null)
            return Results.BadRequest(new { message = "Review already exists for this order" });

        var review = new Review
        {
            Id = Guid.NewGuid(),
            CustomerId = Guid.Parse(userId),
            OrderId = request.OrderId,
            Rating = request.Rating,
            ReviewText = request.ReviewText
        };

        var created = reviewService.Create(review);

        // Update product and store ratings
        var orderDetails = orderService.GetOrderDetailsByCustomerId(new CustomerId(Guid.Parse(userId)))
            .FirstOrDefault(od => od.OrderId == request.OrderId);

        if (orderDetails != null)
        {
            var product = productService.GetById(new ProductId(orderDetails.ProductId));
            if (product != null)
                productService.AddReview(product, request.Rating);

            var store = storeService.GetById(new StoreId(orderDetails.StoreId));
            if (product != null)
                productService.AddReview(product, request.Rating);
        }

        return Results.Created($"/api/v1/reviews/{created.Id}", created);
    }
    catch (IdNotFoundException)
    {
        return Results.BadRequest(new { message = "Invalid order/review" });
    }
})
.RequireAuthorization("CustomerOnly")
.WithName("CreateReview")
.WithOpenApi();

app.MapGet("/api/v1/reviews/{orderId}", (IReviewService reviewService, Guid orderId) =>
{
    var review = reviewService.GetByOrderId(new OrderId(orderId));
    return review is null ? Results.NotFound(new { message = "Review not found" }) : Results.Ok(review);
})
.RequireAuthorization("CustomerOnly")
.WithName("GetReview")
.WithOpenApi();

app.MapPatch("/api/v1/reviews/{orderId}", (
    Guid orderId,
    IReviewService reviewService,
    IOrderService orderService,
    HttpContext httpContext,
    ReviewInfoWDTO request) =>
{
    var userId = httpContext.User.FindFirst("user_id")?.Value;
    if (userId == null) 
        return Results.Unauthorized();

    try
    {
        // Check if order exists and belongs to customer
        var order = orderService.GetById(new OrderId(orderId));
        if (order.CustomerId != Guid.Parse(userId))
            return Results.BadRequest(new { message = "Invalid order" });
        if (order.Status != OrderStatus.Payed)
            return Results.BadRequest(new { message = "Order not payed" });

        // Check if review doesn't exists for this order
        var existingReview = reviewService.GetByOrderId(new OrderId(orderId));
        if (existingReview == null)
            return Results.BadRequest(new { message = "Review doesn't exists for this order" });

        var created = reviewService.UpdateInfo(existingReview, request.WDTOtoDDTO());

        return Results.Created($"/api/v1/reviews/{created.Id}", created);
    }
    catch (IdNotFoundException)
    {
        return Results.NotFound(new { message = "Order not found" });
    }
})
.RequireAuthorization("CustomerOnly")
.WithName("UpdateReview")
.WithOpenApi();

app.MapDelete("/api/v1/reviews/{orderId}", (IReviewService reviewService, Guid orderId, HttpContext httpContext) =>
{
    var userId = httpContext.User.FindFirst("user_id")?.Value;

    try
    {
        var review = reviewService.GetByOrderId(new OrderId(orderId));
        if (review == null)
            return Results.NotFound(new { message = "Review not found for this order" });

        // Проверяем что отзыв принадлежит текущему пользователю
        if (review.CustomerId != Guid.Parse(userId!))
            return Results.Forbid();

        // Удаляем отзыв
        var result = reviewService.DeleteById(new ReviewId(review.Id));

        return Results.NoContent();
    }
    catch (IdNotFoundException)
    {
        return Results.NotFound(new { message = "Review not found for deletion" });
    }
})
.RequireAuthorization("CustomerOnly")
.WithName("DeleteReview")
.WithOpenApi();

// Favorite endpoints
app.MapGet("/api/v1/favorites", (IFavoriteService favoriteService, HttpContext httpContext) =>
{
    var userId = httpContext.User.FindFirst("user_id")?.Value;
    if (userId == null) 
        return Results.Unauthorized();
    var favorites = favoriteService.GetFavoriteDetailsByCustomerId(new CustomerId(Guid.Parse(userId)));
    return Results.Ok(favorites);
})
.RequireAuthorization("CustomerOnly")
.WithName("GetFavorites")
.WithOpenApi();

app.MapPost("/api/v1/favorites", (
    IFavoriteService favoriteService,
    HttpContext httpContext,
    CreateFavoriteRequest request) =>
{
    var userId = httpContext.User.FindFirst("user_id")?.Value;
    if (userId == null) 
        return Results.Unauthorized();

    var favorite = new Favorite
    {
        Id = Guid.NewGuid(),
        CustomerId = Guid.Parse(userId),
        ProductId = request.ProductId
    };

    try
    {
        var created = favoriteService.Create(favorite);
        return Results.Created($"/api/v1/favorites/{created.Id}", created);
    }
    catch (ValidationException)
    {
        return Results.BadRequest(new { message = "Validation failed" });
    }
})
.RequireAuthorization("CustomerOnly")
.WithName("CreateFavorite")
.WithOpenApi();

app.MapDelete("/api/v1/favorites/{favoriteId}", (IFavoriteService favoriteService, Guid favoriteId, HttpContext httpContext) =>
{
    var userId = httpContext.User.FindFirst("user_id")?.Value;
    try
    {
        var result = favoriteService.DeleteById(new FavoriteId(favoriteId));
        return result != null ? Results.NoContent() : Results.NotFound();
    }
    catch (IdNotFoundException)
    {
        return Results.NotFound(new { message = "Favorite not found" });
    }
})
.RequireAuthorization()
.WithName("DeleteFavorite")
.WithOpenApi();

// Product endpoints
app.MapGet("/api/v1/products", (IProductService productService, string? name = null) =>
{
    List<Product> products;
    if (string.IsNullOrEmpty(name))
        products = productService.GetByName("");
    else
        products = productService.GetByName(name);
    return Results.Ok(products);
})
.RequireAuthorization("CustomerOnly")
.WithName("GetProducts")
.WithOpenApi();

app.MapPost("/api/v1/products", (IProductService productService, ProductInfoWDTO productInfo) =>
{
    try
    {
        var created = productService.Create(productInfo.WDTOtoDDTO());
        return Results.Created($"/api/v1/products/{created.Id}", created);
    }
    catch (ValidationException)
    {
        return Results.BadRequest(new { message = "Validation failed" });
    }
})
.RequireAuthorization("AdminOnly")
.WithName("CreateProduct")
.WithOpenApi();

app.MapGet("/api/v1/products/{productId}", (IProductService productService, Guid productId) =>
{
    try
    {
        var product = productService.GetById(new ProductId(productId));
        return Results.Ok(product);
    }
    catch (IdNotFoundException)
    {
        return Results.NotFound(new { message = "Product not found" });
    }
})
.RequireAuthorization("CustomerOnly")
.WithName("GetProduct")
.WithOpenApi();

app.MapPut("/api/v1/products/{productId}", (IProductService productService, Guid productId, Product productInfo) =>
{
    try
    {
        var existingProduct = productService.GetById(new ProductId(productId));
        productService.UpdateName(existingProduct, productInfo.Name);
        productService.UpdateCategory(existingProduct, productInfo.Category);
        var resultingProduct = productService.UpdateDescription(existingProduct, productInfo.Description);
        return Results.Ok(resultingProduct);
    }
    catch (IdNotFoundException)
    {
        return Results.NotFound();
    }
    catch (ValidationException)
    {
        return Results.BadRequest(new { message = "Validation failed" });
    }
})
.RequireAuthorization("AdminOnly")
.WithName("UpdateProduct")
.WithOpenApi();

app.MapGet("/api/v1/products/{productId}/offers", (IOfferService offerService, Guid productId) =>
{
    var offers = offerService.GetOfferDetailsByProductId(new ProductId(productId));
    return Results.Ok(offers);
})
.RequireAuthorization("CustomerOnly")
.WithName("GetProductOffers")
.WithOpenApi();

// Store endpoints
app.MapGet("/api/v1/stores", (IStoreService storeService, HttpContext httpContext) =>
{
    var userId = httpContext.User.FindFirst("user_id")?.Value;
    if (userId == null)
        return Results.Unauthorized();

    try
    {
        var stores = storeService.GetBySellerId(new SellerId(Guid.Parse(userId)));
        return Results.Ok(stores);
    }
    catch (IdNotFoundException)
    {
        return Results.NotFound(new { message = "Store not found" });
    }
})
.RequireAuthorization("SellerOnly")
.WithName("GetSellerStores")
.WithOpenApi();

app.MapPost("/api/v1/stores", (IStoreService storeService, HttpContext httpContext, StoreInfoWDTO storeInfo) =>
{
    var userId = httpContext.User.FindFirst("user_id")?.Value;
    if (userId == null)
        return Results.Unauthorized();
    try
    {
        var created = storeService.Create(storeInfo.WDTOtoDDTO(), new SellerId(Guid.Parse(userId)));
        return Results.Created($"/api/v1/stores/{created.Id}", created);
    }
    catch (ValidationException)
    {
        return Results.BadRequest(new { message = "Validation failed" });
    }
})
.RequireAuthorization("SellerOnly")
.WithName("CreateStore")
.WithOpenApi();

app.MapPut("/api/v1/stores/{storeId}", (IStoreService storeService, Guid storeId, StoreInfoWDTO storeInfo, HttpContext httpContext) =>
{
    var userId = httpContext.User.FindFirst("user_id")?.Value;
    if (userId == null) 
        return Results.Unauthorized();

    try
    {
        var existingStore = storeService.GetById(new StoreId(storeId));
        if (existingStore.OwnerSellerId != Guid.Parse(userId))
            return Results.Unauthorized();

        var store = storeService.Update(existingStore, storeInfo.WDTOtoDDTO());

        return Results.Ok(store);
    }
    catch (IdNotFoundException)
    {
        return Results.NotFound(new { message = "Store not found" });
    }
    catch (ValidationException)
    {
        return Results.BadRequest(new { message = "Validation failed" });
    }
})
.RequireAuthorization("SellerOnly")
.WithName("UpdateStore")
.WithOpenApi();

app.MapGet("/api/v1/stores/{storeId}/offers", (IOfferService offerService, Guid storeId) =>
{
    try
    {
        var offers = offerService.GetByStoreId(new StoreId(storeId));
        return Results.Ok(offers);
    }
    catch (IdNotFoundException)
    {
        return Results.NotFound(new { message = "Offer not found" });
    }
})
.RequireAuthorization("SellerOnly")
.WithName("GetStoreOffers")
.WithOpenApi();

app.MapPost("/api/v1/stores/{storeId}/offers", (
    IOfferService offerService,
    IStoreService storeService,
    Guid storeId,
    HttpContext httpContext,
    OfferInfoWDTO offerInfo) =>
{
    var userId = httpContext.User.FindFirst("user_id")?.Value;
    if (userId == null) 
        return Results.Unauthorized();

    try
    {
        var store = storeService.GetById(new StoreId(storeId));
        if (store.OwnerSellerId != Guid.Parse(userId))
            return Results.BadRequest(new { message = "Invalid store" });

        var created = offerService.Create(offerInfo.WDTOtoDDTO());
        return Results.Created($"/api/v1/offers/{created.Id}", created);
    }
    catch (IdNotFoundException)
    {
        return Results.NotFound(new { message = "Store not found" });
    }
    catch (ValidationException)
    {
        return Results.BadRequest(new { message = "Validation failed" });
    }
})
.RequireAuthorization("SellerOnly")
.WithName("CreateStoreOffer")
.WithOpenApi();

// Offer endpoints
app.MapPut("/api/v1/offers/{offerId}", (
    IOfferService offerService,
    IStoreService storeService,
    Guid offerId,
    HttpContext httpContext,
    OfferUpdateInfoWDTO offerInfo) =>
{
    try
    {
        var userId = httpContext.User.FindFirst("user_id")?.Value;
        if (userId == null)
            return Results.Unauthorized();

        var existingOffer = offerService.GetById(new OfferId(offerId));
        var store = storeService.GetById(new StoreId(existingOffer.StoreId));
        if (store.OwnerSellerId != Guid.Parse(userId))
            return Results.BadRequest(new { message = "Invalid store" });

        var offer = offerService.UpdatePrice(existingOffer, offerInfo.Price);
        offer = offerService.UpdateQuantity(offer, offerInfo.Quantity);
        offer = offerService.UpdateDeliveryTime(offer, offerInfo.DeliveryTime);
        return Results.Ok(offer);
    }
    catch (IdNotFoundException)
    {
        return Results.NotFound();
    }
    catch (ValidationException)
    {
        return Results.BadRequest(new { message = "Validation failed" });
    }
})
.RequireAuthorization("SellerOnly")
.WithName("UpdateOffer")
.WithOpenApi();

app.Run();
