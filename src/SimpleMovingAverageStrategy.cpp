#include "SimpleMovingAverageStrategy.h"

Signal SimpleMovingAverageStrategy::generateSignal(const std::vector<float>& data) {
    // Simplified SMA strategy
    if (data.size() < 2) {
        return Signal::HOLD;
    }

    float sma = 0;
    for (float price : data) {
        sma += price;
    }
    sma /= data.size();

    if (data.back() > sma) {
        return Signal::BUY;
    } else {
        return Signal::SELL;
    }
}
