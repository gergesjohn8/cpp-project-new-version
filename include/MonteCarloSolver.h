#pragma once
#include "Solver.h"
#include <cstddef>
#include <cstdint>

// Monte Carlo integrator using uniform samples on [a,b].
// If seed == 0 (default) the RNG is seeded from std::random_device for non-deterministic runs.
// If seed != 0 the RNG is seeded with that value (deterministic).
class MonteCarloSolver : public Solver {
public:
    // n = number of samples (falls back to 1 if 0)
    // seed = 0 means "random seed" (non-deterministic)
    explicit MonteCarloSolver(std::size_t n = 10000, std::uint64_t seed = 0);

    // integrate f on [a,b] using simple Monte Carlo estimator
    double integrate(const Function& f, double a, double b) const override;

private:
    std::size_t n_;
    std::uint64_t seed_;
};
