#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "../include/ApiClient.h"
#include "../include/ArbitrageDetector.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

std::unique_ptr<http_listener> listener;

// set CORS headers for HTTP response
void addCorsHeaders(http_response &response)
{
    response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
    response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, OPTIONS"));
    response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
}

// split a string of currencies separated by commas into a vector
std::vector<std::string> parseSelectedCurrencies(const std::string &selectedCurrenciesStr)
{
    std::vector<std::string> selectedCurrencies;
    std::istringstream stream(selectedCurrenciesStr);
    std::string currency;

    while (std::getline(stream, currency, ','))
    {
        selectedCurrencies.push_back(currency);
    }

    return selectedCurrencies;
}

// handle HTTP GET request to fetch exchange rates
void handleGetRates(http_request request)
{
    std::cout << "Handling GET request for /rates" << std::endl;
    try {
        ApiClient apiClient("EUR");  // Default to EUR as base currency
        auto exchangeRates = apiClient.fetchRates();

        json::value jsonResponse = json::value::object();
        for (const auto &rate : exchangeRates)
        {
            jsonResponse[rate.first] = json::value::number(rate.second);
        }

        http_response response(status_codes::OK);
        response.set_body(jsonResponse);
        addCorsHeaders(response);
        request.reply(response);
    }
    catch (const std::exception &e) {
        std::cerr << "Error in handleGetRates: " << e.what() << std::endl;
        request.reply(status_codes::InternalError, U("Internal Server Error"));
    }
}

// handle HTTP GET request to get available currencies
void handleGetAvailableCurrencies(http_request request)
{
    std::cout << "Handling GET request for /availableCurrencies" << std::endl;
    try {
        // Get available currencies from API
        ApiClient apiClient("EUR");
        auto exchangeRates = apiClient.fetchRates();
        ArbitrageDetector arbitrageDetector(exchangeRates);
        auto availableCurrencies = arbitrageDetector.getAvailableCurrencies();

        // Load currency information from CSV
        std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>> currencyInfoMap;
        std::ifstream file("../resources/currency_list.csv");
        std::string line;
        // Skip header
        std::getline(file, line);
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string code, name, symbol, emoji;
            
            // Parse CSV line
            if (!std::getline(iss, code, ',')) continue;
            if (!std::getline(iss, name, ',')) continue;
            if (!std::getline(iss, symbol, ',')) continue;
            if (!std::getline(iss, emoji, ',')) continue;
            
            currencyInfoMap[code] = std::make_tuple(name, symbol, emoji);
        }

        // Create response with currency details
        json::value jsonResponse = json::value::array();
        int index = 0;
        for (const auto& currencyCode : availableCurrencies)
        {
            json::value currencyObj = json::value::object();
            currencyObj["code"] = json::value::string(currencyCode);
            
            if (currencyInfoMap.find(currencyCode) != currencyInfoMap.end())
            {
                currencyObj["name"] = json::value::string(std::get<0>(currencyInfoMap[currencyCode]));
                currencyObj["symbol"] = json::value::string(std::get<1>(currencyInfoMap[currencyCode]));
                currencyObj["emoji"] = json::value::string(std::get<2>(currencyInfoMap[currencyCode]));
            }
            else
            {
                currencyObj["name"] = json::value::string(currencyCode);
                currencyObj["symbol"] = json::value::string(currencyCode);
                currencyObj["emoji"] = json::value::string("");
            }
            
            jsonResponse[index++] = currencyObj;
        }

        http_response response(status_codes::OK);
        response.set_body(jsonResponse);
        addCorsHeaders(response);
        request.reply(response);
    }
    catch (const std::exception &e) {
        std::cerr << "Error in handleGetAvailableCurrencies: " << e.what() << std::endl;
        request.reply(status_codes::InternalError, U("Internal Server Error"));
    }
}

