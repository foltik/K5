#pragma once

#include <iostream>
#include <chrono>

namespace k5 {
    namespace Time {
        using seconds = std::chrono::seconds;
        using milliseconds = std::chrono::milliseconds;
        using microseconds = std::chrono::microseconds;
        using nanoseconds = std::chrono::nanoseconds;

        using namespace std::chrono;

        template<typename Duration>
        std::ostream& operator<<(std::ostream& stream, const Duration& duration) {
            stream << duration.count();
            return stream;
        };

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