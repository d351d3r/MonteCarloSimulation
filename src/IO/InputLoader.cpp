#include "InputLoader.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <cassert>
#include <filesystem>
#include <vector>
#include <sstream>
#include <stdexcept>

namespace IO {

InputLoader::InputLoader(const std::string& configPath) : configFilePath(configPath) {
    assert(std::filesystem::exists(configFilePath));
}

std::vector<std::vector<std::string>> InputLoader::loadData(const std::string& filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(configFilePath + "/" + filename);  // Путь к файлу теперь включает configFilePath
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

void InputLoader::saveData(const std::vector<std::vector<std::string>>& data, const std::string& filename) {
    // Поскольку InputLoader не предполагает сохранение данных,
    // метод может быть оставлен пустым или бросать исключение.
    throw std::runtime_error("InputLoader does not support saving data.");
}

std::map<std::string, std::string> InputLoader::loadParameters() {
    log("Loading parameters from config file...");
    std::map<std::string, std::string> parameters;
    std::ifstream configFile(configFilePath); // Теперь предполагается, что configFilePath - это путь к файлу конфигурации
    std::string line;

    while (std::getline(configFile, line)) {
        auto delimiterPos = line.find("=");
        if (delimiterPos == std::string::npos) {
            throw std::runtime_error("Invalid config line: " + line);
        }
        auto name = line.substr(0, delimiterPos);
        auto value = line.substr(delimiterPos + 1);
        parameters[name] = value;
    }

    configFile.close();
    return parameters;
}

void InputLoader::log(const std::string& message) const {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::string timeStr = std::ctime(&time);
    timeStr.pop_back(); // Удаление символа новой строки
    std::cout << "[" << timeStr << "]: " << message << std::endl;
}

} // namespace IO
