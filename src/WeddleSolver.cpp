#include "WeddleSolver.h"



double WeddleSolver::integrate(const Function& f, double a, double b) const {
    validate_interval(a, b);
    const double h = (b - a) / static_cast<double>(n_);
    double sum = f(a) + f(b);
    for (std::size_t i = 0; i < n_; ++i) {
        double x_midpoint = a + (static_cast<double>(i) + 0.5) * h;
        sum += 2.0 * f(x_midpoint);
    }
    return sum * (h / 2.0);
}
