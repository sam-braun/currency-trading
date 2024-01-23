#include "ArbitrageDetector.h"
#include <iostream>
#include <algorithm>
#include <limits>

ArbitrageDetector::ArbitrageDetector() {}

void ArbitrageDetector::setCurrencyData(const std::unordered_map<std::string, double>& rates) {
    this->exchangeRates = rates;
}

void ArbitrageDetector::findArbitrageOpportunities(const std::vector<std::string>& currencies) {
    int n = currencies.size();
    // Matrix to store the converted rates
    std::vector<std::vector<double>> rateMatrix(n, std::vector<double>(n, 0.0));

    // Initialize the rate matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                rateMatrix[i][j] = 1.0;
            } else {
                std::string pair = currencies[i] + "-" + currencies[j];
                if (exchangeRates.find(pair) != exchangeRates.end()) {
                    rateMatrix[i][j] = exchangeRates[pair];
                }
            }
        }
    }

    // Detect arbitrage opportunities using Bellman-Ford algorithm
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rateMatrix[i][k] * rateMatrix[k][j] > rateMatrix[i][j]) {
                    rateMatrix[i][j] = rateMatrix[i][k] * rateMatrix[k][j];
                }
            }
        }
    }

    // Check for arbitrage opportunities
    for (int i = 0; i < n; ++i) {
        if (rateMatrix[i][i] > 1.0) {
            std::cout << "Arbitrage opportunity detected with currency: " << currencies[i] << std::endl;
        }
    }
}
