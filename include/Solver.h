#pragma once
#include "Function.h"
#include <stdexcept>

// Abstract base class for numerical integrators
class Solver {
public:
    // Integrate f on [a,b] and return approximate integral.
    // Concrete classes implement this.
    virtual double integrate(const Function& f, double a, double b) const = 0;
    virtual ~Solver() = default;

protected:
    // Optional helper: validate interval
    static void validate_interval(double a, double b) {
        if (!(a < b)) throw std::invalid_argument("Invalid interval: require a < b");
    }
};
