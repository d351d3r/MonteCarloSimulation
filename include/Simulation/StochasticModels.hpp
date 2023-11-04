#pragma once
#include <vector>

namespace Simulation {
    class StochasticModels {
    public:
        static void initialize();
        static std::vector<double> geometricBrownianMotion(double initialPrice, double volatility, double drift, int steps);
    };
}