#include <Python.h>
#include "lib/std.hpp"
#include "lib/xoshiro256.hpp"
#include <fmt/core.h>
#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;

Xoshiro256 rng;

auto calculate_pi() {
    vector<pair<int64_t, double>> result;

    const int64_t n_iterations = 1000000;
    int64_t n_in = 0;
    for(int64_t iter = 1; iter <= n_iterations; ++iter) {
        auto x = rng.next_double();
        auto y = rng.next_double();

        if(x*x + y*y < 1.0) { n_in++; }

        if(iter % 1000 == 0) {
            double approx_pi = 4.0 * (double)n_in / iter;
            result.emplace_back(iter, approx_pi);
            fmt::print("{:8}: {:f}\n", iter, approx_pi);
        }
    }

    return result;
}

void plot(const vector<pair<int64_t, double>>& result) {
    vector<int64_t> xs;
    vector<double> ys;
    for(auto [x, y] : result) {
        xs.emplace_back(x);
        ys.emplace_back(y);
    }

    plt::figure_size(1200, 780);
    plt::plot(xs, ys);
    plt::title("Approximation of PI");
    plt::save("./plot.png");
}

int main() {
    auto result = calculate_pi();
    plot(result);
}
