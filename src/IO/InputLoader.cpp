#include "InputLoader.hpp"
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>
#include <cassert>

namespace IO {
    void InputLoader::log(const std::string& message) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::cout << "[" << std::ctime(&time) << "]: " << message << std::endl;
    }

    void InputLoader::loadParameters() {
        log("Loading general parameters from config file...");
        // Add assertions for testing
        assert(std::filesystem::exists("config.txt") == true);
        std::ifstream configFile("config.txt");
        loadConfigFromFile(configFile);
    }

    // Implement the loadConfigFromFile function
    // TODO: Implement config file reading logic
    void InputLoader::loadConfigFromFile(std::ifstream& /* configFile */) {
        // TODO: Implement config file reading logic
    }
}