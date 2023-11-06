#include "crow.h"
#include "nlohmann/json.hpp"
#include "include/ApiClient.h"  // Make sure this path is correct

int main() {
    crow::SimpleApp app;

    std::string accessKey = "your access key"
    std::string apiUrl = "http://api.exchangeratesapi.io/v1/latest?access_key=YOUR_ACCESS_KEY" + accessKey;
    
    ApiClient apiClient(apiUrl);
    
    auto exchangeRates = apiClient.fetchExchangeRates();
    
    CROW_ROUTE(app, "/currency-data")
    ([&exchangeRates]() -> crow::response {
        nlohmann::json currencyData = nlohmann::json(exchangeRates);
        return crow::response{currencyData.dump()};
    });

    CROW_ROUTE(app, "/arbitrage")
    ([&exchangeRates]() -> crow::response {
        auto arbitrageOpportunities = detectArbitrage(exchangeRates);
        nlohmann::json response = nlohmann::json(arbitrageOpportunities);
        return crow::response{response.dump()};
    });

    // app.port(4000).multithreaded().run();

    return 0;
}


