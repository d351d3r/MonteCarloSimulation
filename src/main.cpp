#include "OutputSaver.hpp"
#include "StochasticModels.hpp"
#include "Statistics.hpp"
#include "Visualization.hpp"

#include <vector>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        // Check if there are enough arguments
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " <directory> <filename> [--generate-data]" << std::endl;
            return EXIT_FAILURE;
        }

        // Parse arguments
        std::string directory = argv[1];
        std::string filename = argv[2];
        bool generateData = (argc > 3 && std::string(argv[3]) == "--generate-data");

        // Simulation parameters
        size_t numPaths = 10000;  // Adjust as necessary
        long double initialPrice = 100.0; // Initial asset price
        long double volatility = 0.2;     // Volatility
        long double drift = 0.05;         // Drift (average return)
        int steps = 252;             // Number of steps (e.g., trading days in a year)

        // Create an instance of OutputSaver with the directory from arguments
        IO::OutputSaver outputSaver(directory);

        // Generate test data if the flag is present
        if (generateData) {
            outputSaver.generateTestData(filename, numPaths, initialPrice, volatility, drift, steps);
        }

        // Run Monte Carlo simulation
        std::cout << "Running Monte Carlo simulation...\n";
        auto simulationResults = Simulation::StochasticModels::runMonteCarloSimulation(
            initialPrice, volatility, drift, steps, numPaths);

        // Calculate statistics from the simulation results
        std::cout << "Calculating statistics...\n";
       // auto stats = Statistics::calculateStatistics(simulationResults);

        // Visualize the results (this is a placeholder for your actual visualization logic)
        std::cout << "Generating visualizations...\n";
      //  Visualization::generateCharts(simulationResults, "simulation_results.png");

        // Save simulation results to a file
        std::cout << "Saving simulation results...\n";
        std::vector<std::vector<std::string>> simulationResultsAsString;
        for (const auto& value : simulationResults) {
            std::vector<std::string> row;
            row.push_back(std::to_string(value));
            simulationResultsAsString.push_back(row);
        }
        outputSaver.saveData(simulationResultsAsString, "simulation_results.csv");

      //  outputSaver.saveData(simulationResults,"simulation_results.csv");

        // Save statistics to a file
        std::cout << "Saving statistics...\n";
       // outputSaver.saveData("statistics.csv", stats);

        std::cout << "Monte Carlo simulation completed successfully.\n";
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
