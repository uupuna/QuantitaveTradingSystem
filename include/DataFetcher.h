#pragma once
#include <string>
#include <vector>

class DataFetcher {
public:
    std::vector<float> getHistoricalData(const std::string& symbol);

private:
    std::string fetchData(const std::string& url);
    std::vector<float> parseData(const std::string& jsonData);
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};
