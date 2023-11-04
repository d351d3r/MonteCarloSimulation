#include "Statistics.hpp"
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath> // for sqrt

namespace Analysis {
    void Statistics::analyze(const std::vector<double>& data) {
        std::cout << "Analyzing results..." << std::endl;
        double mean = calculateMean(data);
        double variance = calculateVariance(data);
        double stdDev = std::sqrt(variance);
        
        std::cout << "Mean: " << mean << ", Variance: " << variance << ", Std Dev: " << stdDev << std::endl;
    }

    double Statistics::calculateMean(const std::vector<double>& data) {
        if (data.empty()) return 0.0;
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        return sum / data.size();
    }

    double Statistics::calculateVariance(const std::vector<double>& data) {
        if (data.empty()) return 0.0;
        double mean = calculateMean(data);
        double sqSum = std::inner_product(data.begin(), data.end(), data.begin(), 0.0);
        return sqSum / data.size() - mean * mean;
    }
}
