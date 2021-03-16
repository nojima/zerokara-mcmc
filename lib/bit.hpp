#pragma once
#include "std.hpp"

// n以上の最小の2の冪を返す。
constexpr int bit_ceil(int n) noexcept {
    int ret = 1;
    while (ret < n) { ret *= 2; }
    return ret;
}

constexpr inline uint64_t rotl(const uint64_t x, int k) noexcept {
    return (x << k) | (x >> (64 - k));
}
