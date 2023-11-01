#include "ArbitrageDetector.h"

void ArbitrageDetector::setCurrencyData(std::unordered_map<std::string, double> exchangeRates) {
    exchangeRates_ = exchangeRates;
}

std::vector<std::string> ArbitrageDetector::findArbitrageOpps() {
    std::vector<std::string> opportunities;
    // TODO: finish function

    /*
    
    arbitrageOpportunities = []

    for each currencyA in exchangeRates:
        for each currencyB in exchangeRates:
            if currencyA != currencyB:
                rateAB = getExchangeRate(currencyA, currencyB)
                
                // triangular part
                for each currencyC in exchangeRates:
                    if currencyC != currencyA and currencyC != currencyB:
                        rateBC = getExchangeRate(currencyB, currencyC)
                        
                        rateCA = getExchangeRate(currencyC, currencyA)
                        
                        // arbitrage calulation
                        if rateAB * rateBC * rateCA > 1:
                            arbitrageOpportunity = {
                                'route': [currencyA, currencyB, currencyC, currencyA],
                                'rate': rateAB * rateBC * rateCA
                            }
                            arbitrageOpportunities.append(arbitrageOpportunity)

    
    */
    

    return opportunities;
}
