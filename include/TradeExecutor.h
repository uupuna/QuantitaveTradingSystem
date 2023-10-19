#pragma once

#include "Database.h"
#include <string>

class TradeExecutor {
public:
    explicit TradeExecutor(Database& db);
    struct TradeResult {
        bool success;
        float executionPrice;
        std::string errorMessage;
    };

    /**
     * Executes a trade based on provided information.
     *
     * @param ticker    Stock ticker symbol.
     * @param price     Execution price.
     * @param quantity  Number of units to trade.
     * @param isBuy     True for buying, false for selling.
     */
    
    TradeResult executeTrade(const std::string& ticker, float price, int quantity, bool isBuy);

private:
    Database& m_db;
};
