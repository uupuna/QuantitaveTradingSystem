#ifndef RANDOM_FOREST_STRATEGY_H
#define RANDOM_FOREST_STRATEGY_H

#include <mlpack/core.hpp> 
#include <mlpack/methods/random_forest/random_forest.hpp>

enum class Signal {
    BUY,
    SELL,
    HOLD
};

class RandomForestStrategy {
private:
    mlpack::methods::random_forest::RandomForest<> forest; 

public:
    RandomForestStrategy();

    // Train the random forest model with given features and labels
    void trainModel(const arma::mat& features, const arma::Row<size_t>& labels);

    // Generate signals based on latest features
    Signal generateSignal(const arma::mat& latestFeatures);
};

#endif // RANDOM_FOREST_STRATEGY_H
