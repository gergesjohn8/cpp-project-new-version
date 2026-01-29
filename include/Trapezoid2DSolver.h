#pragma once
#include "Solver2D.h"
#include <cstddef>

class Trapezoid2DSolver : public Solver2D {
public:
    // constructor with explicit argument to prevent implicit creation
    // nx = intervals in x direction, ny = intervals in y direction
    explicit Trapezoid2DSolver(std::size_t nx = 100, std::size_t ny = 100) 
        : nx_(nx ? nx : 1), ny_(ny ? ny : 1) {}
    
    // integrate method to be overridden
    double integrate(const Function2D& f, 
                    double a, double b,
                    double c, double d) const override;

private:
    // private attributes
    std::size_t nx_;
    std::size_t ny_;
};