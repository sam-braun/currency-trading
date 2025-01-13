#pragma once

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <string>
#include <vector>

namespace rate_handlers {
    void addCorsHeaders(web::http::http_response &response);
    std::vector<std::string> parseSelectedCurrencies(const std::string &selectedCurrenciesStr);
    void handleGetRates(web::http::http_request request);
    void handleGetAvailableCurrencies(web::http::http_request request);
    void handleFindArbitrage(web::http::http_request request);
    void handleFindArbitrageWithSelectedCurrencies(web::http::http_request request);
}
