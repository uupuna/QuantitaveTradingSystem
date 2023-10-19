#include "DataFetcher.h"
#include "SimpleMovingAverageStrategy.h"
#include "TradeExecutor.h"
#include "Database.h"
#include "PerformanceEvaluator.h"
#include <iostream>
#include <map>

int main() {
    try {
        DataFetcher dataFetcher;
        SimpleMovingAverageStrategy strategy;
        Database db("trading_data.db");
        db.createTables();
        TradeExecutor executor(db);
        PerformanceEvaluator evaluator;

        std::string ticker = "AAPL";  // For simplicity, using hardcoded ticker.

        auto data = dataFetcher.getHistoricalData(ticker);
        Signal signal = strategy.generateSignal(data);

        TradeExecutor::TradeResult result = {false, 0.0f, "No trade executed"};
        if (signal == Signal::BUY) {
            result = executor.executeTrade(ticker, data.back(), 100, true);
        } else if (signal == Signal::SELL) {
            result = executor.executeTrade(ticker, data.back(), 100, false);
        }

        if (result.success) {
            std::cout << "Trade executed successfully at price: " << result.executionPrice << std::endl;
        } else {
            std::cout << "Trade execution failed. Reason: " << result.errorMessage << std::endl;
            return 1;  // Exiting early since the trade failed.
        }

        float initialBalance = 10000.0f;  // Should come from the user's actual balance in a real-world scenario.
        float finalBalance = initialBalance;

        if (signal == Signal::BUY) {
            finalBalance -= result.executionPrice * 100;
        } else if (signal == Signal::SELL) {
            finalBalance += result.executionPrice * 100;
        }

        float returnPercentage = evaluator.calculateReturn(initialBalance, finalBalance);
        std::cout << "Portfolio Return: " << returnPercentage << "%" << std::endl;

        std::cout << "\nRecent Trades:" << std::endl;
        auto recentTrades = db.getRecentTrades(5);  // Get last 5 trades
        for (const auto& trade : recentTrades) {
            std::cout << trade.timestamp << ": " << trade.ticker << " " << trade.action << " " << trade.quantity << " units @" << trade.price << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) { 
        std::cerr << "Unknown error occurred." << std::endl; 
    }

    return 0;
}