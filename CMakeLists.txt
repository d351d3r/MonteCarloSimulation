# Original CMake content
cmake_minimum_required(VERSION 3.10)
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
project(MonteCarloSimulation)

find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

#add_compile_options(-Wall -Wextra -Werror -Wconversion)
add_compile_definitions(_LIBCPP_ENABLE_THREAD_SAFETY_ANNOTATIONS)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g3)
endif()
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O2")

# Include directories
include_directories(.)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/includes)
include_directories(${CMAKE_SOURCE_DIR}/include/IO)
include_directories(${CMAKE_SOURCE_DIR}/include/Simulation)
include_directories(${CMAKE_SOURCE_DIR}/include/Analysis)

# Source files
set(SOURCE_FILES
    src/main.cpp
    src/IO/InputLoader.cpp
    src/IO/OutputSaver.cpp
    src/Simulation/StochasticModels.cpp
    src/Simulation/Correlation.cpp
    src/Simulation/Parallelization.cpp
    src/Analysis/Statistics.cpp
    src/Analysis/Visualization.cpp
)

# Test files
set(TEST_FILES
    tests/test_main.cpp
    #tests/test_correlation.cpp
    tests/test_parallelization.cpp
)

# Add executable
add_executable(MonteCarloSimulation ${SOURCE_FILES})
target_include_directories(MonteCarloSimulation PRIVATE include)

# Link Conan and other libraries
target_link_libraries(MonteCarloSimulation ${CONAN_LIBS} GTest::GTest spdlog::spdlog)


# Тесты (подключаем библиотеку Google Test)
enable_testing()
add_executable(MonteCarloSimulationTests ${TEST_FILES})
target_include_directories(MonteCarloSimulationTests PRIVATE include)
# Link Google Test and project libraries to test executable
target_link_libraries(MonteCarloSimulationTests ${CONAN_LIBS} GTest::GTest GTest::Main)
add_test(NAME MonteCarloSimulationTests COMMAND MonteCarloSimulationTests)