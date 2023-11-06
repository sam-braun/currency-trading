#include "crow.h"
#include "nlohmann/json.hpp"

nlohmann::json fetchCurrencyData() {
    return nlohmann::json::parse(R"({"USD": {"EUR": 0.85, "GBP": 0.75}, "EUR": {"USD": 1.18, "GBP": 0.88}, "GBP": {"USD": 1.33, "EUR": 1.14}})");
}

nlohmann::json detectArbitrage(const nlohmann::json& currencyData) {
    return nlohmann::json::parse(R"({"opportunity": {"currency_pair": "USD-EUR-GBP", "profit": 0.05}})");
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/currency-data")
        .methods(crow::HTTPMethod::Get)
    ([] {
        auto currencyData = fetchCurrencyData();
        return currencyData;
    });

    CROW_ROUTE(app, "/arbitrage")
        .methods(crow::HTTPMethod::Get)
    ([] {
        auto currencyData = fetchCurrencyData();
        auto arbitrageOpportunities = detectArbitrage(currencyData);
        return arbitrageOpportunities;
    });

    app.port(4000).multithreaded().run();
    return 0;
}




