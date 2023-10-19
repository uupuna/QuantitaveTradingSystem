#include "SimpleMovingAverageStrategy.h"
#include <numeric>  // for std::accumulate

Signal SimpleMovingAverageStrategy::generateSignal(const std::vector<float>& data) {
    // Validate the input
    if (data.size() < 50) {  // We're considering a longer data period for a better SMA calculation.
        return Signal::HOLD;
    }

    // Calculate short and long-term SMA
    float shortSMA = calculateSMA(data, 10);  // 10 days SMA
    float longSMA = calculateSMA(data, 50);   // 50 days SMA

    // Generate signal based on SMA crossover
    if (shortSMA > longSMA && data[data.size() - 11] <= data[data.size() - 51]) {
        return Signal::BUY;  // Short SMA crossed above Long SMA
    } else if (shortSMA < longSMA && data[data.size() - 11] >= data[data.size() - 51]) {
        return Signal::SELL;  // Short SMA crossed below Long SMA
    }

    return Signal::HOLD;
}

float SimpleMovingAverageStrategy::calculateSMA(const std::vector<float>& data, int days) const {
    if (data.size() < days) return 0;

    // Calculate the sum of the last 'days' prices
    float sum = std::accumulate(data.end() - days, data.end(), 0.0);

    return sum / days;
}
