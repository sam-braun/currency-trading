#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <iostream>
#include <memory>
#include <string>
#include "../include/ApiClient.h"
#include "../include/ArbitrageDetector.h"

// g++ -std=c++17 -o arb_backend main.cpp ApiClient.cpp ArbitrageDetector.cpp -lcurl -lboost_system -lssl -lcrypto -lcpprest -I/Users/samuelbraun/Desktop/vcpkg/installed/arm64-osx/include/ -L/Users/samuelbraun/Desktop/vcpkg/installed/arm64-osx/lib -ljsoncpp


using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

std::unique_ptr<http_listener> listener;


// cross-origin resource sharing - CORS
void addCorsHeaders(http_response& response) {
    response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
    response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, OPTIONS"));
    response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With"));
}

std::vector<std::string> parseSelectedCurrencies(const std::string& selectedCurrenciesStr) {
    std::vector<std::string> selectedCurrencies;
    std::istringstream stream(selectedCurrenciesStr);
    std::string currency;

    while (std::getline(stream, currency, ',')) {
        selectedCurrencies.push_back(currency);
    }

    return selectedCurrencies;
}

// Endpoint to fetch exchange rates
void handleGetRates(http_request request) {
    // Your existing code to fetch rates
    std::string accessKey = "cffdfe213a72d94326edb6a8cb190076"; // Fix the typo in "std:string"

    ApiClient apiClient("http://api.exchangeratesapi.io/v1/latest?access_key=" + accessKey);
    auto exchangeRates = apiClient.fetchRates();

    json::value jsonResponse = json::value::object();
    for (const auto& rate : exchangeRates) {
        jsonResponse[rate.first] = json::value::number(rate.second);
    }

    http_response response(status_codes::OK);
    response.set_body(jsonResponse.serialize(), "application/json");
    addCorsHeaders(response);
    request.reply(response);
}

//NEWWWW

void handleGetAvailableCurrencies(http_request request) {
    // Your existing code to find arbitrage opportunities
    ApiClient apiClient("http://api.exchangeratesapi.io/v1/latest?access_key=cffdfe213a72d94326edb6a8cb190076");
    auto exchangeRates = apiClient.fetchRates();
    
    ArbitrageDetector arbitrageDetector(exchangeRates);
    auto availableCurrencies = arbitrageDetector.getAvailableCurrencies();

    json::value jsonResponse = json::value::array();
    for (size_t i = 0; i < availableCurrencies.size(); ++i) {
        jsonResponse[i] = json::value::string(availableCurrencies[i]);
    }

    http_response httpResponse(status_codes::OK);
    httpResponse.set_body(jsonResponse.serialize(), "application/json");
    addCorsHeaders(httpResponse);
    request.reply(httpResponse);
}

// end NEWWWW

// Endpoint to find arbitrage opportunities
void handleFindArbitrage(http_request request) {
    // Extract base currency code from request
    auto query = uri::split_query(request.request_uri().query());
    std::string baseCurrencyCode = query["baseCurrency"];

    // Your existing code to find arbitrage opportunities
    ApiClient apiClient("http://api.exchangeratesapi.io/v1/latest?access_key=cffdfe213a72d94326edb6a8cb190076");
    auto exchangeRates = apiClient.fetchRates();
    ArbitrageDetector arbitrageDetector(exchangeRates);
    arbitrageDetector.setBaseCurrency(baseCurrencyCode);
    arbitrageDetector.findArbitrageOpportunities();

    // Convert opportunities to JSON
    json::value jsonResponse = json::value::array();
    const auto& opportunities = arbitrageDetector.getArbitrageOpportunities();
    for (size_t i = 0; i < opportunities.size(); ++i) {
        auto& opportunity = opportunities[i];
        jsonResponse[i] = json::value::object();
        jsonResponse[i]["from"] = json::value::string(std::get<0>(opportunity));
        jsonResponse[i]["mid"] = json::value::string(std::get<1>(opportunity));
        jsonResponse[i]["to"] = json::value::string(std::get<2>(opportunity));
        jsonResponse[i]["profit"] = json::value::number(std::get<3>(opportunity));
    }

    // Prepare and send the HTTP response
    http_response response(status_codes::OK);
    response.set_body(jsonResponse.serialize(), "application/json");
    addCorsHeaders(response);
    request.reply(response);
}


void handleFindArbitrageWithSelectedCurrencies(http_request request) {
    // Extract base currency and selected currencies from request
    auto query = uri::split_query(request.request_uri().query());
    std::string baseCurrencyCode = query["baseCurrency"];
    std::vector<std::string> selectedCurrencies = parseSelectedCurrencies(query["selectedCurrencies"]);

    // Your existing code to find arbitrage opportunities
    ApiClient apiClient("http://api.exchangeratesapi.io/v1/latest?access_key=cffdfe213a72d94326edb6a8cb190076");
    auto exchangeRates = apiClient.fetchRates();
    ArbitrageDetector arbitrageDetector(exchangeRates);
    arbitrageDetector.setCurrencies(baseCurrencyCode, selectedCurrencies);
    arbitrageDetector.findArbitrageOpportunities();

    // Convert opportunities to JSON
    json::value jsonResponse = json::value::array();
    const auto& opportunities = arbitrageDetector.getArbitrageOpportunities();
    for (size_t i = 0; i < opportunities.size(); ++i) {
        auto& opportunity = opportunities[i];
        jsonResponse[i] = json::value::object();
        jsonResponse[i]["from"] = json::value::string(std::get<0>(opportunity));
        jsonResponse[i]["mid"] = json::value::string(std::get<1>(opportunity));
        jsonResponse[i]["to"] = json::value::string(std::get<2>(opportunity));
        jsonResponse[i]["profit"] = json::value::number(std::get<3>(opportunity));
    }

    // Prepare and send the HTTP response
    http_response response(status_codes::OK);
    response.set_body(jsonResponse.serialize(), "application/json");
    addCorsHeaders(response);
    request.reply(response);
}


int main() {
    listener = std::make_unique<http_listener>(U("http://localhost:8080"));

    listener->support(methods::OPTIONS, [](http_request request) {
        http_response response(status_codes::OK);
        addCorsHeaders(response);
        request.reply(response);
    });

    // define endpoints
    listener->support(methods::GET, [](http_request request) {
        auto path = uri::split_path(uri::decode(request.relative_uri().path()));
        if (!path.empty()) {
            if (path[0] == "rates") {
                handleGetRates(request);
            } else if (path[0] == "availableCurrencies") {
                handleGetAvailableCurrencies(request);
            } else if (path[0] == "arbitrage") {
                handleFindArbitrage(request);
            } else if (path[0] == "arbitrageWithSelectedCurrencies") {
                handleFindArbitrageWithSelectedCurrencies(request);
            } else {
                request.reply(status_codes::NotFound);
            }
        } else {
            request.reply(status_codes::NotFound);
        }
    });

    try {
        listener->open().wait();
        std::cout << "Listening on port 8080..." << std::endl;

        std::string line;
        std::getline(std::cin, line);
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
