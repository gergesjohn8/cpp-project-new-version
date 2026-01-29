#include "TrapezoidSolver.h"
#include <cmath>


/*
Implementation of the TrapzeoidSolver for 1d functions.

Composite Trapezoidal Rule
Approximates ∫ₐᵇ f(x)dx by summing trapezoid areas
Error: O(h²) where h = (b-a)/n

*/

double TrapezoidSolver::integrate(const Function& f, double a, double b) const {
    validate_interval(a, b);
    const std::size_t n = n_;
    const double h = (b - a) / static_cast<double>(n);

    // Trapezoidal formula: (h/2)[f(a) + 2·Σf(xᵢ) + f(b)]
    // Rewritten as: h·[f(a)/2 + Σf(xᵢ) + f(b)/2]
    
    double s = 0.5 * (f(a) + f(b));
    for (std::size_t i = 1; i < n; ++i) {
        double x = a + i * h;
        s += f(x);
    }
    return s * h;
}
