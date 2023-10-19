// #pragma once
// #include <vector>

// class Database {
// public:
//     void saveTrade(float price, int quantity, bool isBuy); // Saves a trade to the database
// };


#pragma once

#include <string>
#include <vector>
#include <sqlite3.h>

class Database {
public:
    Database(const std::string& db_name);
    ~Database();

    void createTables();
    void insertPriceData(const std::string& ticker, double price);
    void insertTradeData(const std::string& ticker, const std::string& action, double price, int quantity);
    void saveTradeData(const std::string& ticker, const std::string& action, double price, int quantity);


    //... (Additional functions as required)

private:
    sqlite3* db;
};
