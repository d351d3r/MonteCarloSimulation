#ifndef OUTPUTSAVER_HPP
#define OUTPUTSAVER_HPP

#include "IDataHandler.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <mutex>

namespace IO {

class OutputSaver : public IDataHandler {
public:
    explicit OutputSaver(const std::string& baseDirectory);
    ~OutputSaver() override;

    std::vector<std::vector<std::string>> loadData(const std::string& filename) override;
    void saveData(const std::vector<std::vector<std::string>>& data, const std::string& filename) override;

private:
    std::string baseDir;
    mutable std::mutex csvMutex;

    // Declare the helper method to open a file for writing
    std::ofstream openFileForWriting(const std::string& filename) const;
};

} // namespace IO

#endif // OUTPUTSAVER_HPP
