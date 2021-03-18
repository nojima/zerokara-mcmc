#include <Python.h>
#include "lib/std.hpp"
#include "lib/xoshiro256.hpp"
#include <fmt/core.h>
#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;

Xoshiro256 rng;

// [-1, 1] の一様乱数を返す
inline double noise() noexcept {
    return rng.next_double() * 2.0 - 1.0;
}

template <class Action>
vector<double> metropolis(
    int n_iters,
    double step_size,
    Action action
) {
    vector<double> result;

    double x = 0;
    int n_accept = 0;

    for(int iter = 1; iter <= n_iters; ++iter) {
        // step1: ⊿x をランダムに選ぶ
        double dx = noise() * step_size;
        double x_candidate = x + dx;

        // step2: メトロポリステスト
        double prob_accept = min(1.0, exp(action(x) - action(x_candidate)));
        if(rng.next_double() < prob_accept) {
            // 受理
            x = x_candidate;
            ++n_accept;
        } else {
            // 棄却
        }

        if(iter % 1000 == 0) {
            double r_accept = (double)n_accept / iter;
            fmt::print("{:8}: {:f} {:f}\n", iter, x, r_accept);
        }

        result.emplace_back(x);
    }

    return result;
}

void plot(const vector<double>& result) {
    plt::hist(result, 100);
    plt::save("./plot.png");
}

inline double sq(double x) noexcept {
    return x * x;
}

int main() {
    auto action = [](double x) {
        return -log( exp(-sq(x - 3) * 0.5) + exp(-sq(x + 3) * 0.5) );
    };
    /*
    auto action = [](double x) {
        return -log( exp(-sq(x) * 0.5) + exp(-sq(x - 100) * 0.5) );
    };
    */

    auto result = metropolis(
        1'000'000,     // n_iters
        2.0,           // step_size
        action
    );
    plot(result);
}
