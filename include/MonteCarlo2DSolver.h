#pragma once
#include "Solver2D.h"
#include <cstddef>
#include <cstdint>

class MonteCarlo2DSolver : public Solver2D {
public:
    explicit MonteCarlo2DSolver(std::size_t n = 1000000, std::uint64_t seed = 0)
        : n_(n ? n : 1), seed_(seed) {}
    
    double integrate(const Function2D& f,
                    double a, double b,
                    double c, double d) const override;

private:
    std::size_t n_;
    std::uint64_t seed_;
};