#include "SimpsonSolver.h"
#include <cmath>

/*
Implementation of the SimpsonSolver integrate method.
*/

double SimpsonSolver::integrate(const Function& f, double a, double b) const {
    validate_interval(a, b);
    const std::size_t n = n_;
    const double h = (b - a) / static_cast<double>(n);
    double s = f(a) + f(b);

    // odd indices
    for (std::size_t i = 1; i < n; i += 2) {
        double x = a + i * h;
        s += 4.0 * f(x);
    }
    // even indices
    for (std::size_t i = 2; i < n; i += 2) {
        double x = a + i * h;
        s += 2.0 * f(x);
    }
    return s * (h / 3.0);
}
