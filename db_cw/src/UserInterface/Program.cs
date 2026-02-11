using System;
using System.IO;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Logging;
using Serilog;
using UserInterface;

internal static class Program
{
        static int Main(string[] args)
    {
        var configuration = new ConfigurationBuilder()
            .SetBasePath(Directory.GetCurrentDirectory())
            .AddJsonFile("appsettings.json", optional: false, reloadOnChange: true)
            .Build();

        Log.Logger = new LoggerConfiguration()
                .ReadFrom.Configuration(configuration) // reads Serilog section
                .CreateLogger();

        try
        {
            Log.Information("Application starting up");

            using var loggerFactory = LoggerFactory.Create(builder =>
            {
                builder.AddSerilog(Log.Logger, dispose: true);
            });

            var logger = loggerFactory.CreateLogger<Application>();

            var connectionString = configuration.GetConnectionString("MarketplaceDb")!;
            var priceCoef = configuration.GetValue<double>("Business:RecommendationPriceCoef");
            var deliveryTimeCoef = configuration.GetValue<double>("Business:RecommendationDeliveryTimeCoef");

            var app = new Application(connectionString, configuration, logger, priceCoef, deliveryTimeCoef);
            app.Run();

            return 0;
        }
        catch (Exception ex)
        {
            Log.Fatal(ex, "Unhandled exception");
            return 1;
        }
        finally
        {
            Log.CloseAndFlush();
        }
    }
}
