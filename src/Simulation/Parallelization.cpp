#include "Parallelization.hpp"
#include <iostream>
#include <thread>  // for std::thread

namespace Simulation {

    void Parallelization::runSimulation() {
        // Implement single-threaded simulation logic here
        std::cout << "Single-threaded simulation running..." << std::endl;
    }

    void Parallelization::runMultiThreadedSimulation() {
        // Implement multi-threaded simulation logic here
        std::cout << "Multi-threaded simulation running..." << std::endl;

        // Example: Running two threads
        std::thread t1([] { std::cout << "Thread 1 running\n"; });
        std::thread t2([] { std::cout << "Thread 2 running\n"; });
        t1.join();
        t2.join();
    }

    void Parallelization::runParallelTasks() {
        // Implement parallel tasks logic
        std::cout << "Parallel tasks running..." << std::endl;
    }
}
