#include "OutputSaver.hpp"
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>  // for std::vector
int main() {
    std::vector<double> data = {1.0, 2.0, 3.0}; // Пример данных
    IO::OutputSaver::saveResults(data);
}
