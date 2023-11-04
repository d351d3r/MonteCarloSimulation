#ifndef STOCHASTIC_MODELS_HPP
#define STOCHASTIC_MODELS_HPP

#include <vector>
#include <functional>

namespace Analysis {

    class Statistics {
    public:
        static void analyze(const std::vector<double>& data);
        static double calculateMean(const std::vector<double>& data);
        static double calculateVariance(const std::vector<double>& data);

        // Дополнительные методы, если необходимы
    };

}

#endif // STOCHASTIC_MODELS_HPP