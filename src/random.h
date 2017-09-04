#pragma once
#include <ctime>
#include <random>

class random {
public:
    explicit random(auto seed = time(nullptr)) : engine(seed) {}

    template <typename T>
    T genNumber(T low, T high) {
        std::uniform_real_distribution<T> dist(low, high);
        return dist(engine);
    }


private:
    std::mt19937 engine;
};
