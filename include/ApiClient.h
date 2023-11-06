#ifndef API_CLIENT_H
#define API_CLIENT_H

#include <string>
#include <unordered_map>

class ApiClient {
public:
    ApiClient(const std::string& apiUrl);
    std::unordered_map<std::string, double> fetchExchangeRates();

private:
    std::string apiUrl_;
};

#endif