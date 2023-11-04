#include <gtest/gtest.h>
#include "Simulation/Correlation.hpp"  // Замените на правильный путь к вашему заголовочному файлу

class CorrelationTest : public ::testing::Test {
protected:
    // Здесь можно инициализировать ресурсы, которые будут использоваться в тестах
};

TEST_F(CorrelationTest, TestBasicCorrelation) {
    std::vector<double> x = {1.0, 2.0, 3.0};
    std::vector<double> y = {2.0, 4.0, 6.0};
    double result = Simulation::Correlation::calculateCorrelation(x, y);
    ASSERT_NEAR(result, 1.0, 0.0001); // Проверяем, что корреляция близка к 1
}