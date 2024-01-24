#include "../include/ApiClient.h"
#include "../include/ArbitrageDetector.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

//g++ -std=c++11 -o myprogram main.cpp ApiClient.cpp ArbitrageDetector.cpp -lcurl -I/opt/homebrew/Cellar/jsoncpp/1.9.5/include/  
//g++ -std=c++11 -o myprogram main.cpp ApiClient.cpp ArbitrageDetector.cpp -lcurl -I/opt/homebrew/Cellar/jsoncpp/1.9.5/include/ -L/opt/homebrew/Cellar/jsoncpp/1.9.5/lib -ljsoncpp
//g++ -std=c++11 -o myprogram main.cpp ApiClient.cpp ArbitrageDetector.cpp -lcurl -I/Users/samuelbraun/Desktop/vcpkg/installed/arm64-osx/include/ -L/Users/samuelbraun/Desktop/vcpkg/installed/arm64-osx/lib -ljsoncpp
//g++ -std=c++17 -o myprogram main.cpp ApiClient.cpp ArbitrageDetector.cpp -lcurl -I/Users/samuelbraun/Desktop/vcpkg/installed/arm64-osx/include/ -L/Users/samuelbraun/Desktop/vcpkg/installed/arm64-osx/lib -ljsoncpp


int main() {

    // setting up API client
    std::string accessKey = "cffdfe213a72d94326edb6a8cb190076";
    std::string apiUrl = "http://api.exchangeratesapi.io/v1/latest?access_key=" + accessKey;
    ApiClient apiClient(apiUrl);
    
    // setting up arbitrage detector
    auto exchangeRates = apiClient.fetchRates();
    ArbitrageDetector arbitrageDetector(exchangeRates);

    // get user-selected base currency
    std::cout << "Enter base currency (e.g., USD, EUR, JPY): ";
    std::string baseCurrencyCode;
    std::getline(std::cin, baseCurrencyCode);
    
    arbitrageDetector.setBaseCurrency(baseCurrencyCode);
    arbitrageDetector.findArbitrageOpportunities();
    arbitrageDetector.printArbitrageOpportunities();


    

    return 0;
}