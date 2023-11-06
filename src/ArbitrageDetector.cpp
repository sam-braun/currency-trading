#include "include/ArbitrageDetector.h"
#include <string>
#include <vector>
#include <unordered_map>

class ArbitrageDetector {
public:
    struct ArbitrageOpportunity {
        std::vector<std::string> route;
        double rate;
    };

    void ArbitrageDetector::setCurrencyData(std::unordered_map<std::string, double> exchangeRates) {
        exchangeRates_ = exchangeRates;
    }

    double getExchangeRate(const std::string& baseCurrency, const std::string& targetCurrency) {

        // TODO
    }

    std::vector<std::string> ArbitrageDetector::findArbitrageOpps() {
        std::vector<std::string> opportunities;
        
        for (const auto& entryA : exchangeRates) {
                std::string currencyA = entryA.first.substr(0, 3);

                // loop through each other currency to find a potential arbitrage loop
                for (const auto& entryB : exchangeRates) {
                    std::string currencyB = entryB.first.substr(0, 3);

                    if (currencyA != currencyB) {
                        double rateAB = getExchangeRate(currencyA, currencyB);

                        for (const auto& entryC : exchangeRates) {
                            std::string currencyC = entryC.first.substr(0, 3);

                            if (currencyC != currencyA && currencyC != currencyB) {
                                double rateBC = getExchangeRate(currencyB, currencyC);
                                double rateCA = getExchangeRate(currencyC, currencyA);

                                // check if there's an arbitrage opportunity
                                if (rateAB * rateBC * rateCA > 1) {
                                    ArbitrageOpportunity opportunity;
                                    opportunity.route = {currencyA, currencyB, currencyC, currencyA};
                                    opportunity.rate = rateAB * rateBC * rateCA;
                                    opportunities.push_back(opportunity);
                                }
                            }
                        }
                    }
                }
            }

        return opportunities;
    }

    private:
        std::unordered_map<std::string, double> exchangeRates;

        double getExchangeRate(const std::string& currency1, const std::string& currency2) {
            std::string rateKey = currency1 + currency2;
            auto it = exchangeRates.find(rateKey);
            if (it != exchangeRates.end()) {
                return it->second;
            }

            return 0.0;
        }
    }; 