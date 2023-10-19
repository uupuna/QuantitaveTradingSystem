#include "TradeExecutor.h"
#include <iostream>

TradeExecutor::TradeExecutor(Database& db) : m_db(db) {}

void TradeExecutor::executeTrade(float price, int quantity, bool isBuy) {
    std::cout << (isBuy ? "Executing BUY" : "Executing SELL") << " order for " << quantity << " units @" << price << std::endl;
    m_db.insertTradeData("MYSTOCK", isBuy ? "BUY" : "SELL", price, quantity);

}

