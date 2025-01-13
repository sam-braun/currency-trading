#include "../include/RateHandlers.h"
#include "../include/ApiClient.h"
#include "../include/ArbitrageDetector.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unistd.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

namespace rate_handlers {

void addCorsHeaders(http_response &response)
{
    response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
    response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, OPTIONS"));
    response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
}

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

void handleGetAvailableCurrencies(http_request request)
{
    std::cout << "Handling GET request for /availableCurrencies" << std::endl;
    try {
        ApiClient apiClient("EUR");
        auto exchangeRates = apiClient.fetchRates();
        ArbitrageDetector arbitrageDetector(exchangeRates);
        auto availableCurrencies = arbitrageDetector.getAvailableCurrencies();

        std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>> currencyInfoMap;
        std::ifstream file("../resources/currency_list.csv");
        if (!file.is_open()) {
            std::cerr << "Failed to open currency_list.csv. Current working directory: ";
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                std::cerr << cwd << std::endl;
            }
            std::cerr << "Trying alternate path..." << std::endl;
            file.open("../../backend/resources/currency_list.csv");
            if (!file.is_open()) {
                std::cerr << "Failed to open currency_list.csv from alternate path." << std::endl;
                throw std::runtime_error("Could not open currency_list.csv");
            }
        }
        std::string line;
        std::getline(file, line);
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string code, name, symbol, emoji;
            
            if (!std::getline(iss, code, ',')) continue;
            if (!std::getline(iss, name, ',')) continue;
            if (!std::getline(iss, symbol, ',')) continue;
            if (!std::getline(iss, emoji, ',')) continue;
            
            currencyInfoMap[code] = std::make_tuple(name, symbol, emoji);
        }

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

        json::value jsonResponse = json::value::array();
        const auto &opportunities = arbitrageDetector.getArbitrageOpportunities();
        
        for (size_t i = 0; i < opportunities.size(); ++i)
        {
            auto &opportunity = opportunities[i];
            jsonResponse[i] = json::value::object();
            jsonResponse[i]["from"] = json::value::string(std::get<0>(opportunity));
            jsonResponse[i]["mid"] = json::value::string(std::get<1>(opportunity));
            jsonResponse[i]["to"] = json::value::string(std::get<2>(opportunity));
            jsonResponse[i]["profit"] = json::value::number(std::get<3>(opportunity));
        }

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

        json::value jsonResponse = json::value::array();
        const auto &opportunities = arbitrageDetector.getArbitrageOpportunities();
        
        for (size_t i = 0; i < opportunities.size(); ++i)
        {
            auto &opportunity = opportunities[i];
            jsonResponse[i] = json::value::object();
            jsonResponse[i]["from"] = json::value::string(std::get<0>(opportunity));
            jsonResponse[i]["mid"] = json::value::string(std::get<1>(opportunity));
            jsonResponse[i]["to"] = json::value::string(std::get<2>(opportunity));
            jsonResponse[i]["profit"] = json::value::number(std::get<3>(opportunity));
        }

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

}
