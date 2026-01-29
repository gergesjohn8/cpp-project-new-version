#include "MonteCarlo2DSolver.h"
#include <random>

/*
Implementation of the Monte Carlo solver for 2D functions.
*/
double MonteCarlo2DSolver::integrate(const Function2D& f,
                                     double a, double b,
                                     double c, double d) const {

    // check if the interval is correct
    validate_intervals(a, b, c, d);
    
    
    const std::uint64_t actual_seed = (seed_ != 0) ? seed_ : std::random_device{}();
    std::mt19937_64 rng(actual_seed);
    std::uniform_real_distribution<double> dist_x(a, b);
    std::uniform_real_distribution<double> dist_y(c, d);
    
    double sum = 0.0;
    // sample points from the 2d interval
    // evaluate the function at these points and calculate the average
    for (std::size_t i = 0; i < n_; ++i) {
        double x = dist_x(rng);
        double y = dist_y(rng);
        sum += f(x, y);
    }
    
    double area = (b - a) * (d - c);
    return area * sum / static_cast<double>(n_);
}