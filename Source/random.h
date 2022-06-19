#pragma once
#include <ctime>
#include <random>

class Random {
public:
    Random() : engine((size_t)time(nullptr)) {}
    explicit Random(size_t seed) : engine(seed) {}

    template <typename T>
    T genNumber(T low, T high) {
        std::uniform_real_distribution<T> dist(low, high);
        return dist(engine);
    }

private:
    std::mt19937 engine;
};
