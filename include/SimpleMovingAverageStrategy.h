#pragma once
#include <vector>

enum class Signal {
    BUY, SELL, HOLD
};

class SimpleMovingAverageStrategy {
public:
    Signal generateSignal(const std::vector<float>& data);
};
