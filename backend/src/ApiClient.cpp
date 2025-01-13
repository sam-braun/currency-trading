#include "../include/ApiClient.h"
#include <curl/curl.h>
#include <sstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json; // alias

// callback function to write received data to string buffer
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
        return 0;
    }
}

// constructor initializes api client with base currency
ApiClient::ApiClient(const std::string &base) : m_base(base) {}

// fetches current exchange rates from external api service
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
        std::string url = "https://api.apilayer.com/exchangerates_data/latest?base=" + m_base;
        
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "apikey: O1pgs4kxOCGZHKBDlhy3aE680xtjYXSh");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        res = curl_easy_perform(curl);
        
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK)
        {
            try
            {
                auto jsonData = json::parse(readBuffer);
                if (jsonData["success"].get<bool>())
                {
                    auto symbols = jsonData["rates"];
                    for (auto &[key, value] : symbols.items())
                    {
                        rates[key] = value.get<double>();
                    }
                }
                else
                {
                    std::cerr << "API Error: " << jsonData["error"]["info"].get<std::string>() << std::endl;
                }
            }
            catch (const json::exception &e)
            {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
            }
        }
        else
        {
            std::cerr << "Curl error: " << curl_easy_strerror(res) << std::endl;
        }
    }

    curl_global_cleanup();
    return rates;
}
