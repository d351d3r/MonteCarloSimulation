#include "Statistics.hpp"
#include <cmath>  // for sqrt
#include <iostream>
#include <numeric>
#include <vector>

namespace Analysis {
void Statistics::analyze(const std::vector<double>& data) {
  std::cout << "Analyzing results..." << std::endl;
  double mean = calculateMean(data);
  double variance = calculateVariance(data);
  double stdDev = std::sqrt(variance);

  std::cout << "Mean: " << mean << ", Variance: " << variance
            << ", Std Dev: " << stdDev << std::endl;
}

double Statistics::calculateMean(const std::vector<double>& data) {
  std::cout << "Calculating mean..." << std::endl;

  if (data.empty())
    return 0.0;
    
  double sum = std::accumulate(data.begin(), data.end(), 0.0);
  
  return sum / data.size();
  
}

double Statistics::calculateVariance(const std::vector<double>& data) {
  std::cout << "Calculating variance..." << std::endl;

  if (data.empty())
    return 0.0;
  double mean = calculateMean(data);
  std::cout << "Mean calculated: " << mean << std::endl;

  double sqSum =
      std::inner_product(data.begin(), data.end(), data.begin(), 0.0);
     // std::cout << "Variance calculated: " << variance << std::endl;

  return sqSum / data.size() - mean * mean;
  
}
}  // namespace Analysis
