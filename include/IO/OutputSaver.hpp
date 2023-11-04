#ifndef OUTPUT_SAVER_HPP
#define OUTPUT_SAVER_HPP

#include <vector>
#include <string>
#include <mutex>

namespace IO {
    extern std::mutex csv_mutex;  // Mutex for thread-safe file operations

    class OutputSaver {
    public:
        static void saveResults(const std::vector<double>& data);
        static void saveToCSV(const std::vector<double>& data, const std::string& filename);
        static void saveToDatabase(const std::vector<double>& data);
    };
}

#endif // OUTPUT_SAVER_HPP
