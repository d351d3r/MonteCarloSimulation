#ifndef INPUT_LOADER_HPP
#define INPUT_LOADER_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>  // For logging time
#include <cassert> // For testing

namespace IO {
    class InputLoader {
    public:
        static void loadParameters();
        static void log(const std::string& message);
    private:
        static void loadConfigFromFile(std::ifstream& configFile);
    };
}

#endif // INPUT_LOADER_HPP