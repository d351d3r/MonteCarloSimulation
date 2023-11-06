#ifndef VISUALIZATION_HPP
#define VISUALIZATION_HPP

#include <vector>

namespace Analysis {
    class Visualization {
    public:
        static void visualize(const std::vector<long double>& data);
        static void plotData(const std::vector<long double>& data);    };
}

#endif // VISUALIZATION_HPP