#include "Trapezoid2DSolver.h"

double Trapezoid2DSolver::integrate(const Function2D& f,
                                    double a, double b,
                                    double c, double d) const {
    validate_intervals(a, b, c, d);
    
    const double hx = (b - a) / static_cast<double>(nx_);
    const double hy = (d - c) / static_cast<double>(ny_);
    
    double sum = 0.0;
    
    for (std::size_t i = 0; i <= nx_; ++i) {
        double x = a + i * hx;
        
        for (std::size_t j = 0; j <= ny_; ++j) {
            double y = c + j * hy;
            
            // Determine weight based on position
            double weight = 1.0;
            
            // Interior points: weight 4
            if (i > 0 && i < nx_ && j > 0 && j < ny_) {
                weight = 4.0;
            }
            // Edge points (not corners): weight 2
            else if ((i == 0 || i == nx_) && (j > 0 && j < ny_)) {
                weight = 2.0;
            }
            else if ((j == 0 || j == ny_) && (i > 0 && i < nx_)) {
                weight = 2.0;
            }
            // Corners: weight 1 (already set)
            
            sum += weight * f(x, y);
        }
    }
    
    return (hx * hy / 4.0) * sum;
}