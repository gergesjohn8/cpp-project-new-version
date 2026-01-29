#include "Simpson2DSolver.h"


/*
Implementation of the Simpson2DSolver method for integration.
*/
double Simpson2DSolver::integrate(const Function2D& f,
                                  double a, double b,
                                  double c, double d) const {
    validate_intervals(a, b, c, d);
    
    const double hx = (b - a) / static_cast<double>(nx_);
    const double hy = (d - c) / static_cast<double>(ny_);
    
    double sum = 0.0;
    
    for (std::size_t i = 0; i <= nx_; ++i) {
        double x = a + i * hx;
        
        // Weight in x direction
        double wx;
        if (i == 0 || i == nx_) {
            wx = 1.0;
        } else if (i % 2 == 1) {
            wx = 4.0;
        } else {
            wx = 2.0;
        }
        
        for (std::size_t j = 0; j <= ny_; ++j) {
            double y = c + j * hy;
            
            // Weight in y direction
            double wy;
            if (j == 0 || j == ny_) {
                wy = 1.0;
            } else if (j % 2 == 1) {
                wy = 4.0;
            } else {
                wy = 2.0;
            }
            
            sum += wx * wy * f(x, y);
        }
    }
    
    return (hx * hy / 9.0) * sum;
}