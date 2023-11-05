#include "OutputSaver.hpp"
#include <vector>
#include <string>

int main() {
    std::vector<double> data = {1.0, 2.0, 3.0};  // Example data
    std::vector<std::vector<std::string>> csvData;

    // Convert the vector of doubles to a vector of vector of strings
    for (const auto& value : data) {
        csvData.push_back({std::to_string(value)});
    }

    // Assuming that "data" is the directory where you want to save the CSV
    IO::OutputSaver outputSaver("data");
    outputSaver.saveData(csvData, "output.csv");  // Use the saveCSV method
}
