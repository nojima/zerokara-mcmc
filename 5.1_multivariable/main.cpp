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

template <class Action, class StepWidth>
vector<pair<double, double>> metropolis(
    int n_iters,
    Action action,       // fn(double x, double y) -> double
    StepWidth step_width // fn(int iter) -> double
) {
    vector<pair<double, double>> result;

    double x = 0;
    double y = 0;
    int n_accept = 0;

    for(int iter = 1; iter <= n_iters; ++iter) {
        // step1: ⊿x, ⊿y をランダムに選ぶ
        double dx = noise() * step_width(iter);
        double dy = noise() * step_width(iter);
        double x_candidate = x + dx;
        double y_candidate = y + dy;

        // step2: メトロポリステスト
        double prob_accept = min(1.0, exp(action(x, y) - action(x_candidate, y_candidate)));
        if(rng.next_double() < prob_accept) {
            // 受理
            x = x_candidate;
            y = y_candidate;
            ++n_accept;
        } else {
            // 棄却
        }

        if(iter % 100 == 0) {
            result.push_back({x, y});
        }

        if(iter % 1000 == 0) {
            double r_accept = (double)n_accept / iter;
            fmt::print("{:8}: ({:f}, {:f}) {:f}\n", iter, x, y, r_accept);
        }
    }

    return result;
}

void plot(const vector<pair<double, double>>& result) {
    vector<double> xs, ys;
    for (auto [x, y] : result) {
        xs.emplace_back(x);
        ys.emplace_back(y);
    }
    plt::scatter(xs, ys, 1.0);
    plt::save("./plot.png");
}

inline double sq(double x) noexcept {
    return x * x;
}

int main() {
    auto action = [](double x, double y) {
        return 0.5 * (sq(x) + sq(y) + x*y);
    };
    auto step_width = [](int) {
        return 0.5;
    };
    /*
    auto action = [](double x) {
        return -log( exp(-sq(x) * 0.5) + exp(-sq(x - 100) * 0.5) );
    };
    auto step_width = [](int iter) {
        if(iter % 2 == 0) {
            return 1.0;
        } else {
            return 100.0;
        }
    };
    */

    auto result = metropolis(
        1'000'000, // n_iters
        action,
        step_width
    );
    plot(result);
}
