#include "headers/ApiClient.h"
#include <curl/curl.h>

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
            // TODO: handle error!!!


        } else {
            size_t startPos = 0, endPos = 0;
            while ((endPos = responseString.find('\n', startPos)) != std::string::npos) {
                std::string line = responseString.substr(startPos, endPos - startPos);
                size_t commaPos = line.find(',');
                std::string currencyPair = line.substr(0, commaPos);
                double rate = std::stod(line.substr(commaPos + 1));
                exchangeRates[currencyPair] = rate;
                startPos = endPos + 1;
            }
        }

        curl_easy_cleanup(curl);
    }

    return exchangeRates;
}
