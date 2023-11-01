#ifndef ARBITRAGE_DETECTOR_H
#define ARBITRAGE_DETECTOR_H

#include <string>
#include <vector>
#include <unordered_map>

class ArbitrageDetector {
public:
    void setCurrencyData(std::unordered_map<std::string, double> exchangeRates);
    double getExchangeRate(const std::string& baseCurrency, const std::string& targetCurrency);
    std::vector<std::string> findArbitrageOpps();
    
private:
    std::unordered_map<std::string, double> exchangeRates_;
};

#endif