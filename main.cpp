#include "DataFetcher.h"
#include "SimpleMovingAverageStrategy.h"
#include "TradeExecutor.h"
#include "Database.h"
#include "PerformanceEvaluator.h"
#include <iostream>

int main() {
    try {
        DataFetcher dataFetcher;
        SimpleMovingAverageStrategy strategy;
        Database db("trading_data.db");
        db.createTables();
        TradeExecutor executor(db);
        PerformanceEvaluator evaluator;

        auto data = dataFetcher.getHistoricalData("AAPL");
        Signal signal = strategy.generateSignal(data);

        if (signal == Signal::BUY) {
            executor.executeTrade(data.back(), 100, true);
        } else if (signal == Signal::SELL) {
            executor.executeTrade(data.back(), 100, false);
        }

        float initialBalance = 10000.0f;
        float finalBalance = signal == Signal::BUY ? initialBalance + 100 : initialBalance - 100;
        float returnPercentage = evaluator.calculateReturn(initialBalance, finalBalance) * 100;

        std::cout << "Portfolio Return: " << returnPercentage << "%" << std::endl;
    }catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) { 
        std::cerr << "Unknown error occurred." << std::endl; 
    }

    return 0;
}
