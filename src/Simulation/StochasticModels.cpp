#include "StochasticModels.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <future>
#include <chrono>
#include <mutex>
#include <thread>

namespace Simulation {
    std::mutex local_mutex;  // Local mutex

    // Function for profiling
    void profile(const std::function<void()>& func) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
    }

    void StochasticModels::initialize() {
        std::cout << "Stochastic models initialized." << std::endl;
    }

    std::vector<double> StochasticModels::geometricBrownianMotion(double initialPrice, double volatility, double drift, int steps) {
        std::vector<double> prices(steps + 1);
        prices[0] = initialPrice;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> d(0, 1);

        // Using a thread pool for asynchronous operations
        std::vector<std::future<void>> futures;
        for (int i = 1; i <= steps; ++i) {
            futures.push_back(std::async(std::launch::async, [&]() {
                double z = d(gen);
                std::lock_guard<std::mutex> lock(local_mutex);  // Local mutex for thread safety
                prices[i] = prices[i-1] * exp((drift - pow(volatility, 2) / 2) + volatility * z);
            }));
        }

        // Waiting for the completion of all asynchronous operations
        for (auto& future : futures) {
            future.get();
        }

        return prices;
    }
}