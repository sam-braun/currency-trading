#ifndef ARBITRAGEDETECTOR_H
#define ARBITRAGEDETECTOR_H

#include <string>
#include <unordered_map>
#include <vector>

class ArbitrageDetector {
public:
    ArbitrageDetector();

    // Sets the exchange rates data
    void setCurrencyData(const std::unordered_map<std::string, double>& rates);

    // Finds and prints out arbitrage opportunities for the given currencies
    void findArbitrageOpportunities(const std::vector<std::string>& currencies);

private:
    // Stores exchange rates as a map, where the key is a currency pair (e.g., "USD-EUR") and the value is the rate
    std::unordered_map<std::string, double> exchangeRates;
};

#endif // ARBITRAGEDETECTOR_H
