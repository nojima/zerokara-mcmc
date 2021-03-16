#include "lib/std.hpp"
#include "lib/xoshiro256.hpp"
#include <fmt/core.h>

int main() {
    Xoshiro256 rng;

    const size_t n_iterations = 100000;
    size_t n_in = 0;
    for(size_t iter = 1; iter <= n_iterations; ++iter) {
        auto x = rng.next_double();
        auto y = rng.next_double();

        if(x*x + y*y < 1.0) { n_in++; }

        if(iter % 1000 == 0) {
            double approx_pi = 4.0 * (double)n_in / iter;
            fmt::print("{:8}: {:f}\n", iter, approx_pi);
        }
    }
}
