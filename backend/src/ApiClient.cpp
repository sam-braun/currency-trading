#include "../include/ApiClient.h"
#include <curl/curl.h>
#include <sstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json; // Alias for convenience

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size * nmemb;
    try
    {
        s->append((char *)contents, newLength);
        return newLength;
    }
    catch (std::bad_alloc &e)
    {
        // Handle memory problem
        return 0;
    }
}

ApiClient::ApiClient(const std::string &url) : m_url(url) {}

std::unordered_map<std::string, double> ApiClient::fetchRates()
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::unordered_map<std::string, double> rates;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, m_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK)
        {
            try
            {
                auto jsonData = json::parse(readBuffer);
                auto symbols = jsonData["rates"];
                for (auto &[key, value] : symbols.items())
                {
                    rates[key] = value.get<double>();
                }
            }
            catch (json::parse_error &e)
            {
                std::cerr << "JSON parse error: " << e.what() << std::endl;
            }
        }
    }
    return rates;
}
