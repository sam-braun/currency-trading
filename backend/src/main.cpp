#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "../include/ApiClient.h"
#include "../include/ArbitrageDetector.h"
#include "../include/RateHandlers.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

std::unique_ptr<http_listener> listener;

// set CORS headers for HTTP response
void addCorsHeaders(http_response &response)
{
    response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
    response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, OPTIONS"));
    response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
}

int main()
{
    utility::string_t port = U("8080");
    utility::string_t address = U("http://0.0.0.0:");
    address.append(port);
    
    listener = std::make_unique<http_listener>(address);
    
    listener->support(methods::OPTIONS, [](http_request request)
    {
        http_response response(status_codes::OK);
        addCorsHeaders(response);
        request.reply(response);
    });

    listener->support(methods::GET, [](http_request request) {
        std::cout << "Received GET request: " << utility::conversions::to_utf8string(request.relative_uri().path()) << std::endl;
        
        auto path = uri::split_path(uri::decode(request.relative_uri().path()));
        if (!path.empty()) {
            if (path[0] == "rates") {
                rate_handlers::handleGetRates(request);
            }
            else if (path[0] == "availableCurrencies") {
                rate_handlers::handleGetAvailableCurrencies(request);
            }
            else if (path[0] == "arbitrage") {
                rate_handlers::handleFindArbitrage(request);
            }
            else if (path[0] == "arbitrageWithSelectedCurrencies") {
                rate_handlers::handleFindArbitrageWithSelectedCurrencies(request);
            }
            else {
                request.reply(status_codes::NotFound);
            }
        } else {
            request.reply(status_codes::NotFound);
        }
    });

    try
    {
        listener->open().wait();
        std::cout << "Listening on " << utility::conversions::to_utf8string(address) << std::endl;

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}