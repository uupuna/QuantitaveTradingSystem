#include "DataFetcher.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>

std::vector<float> DataFetcher::getHistoricalData(const std::string& symbol) {
    std::string apiKey = "JTLWBH5VKOUNIOV3"; 
    std::string endpoint = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=" + symbol + "&apikey=" + apiKey;

    std::string jsonData = fetchData(endpoint);

    return parseData(jsonData);
}

std::string DataFetcher::fetchData(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

std::vector<float> DataFetcher::parseData(const std::string& jsonData) {
    std::vector<float> prices;
    
    try {
        nlohmann::json root = nlohmann::json::parse(jsonData);
        auto dailyPrices = root["Time Series (Daily)"];
        for (const auto& [date, priceData] : dailyPrices.items()) {
            if (priceData["4. close"].is_number()) {
                prices.push_back(priceData["4. close"].get<float>());
            } else if (priceData["4. close"].is_string()) {
                std::string closePriceStr = priceData["4. close"];
                try {
                    float closePrice = std::stof(closePriceStr);
                    prices.push_back(closePrice);
                } catch (const std::exception& ex) {
                    std::cerr << "Error converting string to float for date " << date << ": " << ex.what() << std::endl;
                }
            } else {
                std::cerr << "Unexpected data type for '4. close' on date " << date << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to parse JSON data: " << e.what() << std::endl;
        throw;
    }
    
    return prices;
}


size_t DataFetcher::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
