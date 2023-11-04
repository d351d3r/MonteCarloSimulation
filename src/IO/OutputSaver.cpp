#include "OutputSaver.hpp"
#include <iostream>
#include <fstream>
#include <thread>  
#include <mutex>   

namespace IO {
    std::mutex csv_mutex;  // Mutex for thread-safe file operations

    void OutputSaver::saveResults(const std::vector<double>& data) {
        std::cout << "Saving results..." << std::endl;
        saveToCSV(data, "results.csv");
    }

    void OutputSaver::saveToCSV(const std::vector<double>& data, const std::string& filename) {
        std::lock_guard<std::mutex> lock(csv_mutex);
        std::ofstream outFile(filename, std::ios::out | std::ios::binary);  
        for (const auto& value : data) {
            outFile << value << "\\n";
        }
        outFile.close();
    }

    void OutputSaver::saveToDatabase(const std::vector<double>& data) {
        std::cout << "Saving data to database..." << std::endl;
        // Implement logic to save the data to a database
    }
}
