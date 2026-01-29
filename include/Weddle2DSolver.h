#pragma once
#include "Solver2D.h"
#include <cstddef>

class Weddle2DSolver : public Solver2D {
public:
    explicit Weddle2DSolver(std::size_t nx = 100, std::size_t ny = 100) 
        : nx_(nx ? nx : 1), ny_(ny ? ny : 1) {}
    
    double integrate(const Function2D& f,
                    double a, double b,
                    double c, double d) const override;

private:
    std::size_t nx_;
    std::size_t ny_;
};
