#pragma once
#include "Solver2D.h"
#include <cstddef>

class Simpson2DSolver : public Solver2D {
public:
    // constructor fo Simpson2DSolver, takes number of discretization points in x and y direction as argument
    // explicit prevents implicit creation
    // n must be even for Simpson's rule
    explicit Simpson2DSolver(std::size_t nx = 100, std::size_t ny = 100) 
        : nx_((nx % 2 == 0) ? nx : nx + 1), 
          ny_((ny % 2 == 0) ? ny : ny + 1) {}
    
    // integrate method to be oerridden
    double integrate(const Function2D& f,
                    double a, double b,
                    double c, double d) const override;

private:
    std::size_t nx_;
    std::size_t ny_;
};