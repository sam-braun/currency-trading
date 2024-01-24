#include "../include/ArbitrageDetector.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

ArbitrageDetector::ArbitrageDetector(const std::unordered_map<std::string, double>& rates) 
    : exchangeRates(rates) {}

void ArbitrageDetector::setBaseCurrency(const std::string& baseCurrencyCode) {
    this -> baseCurrency = std::make_tuple(baseCurrencyCode, exchangeRates.at(baseCurrencyCode));
}

// void ArbitrageDetector::findArbitrageOpportunities() {
//     for (const auto& rate1 : exchangeRates) {
//         for (const auto& rate2 : exchangeRates) {
//             if (rate1.first != rate2.first) {
//                 double conversion1 = std::get<1>(baseCurrency) / rate1.second; // convert from base currency to first currency
//                 double conversion2 = rate2.second; // convert from first currency to second currency
//                 double conversionBack = conversion1 * conversion2 * exchangeRates.at(std::get<0>(baseCurrency)); // Convert back to base currency

//                 if (conversionBack > 1) {
//                     arbitrageOpportunities.push_back(std::make_tuple(rate1.first, rate2.first, conversionBack));
//                 }
//             }
//         }
//     }
// }

void ArbitrageDetector::findArbitrageOpportunities() {
    double baseRate = exchangeRates.at(std::get<0>(baseCurrency)); // Rate of the base currency

    for (const auto& rate1 : exchangeRates) {
        for (const auto& rate2 : exchangeRates) {
            if (rate1.first != rate2.first && rate1.first != std::get<0>(baseCurrency) && rate2.first != std::get<0>(baseCurrency)) {
                double conversion1 = baseRate / rate1.second; // convert from base currency to first currency
                double conversion2 = rate1.second / rate2.second; // convert from first currency to second currency
                double conversionBackToBase = conversion2 * rate2.second / baseRate; // Convert back to base currency

                if (conversionBackToBase > 1) {
                    arbitrageOpportunities.push_back(std::make_tuple(rate1.first, rate2.first, conversionBackToBase));
                }
            }
        }
    }
}


std::vector<std::tuple<std::string, std::string, double>> ArbitrageDetector::getArbitrageOpportunities() {
    return arbitrageOpportunities;
}

void ArbitrageDetector::printArbitrageOpportunities() const {
    if (arbitrageOpportunities.empty()) {
        std::cout << "No arbitrage opportunities found." << std::endl;
    } else {
        for (const auto& opportunity : arbitrageOpportunities) {
            std::cout << "Arbitrage Opportunity: "
                      << std::get<0>(baseCurrency) << " -> " << std::get<0>(opportunity)
                      << " -> " << std::get<1>(opportunity)
                      << " -> " << std::get<0>(baseCurrency) << ", Profit: " << std::get<2>(opportunity)
                      << std::endl;
        }
    }
}
