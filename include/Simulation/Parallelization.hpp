#ifndef PARALLELIZATION_HPP
#define PARALLELIZATION_HPP

#include <vector>

namespace Simulation {

    class Parallelization {
    public:
        static void runSimulation();  // Однопоточная симуляция
        static void runMultiThreadedSimulation();  // Многопоточная симуляция
        static void runParallelTasks(); // Дополнительный метод

        // Дополнительные методы, если необходимы
    };

}

#endif // PARALLELIZATION_HPP
