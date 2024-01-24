#ifndef ARBITRAGEDETECTOR_H
#define ARBITRAGEDETECTOR_H

#include <string>
#include <vector>
#include <unordered_map>
#include <tuple>

class ArbitrageDetector {
public:
    ArbitrageDetector(const std::unordered_map<std::string, double>& rates);
    void setBaseCurrency(const std::string& baseCurrencyCode);
    void setCurrencies(const std::string& baseCurrencyCode, const std::vector<std::string>& currencies);
    void findArbitrageOpportunities();
    std::vector<std::tuple<std::string, std::string, std::string, double>> getArbitrageOpportunities();
    std::vector<std::string> getAvailableCurrencies();
    void printArbitrageOpportunities() const;


private:
    std::tuple<std::string, double> baseCurrency;
    std::unordered_map<std::string, double> currencyMap;
    std::unordered_map<std::string, double> exchangeRates;
    std::vector<std::tuple<std::string, std::string, std::string, double>> arbitrageOpportunities;
};

#endif // ARBITRAGEDETECTOR_H