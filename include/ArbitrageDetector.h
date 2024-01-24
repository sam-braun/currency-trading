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
    void findArbitrageOpportunities();
    void printArbitrageOpportunities() const;

private:
    std::unordered_map<std::string, double> exchangeRates;
    std::tuple<std::string, double> baseCurrency;
    std::vector<std::tuple<std::string, std::string, double>> arbitrageOpportunities;
};

#endif // ARBITRAGEDETECTOR_H