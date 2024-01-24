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

// Endpoint to fetch exchange rates
void handleGetRates(http_request request) {
    // Your existing code to fetch rates
    std::string accessKey = "cffdfe213a72d94326edb6a8cb190076"; // Fix the typo in "std:string"

    ApiClient apiClient("http://api.exchangeratesapi.io/v1/latest?access_key=" + accessKey);
    auto exchangeRates = apiClient.fetchRates();

    // Convert rates to JSON and send response
    json::value response = json::value::object();
    for (const auto& rate : exchangeRates) {
        response[rate.first] = json::value::number(rate.second);
    }

    request.reply(status_codes::OK, response);
}

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

    // Convert opportunities to JSON and send response
    json::value response = json::value::array();
    const auto& opportunities = arbitrageDetector.getArbitrageOpportunities();
    for (size_t i = 0; i < opportunities.size(); ++i) {
        auto& opportunity = opportunities[i];
        response[i] = json::value::object();
        response[i]["from"] = json::value::string(std::get<0>(opportunity));
        response[i]["to"] = json::value::string(std::get<1>(opportunity));
        response[i]["profit"] = json::value::number(std::get<2>(opportunity));
    }

    request.reply(status_codes::OK, response);
}

int main() {
    // Set up the HTTP listener
    listener = std::make_unique<http_listener>(U("http://localhost:8080"));

    // Define the endpoints
    listener->support(methods::GET, [](http_request request) {
        auto path = uri::split_path(uri::decode(request.relative_uri().path()));
        if (!path.empty()) {
            if (path[0] == "rates") {
                handleGetRates(request);
            } else if (path[0] == "arbitrage") {
                handleFindArbitrage(request);
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
