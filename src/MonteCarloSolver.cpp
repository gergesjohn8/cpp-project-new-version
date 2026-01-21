#include "MonteCarloSolver.h"
#include <random>
#include <stdexcept>
#include <limits>

MonteCarloSolver::MonteCarloSolver(std::size_t n, std::uint64_t seed)
    : n_(n ? n : 1), seed_(seed) {}

double MonteCarloSolver::integrate(const Function& f, double a, double b) const {
    validate_interval(a, b);

    // choose seed: if user provided seed_ != 0, use it; otherwise use random_device
    const std::uint64_t actual_seed = (seed_ != 0) ? seed_ : std::random_device{}();
    std::mt19937_64 rng(actual_seed);
    std::uniform_real_distribution<double> dist(a, b);

    // accumulate in double; for very large n you might want a compensated sum.
    double sum = 0.0;
    for (std::size_t i = 0; i < n_; ++i) {
        const double x = dist(rng);
        sum += f(x);
    }

    const double factor = (b - a) / static_cast<double>(n_);
    return factor * sum;
}
