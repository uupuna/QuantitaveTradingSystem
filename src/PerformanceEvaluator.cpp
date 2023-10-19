#include "PerformanceEvaluator.h"

float PerformanceEvaluator::calculateReturn(float initialBalance, float finalBalance) {
    return (finalBalance - initialBalance) / initialBalance * 100;
}
