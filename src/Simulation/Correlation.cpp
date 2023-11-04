#include "Correlation.hpp"
#include <iostream>
#include <vector>
#include <numeric>  // for std::accumulate
#include <cmath>    // for std::sqrt

namespace Simulation {
    void Correlation::initialize() {
        std::cout << "Correlation models initialized." << std::endl;
    }

    std::vector<std::vector<double>> Correlation::generateCorrelatedData(const std::vector<std::vector<double>>& inputData) {
        // Implement data correlation logic here
        // For this example, simply returning the input data as is
        std::cout << "Correlated data generated." << std::endl;
        return inputData;
    }

    double Correlation::calculateCorrelation(const std::vector<double>& series1, const std::vector<double>& series2) {
        double mean1 = std::accumulate(series1.begin(), series1.end(), 0.0) / series1.size();
        double mean2 = std::accumulate(series2.begin(), series2.end(), 0.0) / series2.size();
        double numerator = 0.0, den1 = 0.0, den2 = 0.0;
        for (size_t i = 0; i < series1.size(); ++i) {
            numerator += (series1[i] - mean1) * (series2[i] - mean2);
            den1 += (series1[i] - mean1) * (series1[i] - mean1);
            den2 += (series2[i] - mean2) * (series2[i] - mean2);
        }
        return numerator / std::sqrt(den1 * den2);
    }
}