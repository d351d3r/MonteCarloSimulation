#ifndef STOCHASTICMODELS_HPP
#define STOCHASTICMODELS_HPP

#include <vector>

namespace Simulation {

    class StochasticModels {
    public:
        static void initialize();

        static std::vector<long double> geometricBrownianMotion(long double initialPrice, long double volatility, long double drift, int steps);

        static std::vector<long double> runMonteCarloSimulation(long double initialPrice, long double volatility, long double drift, int steps, int numSimulations);
    };

}  // namespace Simulation

#endif // STOCHASTICMODELS_HPP
