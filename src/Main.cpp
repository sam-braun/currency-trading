#include "../include/ApiClient.h"
#include "../include/ArbitrageDetector.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

//g++ -std=c++11 -o myprogram main.cpp ApiClient.cpp ArbitrageDetector.cpp -lcurl -I/opt/homebrew/Cellar/jsoncpp/1.9.5/include/  
//g++ -std=c++11 -o myprogram main.cpp ApiClient.cpp ArbitrageDetector.cpp -lcurl -I/opt/homebrew/Cellar/jsoncpp/1.9.5/include/ -L/opt/homebrew/Cellar/jsoncpp/1.9.5/lib -ljsoncpp


int main() {

    // setting up API client
    std::string accessKey = "cffdfe213a72d94326edb6a8cb190076";
    std::string apiUrl = "http://api.exchangeratesapi.io/v1/latest?access_key=" + accessKey;
    ApiClient apiClient(apiUrl);
    
    // setting up arbitrage detector
    auto exchangeRates = apiClient.fetchRates();
    ArbitrageDetector arbitrageDetector;
    arbitrageDetector.setCurrencyData(exchangeRates);


    // test printing exchange rates
    std::cout << "Fetched Exchange Rates:" << std::endl;
    for (const auto& rate : exchangeRates) {
        std::cout << rate.first << ": " << rate.second << std::endl;
    }


    // // get user-selected currencies
    // std::cout << "Enter currencies (comma-separated, e.g., USD,EUR,JPY): ";
    // std::string input;
    // std::getline(std::cin, input);

    // // extract currencies from input
    // std::vector<std::string> currencies;
    // std::istringstream ss(input);
    // std::string currency;
    // while (std::getline(ss, currency, ',')) {
    //     currencies.push_back(currency);
    // }

    // arbitrageDetector.findArbitrageOpportunities(currencies);


    /*
    
    Write printing method here

    */


    return 0;
}