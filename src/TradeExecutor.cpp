#include "TradeExecutor.h"
#include <iostream>

// Constructor definition
TradeExecutor::TradeExecutor(Database& db) : m_db(db) {
    // Any other initialization code if necessary
}

TradeExecutor::TradeResult TradeExecutor::executeTrade(const std::string& ticker, float price, int quantity, bool isBuy) {
    TradeResult result;

    try {
        std::cout << "Attempting to " << (isBuy ? "BUY" : "SELL") << " " << quantity << " units of " << ticker << " @" << price << std::endl;

        m_db.insertTradeData(ticker, isBuy ? "BUY" : "SELL", price, quantity);

        // Simulate a trade confirmation. In a real system, this might come from a brokerage or trading platform.
        std::cout << "Trade confirmed: " << (isBuy ? "Bought" : "Sold") << " " << quantity << " units of " << ticker << " @" << price << std::endl;

        result.success = true;
        result.executionPrice = price;

    } catch (const std::exception& e) {
        std::cerr << "Error executing trade: " << e.what() << std::endl;

        result.success = false;
        result.executionPrice = 0.0f;
        result.errorMessage = e.what();

    }

    return result;
}
