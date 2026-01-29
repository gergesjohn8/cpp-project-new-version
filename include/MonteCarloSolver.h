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
    // explicit: the user has to deliberately create a MonteCarloSolver object, implicit creations are not possible
    explicit MonteCarloSolver(std::size_t n = 10000, std::uint64_t seed = 0);

    // integrate f on [a,b] using simple Monte Carlo estimator
    // integration method from Solver class that will be overridden
    double integrate(const Function& f, double a, double b) const override;

private:
    // private attributes
    // n_ being number of samples
    // seed_ being seed for randomization
    std::size_t n_;
    std::uint64_t seed_;
};
