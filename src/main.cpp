#include "OutputSaver.hpp"
#include "StochasticModels.hpp"
#include "Statistics.hpp"
#include "Visualization.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    try {
        std::string outputDir = "data"; // Default output directory
        std::string resultsFilename = "simulation_results.csv"; // Default results filename
        std::string testDataFilename = "test_data.csv"; // Default filename for test data
        std::string statsFilename = "statistics.csv"; // Default statistics filename
        bool generateData = false;

        // Default Simulation parameters
        size_t numPaths = 10000;
        long double initialPrice = 100.0;
        long double volatility = 0.2;
        long double drift = 0.05;
        int steps = 252;

        // Parse command line arguments
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--generate-data") {
                generateData = true;
            } else if (arg == "--outputDir" && i + 1 < argc) {
                outputDir = argv[++i];
            } else if (arg == "--numPaths" && i + 1 < argc) {
                numPaths = std::stoull(argv[++i]);
            } else if (arg == "--initialPrice" && i + 1 < argc) {
                initialPrice = std::stold(argv[++i]);
            } else if (arg == "--volatility" && i + 1 < argc) {
                volatility = std::stold(argv[++i]);
            } else if (arg == "--drift" && i + 1 < argc) {
                drift = std::stold(argv[++i]);
            } else if (arg == "--steps" && i + 1 < argc) {
                steps = std::stoi(argv[++i]);
            } else if (arg == "--resultsFile" && i + 1 < argc) {
                resultsFilename = argv[++i];
            } else if (arg == "--statsFile" && i + 1 < argc) {
                statsFilename = argv[++i];
            }
        }

        // Ensure the output directory exists
        if (!fs::exists(outputDir)) {
            fs::create_directories(outputDir);
        }

        // Create instances of OutputSaver for saving results and test data
        IO::OutputSaver outputSaver(outputDir);

        // Generate test data if the flag is present
        if (generateData) {
            std::cout << "Generating test data...\n";
            outputSaver.generateTestData(testDataFilename, numPaths, initialPrice, volatility, drift, steps);
            std::cout << "Test data generated and saved to " << testDataFilename << std::endl;
        }

        // Run the Monte Carlo simulation
        std::cout << "Running Monte Carlo simulation...\n";
        std::vector<long double> simulationResults = Simulation::StochasticModels::runMonteCarloSimulation(
            initialPrice, volatility, drift, steps, numPaths);

        // Convert simulation results to string for saving
        std::vector<std::vector<std::string>> simulationResultsAsString = outputSaver.convertToCSVFormat(simulationResults);

        // Save the simulation results
        outputSaver.saveData(simulationResultsAsString, resultsFilename);
        std::cout << "Simulation results saved to " << resultsFilename << std::endl;

        // Calculate statistics from the simulation results
        // auto stats = Statistics::calculateStatistics(simulationResults);
        // outputSaver.saveData(stats, statsFilename);

        // Visualize the results
        // Visualization::generateCharts(simulationResults, outputDir + "/visualization.png");

        std::cout << "Monte Carlo simulation completed successfully.\n";
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
