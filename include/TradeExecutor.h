#pragma once
#include "Database.h"

class TradeExecutor {
public:
    TradeExecutor(Database& db);
    void executeTrade(float price, int quantity, bool isBuy);
private:
    Database& m_db;
};
