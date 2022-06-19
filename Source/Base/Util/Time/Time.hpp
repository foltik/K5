#pragma once

#include <iostream>
#include <chrono>

namespace k5 {
    namespace Time {
        using namespace std::chrono;

        using seconds = duration<double, std::ratio<1, 1>>;
        using milliseconds = duration<double, std::milli>;
        using microseconds = duration<double, std::micro>;
        using nanoseconds = duration<double, std::nano>;

        template<typename Duration>
        std::ostream& operator<<(std::ostream& stream, const Duration& duration) {
            stream << duration.count();
            return stream;
        }

        template<typename Duration = std::chrono::nanoseconds>
        auto currentTime() {
            return std::chrono::time_point_cast<Duration>(steady_clock::now());
        }

        template<typename ToDuration, typename Duration>
        auto cast(const Duration& duration) {
            return std::chrono::duration_cast<ToDuration>(duration);
        }
    }
}