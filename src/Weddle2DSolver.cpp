#include "Weddle2DSolver.h"

/*
Implementation fo the 2D Weddle Solver.
Tensor product extension: corners + edge midpoints + cell midpoints
*/

double Weddle2DSolver::integrate(const Function2D& f,
                                  double a, double b,
                                  double c, double d) const {
    validate_intervals(a, b, c, d);
    
    const double hx = (b - a) / static_cast<double>(nx_);
    const double hy = (d - c) / static_cast<double>(ny_);
    
    // Corner points
    double sum = f(a, c) + f(a, d) + f(b, c) + f(b, d);
    
    // Edge midpoints in x direction (top and bottom edges)
    for (std::size_t i = 0; i < nx_; ++i) {
        double x_mid = a + (static_cast<double>(i) + 0.5) * hx;
        sum += 2.0 * f(x_mid, c);  // bottom edge
        sum += 2.0 * f(x_mid, d);  // top edge
    }
    
    // Edge midpoints in y direction (left and right edges)
    for (std::size_t j = 0; j < ny_; ++j) {
        double y_mid = c + (static_cast<double>(j) + 0.5) * hy;
        sum += 2.0 * f(a, y_mid);  // left edge
        sum += 2.0 * f(b, y_mid);  // right edge
    }
    
    // Interior midpoints
    for (std::size_t i = 0; i < nx_; ++i) {
        double x_mid = a + (static_cast<double>(i) + 0.5) * hx;
        for (std::size_t j = 0; j < ny_; ++j) {
            double y_mid = c + (static_cast<double>(j) + 0.5) * hy;
            sum += 4.0 * f(x_mid, y_mid);
        }
    }
    
    return sum * (hx * hy / 4.0);
}