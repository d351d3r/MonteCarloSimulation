#include "IDataHandler.hpp"
#include <map>
#include <string>
#include <vector>

namespace IO {

class InputLoader : public IDataHandler {
public:
    explicit InputLoader(const std::string& configPath);
    
    // Реализация чисто виртуальных функций из IDataHandler
    std::vector<std::vector<std::string>> loadData(const std::string& filename) override;
    void saveData(const std::vector<std::vector<std::string>>& data, const std::string& filename) override;

    // Дополнительные функции, специфичные для InputLoader
    std::map<std::string, std::string> loadParameters();

private:
    std::string configFilePath;
    void log(const std::string& message) const;
};

} // namespace IO
