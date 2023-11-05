#ifndef IDATAHANDLER_HPP
#define IDATAHANDLER_HPP

#include <vector>
#include <string>

class IDataHandler {
public:
    virtual ~IDataHandler() = default;

    // Load data from a file and return it in a suitable format.
    virtual std::vector<std::vector<std::string>> loadData(const std::string& filename) = 0;

    // Save data to a file.
    virtual void saveData(const std::vector<std::vector<std::string>>& data, const std::string& filename) = 0;
};

#endif // IDATAHANDLER_HPP

