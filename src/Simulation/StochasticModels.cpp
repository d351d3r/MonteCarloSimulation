#include "StochasticModels.hpp"
#include <chrono>
#include <cmath>
#include <future>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

namespace Simulation {

void StochasticModels::initialize() {
    std::cout << "Stochastic models initialized." << std::endl;
}

// Обновляем функцию для использования типа long double
// std::vector<long double> StochasticModels::geometricBrownianMotion(long double initialPrice, long double volatility, long double drift, int steps) {
//     if (initialPrice <= 0) throw std::invalid_argument("Initial price must be greater than 0.");
//         if (volatility <= 0) throw std::invalid_argument("Volatility must be greater than 0.");
//         if (steps <= 0) throw std::invalid_argument("Number of steps must be greater than 0.");

//         std::vector<long double> prices(steps + 1);
//         prices[0] = initialPrice;

//         std::random_device rd;
//         std::mt19937 gen(rd()); 
//         std::normal_distribution<> d(0.0, 1.0);

//         std::vector<std::future<void>> futures;

//         for (int i = 1; i <= steps; ++i) {
//             futures.push_back(std::async(std::launch::async, [i, &prices, &d, &gen, drift, volatility]() {
//                 try {
//                     long double z = d(gen);
//                     long double exponent = (drift - 0.5 * volatility * volatility) + volatility * z;
//                     long double priceUpdate = prices[i-1] * std::exp(exponent);
                    
//                     if (!std::isfinite(priceUpdate)) throw std::runtime_error("Exp calculation overflow or underflow.");
//                     if (priceUpdate <= 0) throw std::runtime_error("Price update resulted in non-positive value.");

//                     // Additional logging
//                     std::cout << "Thread for step " << i << ": z = " << z << ", exponent = " << exponent 
//                               << ", priceUpdate = " << priceUpdate << ", previous price = " << prices[i-1] << std::endl;

//                     prices[i] = priceUpdate;
//                 } catch (const std::exception& e) {
//                     std::cerr << "Exception in thread for step " << i << ": " << e.what() << std::endl;
//                 }
//             }));
//         }

    //     for (auto& future : futures) {
    //         future.get(); // This will rethrow any exceptions caught by the futures
    //     }

    //     return prices;
    // }
std::vector<long double> StochasticModels::geometricBrownianMotion(long double initialPrice, long double volatility, long double drift, int steps) {
    if (initialPrice <= 0) throw std::invalid_argument("Initial price must be greater than 0.");
    if (volatility <= 0) throw std::invalid_argument("Volatility must be greater than 0.");
    if (steps <= 0) throw std::invalid_argument("Number of steps must be greater than 0.");

    std::vector<long double> prices(steps + 1);
    prices[0] = initialPrice;

    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::normal_distribution<> d(0.0, 1.0);

    for (int i = 1; i <= steps; ++i) {
        long double z = d(gen);
        long double exponent = (drift - 0.5 * volatility * volatility) * 1.0 + volatility * z;
        long double priceUpdate = prices[i-1] * std::exp(exponent);
        
        if (!std::isfinite(priceUpdate)) throw std::runtime_error("Exp calculation overflow or underflow.");
        if (priceUpdate <= 0) throw std::runtime_error("Price update resulted in non-positive value.");
        
        prices[i] = priceUpdate;
    }

    return prices;
}

// Обновляем функцию для использования типа long double
std::vector<long double> StochasticModels::runMonteCarloSimulation(
    long double initialPrice, long double volatility, long double drift, int steps,
    int numSimulations) {
  
  std::cout << "Monte Carlo simulation started with " << numSimulations << " simulations...\n";

  std::vector<long double> finalPrices(numSimulations);

  for (int i = 0; i < numSimulations; ++i) {
    // Generate one price path for the asset
    auto pricePath = StochasticModels::geometricBrownianMotion(
        initialPrice, volatility, drift, steps);
    
    // Store the final price from each simulation
    finalPrices[i] = pricePath.back();

    // Output the final price of each simulation
    std::cout << "Simulation " << i + 1 << " final price: " << finalPrices[i] << std::endl;
  }

  std::cout << "Monte Carlo simulation completed.\n";

  return finalPrices;
}

}  // namespace Simulation
