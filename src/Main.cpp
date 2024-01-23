#include "include/ApiClient.h"
#include "include/ArbitrageDetector.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main() {

    // setting up API client
    std::string accessKey = "cffdfe213a72d94326edb6a8cb190076";
    std::string apiUrl = "http://api.exchangeratesapi.io/v1/latest?access_key=" + accessKey;
    ApiClient apiClient(apiUrl);
    
    // setting up arbitrage detector
    auto exchangeRates = apiClient.fetchRates();
    ArbitrageDetector arbitrageDetector;
    arbitrageDetector.setCurrencyData(exchangeRates);

    // get user-selected currencies
    std::cout << "Enter currencies (comma-separated, e.g., USD,EUR,JPY): ";
    std::string input;
    std::getline(std::cin, input);

    // extract currencies from input
    std::vector<std::string> currencies;
    std::istringstream ss(input);
    std::string currency;
    while (std::getline(ss, currency, ',')) {
        currencies.push_back(currency);
    }

    auto arbitrageOpportunities = arbitrageDetector.findArbitrageOpps();

    /*
    
    Write printing method here

    */


    return 0;
}