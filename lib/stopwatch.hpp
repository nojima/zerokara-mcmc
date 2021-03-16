#pragma once
#include "std.hpp"
#include <chrono>

class Stopwatch {
    chrono::steady_clock::time_point t0;

public:
    Stopwatch(): t0(chrono::steady_clock::now()) {}

    int64_t elapsed_millis() const {
        auto now = chrono::steady_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(now - t0).count();
    }
};
