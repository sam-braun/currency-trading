#ifndef APICLIENT_H
#define APICLIENT_H

#include <string>
#include <unordered_map>

class ApiClient {
public:
    ApiClient(const std::string& url);
    std::unordered_map<std::string, double> fetchRates();

private:
    std::string m_url;
};

#endif // APICLIENT_H