// handle HTTP GET request to find arbitrage opportunities
void handleFindArbitrage(http_request request)
{
    std::cout << "handleFindArbitrage" << std::endl;
    try {
        auto query = uri::split_query(request.request_uri().query());
        std::string baseCurrencyCode = query["baseCurrency"];

        ApiClient apiClient(baseCurrencyCode);
        auto exchangeRates = apiClient.fetchRates();
        ArbitrageDetector arbitrageDetector(exchangeRates);
        arbitrageDetector.setBaseCurrency(baseCurrencyCode);
        arbitrageDetector.findArbitrageOpportunities();

        // convert opportunities to JSON
        json::value jsonResponse = json::value::array();
        const auto &opportunities = arbitrageDetector.getArbitrageOpportunities();
        
        // Sort opportunities by profit in descending order
        for (size_t i = 0; i < opportunities.size(); ++i)
        {
            auto &opportunity = opportunities[i];
            jsonResponse[i] = json::value::object();
            jsonResponse[i]["from"] = json::value::string(std::get<0>(opportunity));
            jsonResponse[i]["mid"] = json::value::string(std::get<1>(opportunity));
            jsonResponse[i]["to"] = json::value::string(std::get<2>(opportunity));
            jsonResponse[i]["profit"] = json::value::number(std::get<3>(opportunity));
        }

        // prepare and send HTTP response
        http_response response(status_codes::OK);
        response.set_body(jsonResponse);
        addCorsHeaders(response);
        request.reply(response);
    }
    catch (const std::exception &e) {
        std::cerr << "Error in handleFindArbitrage: " << e.what() << std::endl;
        request.reply(status_codes::InternalError, U("Internal Server Error"));
    }
}

// handle HTTP GET request to find arbitrage with selected currencies
void handleFindArbitrageWithSelectedCurrencies(http_request request)
{
    try {
        auto query = uri::split_query(request.request_uri().query());
        std::string baseCurrencyCode = query["baseCurrency"];
        std::vector<std::string> selectedCurrencies = parseSelectedCurrencies(query["selectedCurrencies"]);

        ApiClient apiClient(baseCurrencyCode);
        auto exchangeRates = apiClient.fetchRates();
        ArbitrageDetector arbitrageDetector(exchangeRates);

        arbitrageDetector.setCurrencies(baseCurrencyCode, selectedCurrencies);
        arbitrageDetector.findArbitrageOpportunities();

        // convert opportunities to JSON
        json::value jsonResponse = json::value::array();
        const auto &opportunities = arbitrageDetector.getArbitrageOpportunities();
        
        // Sort opportunities by profit in descending order
        for (size_t i = 0; i < opportunities.size(); ++i)
        {
            auto &opportunity = opportunities[i];
            jsonResponse[i] = json::value::object();
            jsonResponse[i]["from"] = json::value::string(std::get<0>(opportunity));
            jsonResponse[i]["mid"] = json::value::string(std::get<1>(opportunity));
            jsonResponse[i]["to"] = json::value::string(std::get<2>(opportunity));
            jsonResponse[i]["profit"] = json::value::number(std::get<3>(opportunity));
        }

        // prepare and send the HTTP response
        http_response response(status_codes::OK);
        response.set_body(jsonResponse);
        addCorsHeaders(response);
        request.reply(response);
    }
    catch (const std::exception &e) {
        std::cerr << "Error in handleFindArbitrageWithSelectedCurrencies: " << e.what() << std::endl;
        request.reply(status_codes::InternalError, U("Internal Server Error"));
    }
}

int main()
{
    utility::string_t port = U("8080");
    utility::string_t address = U("http://0.0.0.0:");
    address.append(port);

    listener = std::make_unique<http_listener>(address);

    listener->support(methods::OPTIONS, [](http_request request)
    {
        http_response response(status_codes::OK);
        addCorsHeaders(response);
        request.reply(response);
    });

    listener->support(methods::GET, [](http_request request)
    {
        std::cout << "Received GET request: " << utility::conversions::to_utf8string(request.relative_uri().path()) << std::endl;
        
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

    try
    {
        listener->open().wait();
        std::cout << "Listening on " << utility::conversions::to_utf8string(address) << std::endl;

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}