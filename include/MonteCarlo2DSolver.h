#pragma once
#include "Solver2D.h"
#include <cstddef>
#include <cstdint>

class MonteCarlo2DSolver : public Solver2D {
public:
    // constructor of MonteCarlo Solver in 2D, takes number of sampled points and random seed as input
    explicit MonteCarlo2DSolver(std::size_t n = 1000000, std::uint64_t seed = 0)
        : n_(n ? n : 1), seed_(seed) {}
    // integrate method to be overridden
    // takes reference to 2D Function object and two intervals over which to integrate
    double integrate(const Function2D& f,
                    double a, double b,
                    double c, double d) const override;

private:
    // private attributes, the number of samples and the seed
    std::size_t n_;
    std::uint64_t seed_;
};