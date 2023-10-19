#pragma once

#include <string>
#include <vector>
#include <sqlite3.h>

class Database {
public:
    struct TradeRecord {
        std::string ticker;
        std::string action;
        double price;
        int quantity;
        std::string timestamp;
    };
    
    Database(const std::string& db_name);
    ~Database();

    void createTables();
    void insertPriceData(const std::string& ticker, double price);
    void insertTradeData(const std::string& ticker, const std::string& action, double price, int quantity);
    void saveTradeData(const std::string& ticker, const std::string& action, double price, int quantity);

    std::vector<TradeRecord> getRecentTrades(int limit = 10);

private:
    sqlite3* db;
};