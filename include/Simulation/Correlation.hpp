#ifndef CORRELATION_HPP
#define CORRELATION_HPP

#include <vector>

namespace Simulation {
    class Correlation {
    public:
        static void initialize();
        static std::vector<std::vector<double>> generateCorrelatedData(const std::vector<std::vector<double>>& inputData);
        static double calculateCorrelation(const std::vector<double>& series1, const std::vector<double>& series2);
    };
}

#endif // CORRELATION_HPP