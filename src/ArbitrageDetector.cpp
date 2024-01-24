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

void ArbitrageDetector::findArbitrageOpportunities() {
    double baseRate = exchangeRates.at(std::get<0>(baseCurrency));
    std::string baseCode = std::get<0>(baseCurrency);

    for (const auto& rate1 : exchangeRates) {
        for (const auto& rate2 : exchangeRates) {
            if (rate1.first != rate2.first && rate1.first != baseCode && rate2.first != baseCode) {
                double conversion1 = 1 / rate1.second; // Convert base to first currency
                double conversion2 = conversion1 / rate2.second; // Convert first to second currency
                double conversionBackToBase = conversion2 * baseRate; // Convert second back to base currency

                if (conversionBackToBase > 1) {
                    arbitrageOpportunities.push_back(std::make_tuple(baseCode, rate1.first, rate2.first, conversionBackToBase));
                }
            }
        }
    }
}



std::vector<std::string> ArbitrageDetector::getAvailableCurrencies() {
    std::vector<std::string> availableCurrencies;
    for (const auto& rate : exchangeRates) {
        availableCurrencies.push_back(rate.first);
    }
    return availableCurrencies;
}


std::vector<std::tuple<std::string, std::string, std::string, double>> ArbitrageDetector::getArbitrageOpportunities() {
    return arbitrageOpportunities;
}

void ArbitrageDetector::printArbitrageOpportunities() const {
    if (arbitrageOpportunities.empty()) {
        std::cout << "No arbitrage opportunities found." << std::endl;
    } else {
        for (const auto& opportunity : arbitrageOpportunities) {
            std::cout << "Arbitrage Opportunity: " << std::get<0>(baseCurrency)
                      << " -> A" << std::get<0>(opportunity) 
                      << " -> B" << std::get<1>(opportunity)
                      << " -> C" << std::get<0>(baseCurrency)
                      << ", Profit: " << std::get<2>(opportunity)
                      << std::endl;
        }
    }
}
