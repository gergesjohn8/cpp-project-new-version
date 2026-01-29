#include "MonteCarloSolver.h"
#include <random>
#include <stdexcept>
#include <limits>


/*
Implementation of the Monte Carlo solver for 1d functions.
*/

/*
// 2D Monte Carlo Integration
// Sample (Xᵢ,Yᵢ) ~ Uniform([a,b]×[c,d]), then:
// Area · (1/n)·Σf(Xᵢ,Yᵢ) → ∫∫f(x,y)dydx
// Key advantage: error O(n^(-1/2)) regardless of dimension
*/
MonteCarloSolver::MonteCarloSolver(std::size_t n, std::uint64_t seed)
    : n_(n ? n : 1), seed_(seed) {}

// integrate method
double MonteCarloSolver::integrate(const Function& f, double a, double b) const {
    validate_interval(a, b);

    // choose seed: if user provided seed_ != 0, use it; otherwise use random_device
    const std::uint64_t actual_seed = (seed_ != 0) ? seed_ : std::random_device{}();
    std::mt19937_64 rng(actual_seed);
    std::uniform_real_distribution<double> dist(a, b);

    // sample points from the interval and evaluate the function, finally compute the average
    // accumulate in double; for very large n you might want a compensated sum.
    double sum = 0.0;
    for (std::size_t i = 0; i < n_; ++i) {
        const double x = dist(rng);
        sum += f(x);
    }

    const double factor = (b - a) / static_cast<double>(n_);
    return factor * sum;
}
