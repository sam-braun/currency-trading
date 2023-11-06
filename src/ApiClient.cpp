#include "include/ApiClient.h"
#include <curl/curl.h>
#include <json/json.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

ApiClient::ApiClient(const std::string& apiUrl) : apiUrl_(apiUrl) {}

std::unordered_map<std::string, double> ApiClient::fetchExchangeRates() {
    std::unordered_map<std::string, double> exchangeRates;
    CURL* curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl_.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        std::string responseString;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);

        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            curl_easy_cleanup(curl);
            return exchangeRates;
        }

        curl_easy_cleanup(curl);

        Json::Value jsonData;
        Json::Reader jsonReader;

        if(jsonReader.parse(responseString, jsonData)) {
            const Json::Value& rates = jsonData["rates"];
            for (Json::ValueIterator it = rates.begin(); it != rates.end(); ++it) {
                // Assuming each key in the JSON "rates" object is a currency code
                std::string currencyCode = it.key().asString();
                double rate = (*it).asDouble();
                exchangeRates[currencyCode] = rate;
            }
        } else {
            //TODO handle error





        }
    }

    return exchangeRates;
}