#include "OutputSaver.hpp"
#include "StochasticModels.hpp"
#include <sstream>
#include <filesystem>
#include <stdexcept>

namespace IO {

OutputSaver::OutputSaver(const std::string& baseDirectory) : baseDir(baseDirectory) {}

OutputSaver::~OutputSaver() {
    // Destructor implementation if needed
}

std::vector<std::vector<std::string>> OutputSaver::loadData(const std::string& filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(baseDir + "/" + filename);
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::cout << "Attempting to open file for loading: " << baseDir + "/" + filename << std::endl;
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<std::string> rowData;

        while (std::getline(lineStream, cell, ',')) {
            rowData.push_back(cell);
        }

        data.push_back(rowData);
    }
    std::cout << "File loaded successfully. Number of rows read: " << data.size() << std::endl;
    file.close();
    return data;
}

void OutputSaver::saveData(const std::vector<std::vector<std::string>>& data, const std::string& filename) {
    std::lock_guard<std::mutex> lock(csvMutex);
    std::ofstream file(baseDir + "/" + filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::cout << "Attempting to open file for saving: " << baseDir + "/" + filename << std::endl;
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << ",";
            }
        }
        file << '\n';
    }
    file.close();
    std::cout << "Data saved successfully to file: " << baseDir + "/" + filename << std::endl;

}
std::vector<std::vector<std::string>> OutputSaver::convertToCSVFormat(const std::vector<long double>& data) {
    std::vector<std::vector<std::string>> formattedData;
    formattedData.reserve(data.size());

    for (auto& value : data) {
        formattedData.push_back({std::to_string(value)});
    }

    return formattedData;
}
std::ofstream OutputSaver::openFileForWriting(const std::string& filename) const {
    // Check and create directory if it does not exist
    if (!std::filesystem::exists(baseDir)) {
        std::filesystem::create_directories(baseDir);
    }
    std::filesystem::path filePath = std::filesystem::path(baseDir) / filename;

    std::ofstream outFile(filePath, std::ios::out); // Removed std::ios::binary for text file
    if (!outFile.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filePath.string());
    }
    return outFile;
}
void OutputSaver::generateTestData(const std::string& filename, size_t numberOfPaths, long double initialPrice, long double volatility, long double drift, int steps) {
    std::cout << "Starting test data generation: " << filename << " with " << numberOfPaths << " paths." << std::endl;

    std::lock_guard<std::mutex> lock(csvMutex);
    std::ofstream file = openFileForWriting(filename);

    // Write headers
    file << "Path,Step,Price\n";

    for (size_t pathNum = 0; pathNum < numberOfPaths; ++pathNum) {
        auto prices = Simulation::StochasticModels::geometricBrownianMotion(initialPrice, volatility, drift, steps);
        for (int i = 0; i <= steps; ++i) {
            file << pathNum << "," << i << "," << prices[i] << "\n";
        }
    }

    file.close();
    std::cout << "Test data generated and saved to file: " << filename << std::endl;
}

} // namespace IO
