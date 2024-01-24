#include "../include/ArbitrageDetector.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class ArbitrageDetector {
public:
    ArbitrageDetector(const std::unordered_map<std::string, double>& rates);
    void setBaseCurrency(const std::string& baseCurrencyCode);
    void findArbitrageOpportunities();
    void printArbitrageOpportunities() const;

private:
    std::unordered_map<std::string, double> exchangeRates;
    std::tuple<std::string, double> baseCurrency;
    std::vector<std::tuple<std::string, std::string, double>> arbitrageOpportunities;
};

ArbitrageDetector::ArbitrageDetector(const std::unordered_map<std::string, double>& rates) 
    : exchangeRates(rates) {}

void ArbitrageDetector::setBaseCurrency(const std::string& baseCurrencyCode) {
    this -> baseCurrency = std::make_tuple(baseCurrencyCode, exchangeRates.at(baseCurrencyCode));
}

void ArbitrageDetector::findArbitrageOpportunities() {
    for (const auto& rate1 : exchangeRates) {
        for (const auto& rate2 : exchangeRates) {
            if (rate1.first != rate2.first) {
                double conversion1 = std::get<1>(baseCurrency) / rate1.second; // convert from base currency to first currency
                double conversion2 = rate2.second; // convert from first currency to second currency
                double conversionBack = conversion1 * conversion2 * exchangeRates.at(std::get<0>(baseCurrency)); // Convert back to base currency

                if (conversionBack > 1) {
                    arbitrageOpportunities.push_back(std::make_tuple(rate1.first, rate2.first, conversionBack));
                }
            }
        }
    }
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
