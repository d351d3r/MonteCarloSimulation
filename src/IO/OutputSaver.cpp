#include "OutputSaver.hpp"
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

    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<std::string> rowData;

        while (std::getline(lineStream, cell, ',')) {
            rowData.push_back(cell);
        }

        data.push_back(rowData);
    }

    file.close();
    return data;
}

void OutputSaver::saveData(const std::vector<std::vector<std::string>>& data, const std::string& filename) {
    std::lock_guard<std::mutex> lock(csvMutex);
    std::ofstream file(baseDir + "/" + filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

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
}
std::ofstream OutputSaver::openFileForWriting(const std::string& filename) const {
    // Проверка и создание директории, если она не существует
    if (!std::filesystem::exists(baseDir)) {
        std::filesystem::create_directories(baseDir);
    }
    std::filesystem::path basePath = baseDir; // Преобразовать std::string в std::filesystem::path
    std::filesystem::path filePath = basePath / filename;
    
    std::ofstream outFile(filePath, std::ios::out | std::ios::binary);
    if (!outFile.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filePath.string());
    }
    return outFile;
}
} // namespace IO
