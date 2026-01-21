#include "TrapezoidSolver.h"
#include <cmath>

double TrapezoidSolver::integrate(const Function& f, double a, double b) const {
    validate_interval(a, b);
    const std::size_t n = n_;
    const double h = (b - a) / static_cast<double>(n);
    double s = 0.5 * (f(a) + f(b));
    for (std::size_t i = 1; i < n; ++i) {
        double x = a + i * h;
        s += f(x);
    }
    return s * h;
}
