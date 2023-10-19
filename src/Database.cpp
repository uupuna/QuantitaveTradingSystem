#include "Database.h"
#include <iostream>

Database::Database(const std::string& db_name) {
    int rc = sqlite3_open(db_name.c_str(), &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        throw std::runtime_error("Failed to open database");
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

void Database::createTables() {
    char* errorMsg = nullptr;

    const char* sql_create_prices_table = 
        "CREATE TABLE IF NOT EXISTS HistoricalPrices ("
        "Ticker TEXT NOT NULL,"
        "Price REAL NOT NULL,"
        "Timestamp DATETIME DEFAULT CURRENT_TIMESTAMP"
        ");";
    
    int result = sqlite3_exec(db, sql_create_prices_table, 0, 0, &errorMsg);
    if (result != SQLITE_OK) {
        std::cerr << "Error creating HistoricalPrices table: " << errorMsg << std::endl;
        sqlite3_free(errorMsg);
        throw std::runtime_error("Failed to create HistoricalPrices table");
    }

    const char* sql_create_trades_table =
        "CREATE TABLE IF NOT EXISTS Trades ("
        "Ticker TEXT NOT NULL,"
        "Action TEXT NOT NULL,"
        "Price REAL NOT NULL,"
        "Quantity INT NOT NULL,"
        "Timestamp DATETIME DEFAULT CURRENT_TIMESTAMP"
        ");";

    result = sqlite3_exec(db, sql_create_trades_table, 0, 0, &errorMsg);
    if (result != SQLITE_OK) {
        std::cerr << "Error creating Trades table: " << errorMsg << std::endl;
        sqlite3_free(errorMsg);
        throw std::runtime_error("Failed to create Trades table");
    }
}

void Database::insertPriceData(const std::string& ticker, double price) {
    const char* sql = "INSERT INTO HistoricalPrices (Ticker, Price) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    sqlite3_bind_text(stmt, 1, ticker.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, price);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to insert price data");
    }
    sqlite3_finalize(stmt);
}

void Database::insertTradeData(const std::string& ticker, const std::string& action, double price, int quantity) {
    const char* sql = "INSERT INTO Trades (Ticker, Action, Price, Quantity) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    sqlite3_bind_text(stmt, 1, ticker.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, action.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, price);
    sqlite3_bind_int(stmt, 4, quantity);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        throw std::runtime_error("Failed to insert trade data");
    }
    sqlite3_finalize(stmt);
}
