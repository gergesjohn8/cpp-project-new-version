#pragma once
#include "Function2D.h"
#include <stdexcept>

// Abstract base class for 2D numerical integrators
// This is the 2D equivalent of your Solver.h

class Solver2D {
public:
    // Integrate f on [a,b] x [c,d] and return approximate integral
    // a, b = bounds for x
    // c, d = bounds for y
    virtual double integrate(const Function2D& f, 
                            double a, double b,
                            double c, double d) const = 0;
    virtual ~Solver2D() = default;

protected:
    // Helper: validate intervals
    static void validate_intervals(double a, double b, double c, double d) {
        if (!(a < b)) throw std::invalid_argument("Invalid x interval: require a < b");
        if (!(c < d)) throw std::invalid_argument("Invalid y interval: require c < d");
    }
};