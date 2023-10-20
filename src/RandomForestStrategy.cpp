#include "RandomForestStrategy.h"
using namespace arma;
using namespace mlpack;
using namespace mlpack::tree;


RandomForestStrategy::RandomForestStrategy() {

}

void RandomForestStrategy::trainModel(const arma::mat& features, const arma::Row<size_t>& labels) {
    forest.Train(features, labels);
}

Signal RandomForestStrategy::generateSignal(const arma::mat& latestFeatures) {
    arma::Row<size_t> predictions;
    forest.Predict(latestFeatures, predictions);


    if (predictions(0) == 1) {
        return Signal::BUY;
    } else if (predictions(0) == 2) {
        return Signal::SELL;
    } else {
        return Signal::HOLD;
    }
}
