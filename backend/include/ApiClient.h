#pragma once

#include <string>
#include <unordered_map>

class ApiClient {
public:
    ApiClient(const std::string& base);
    std::unordered_map<std::string, double> fetchRates();

private:
    std::string m_base;
};