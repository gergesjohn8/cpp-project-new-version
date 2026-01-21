#pragma once
#include "Solver.h"
#include <cstddef>

class SimpsonSolver : public Solver {
public:
    // n is the number of subintervals; Simpson requires even n
    explicit SimpsonSolver(std::size_t n = 1000) : n_( (n%2==0) ? n : n+1 ) {}
    double integrate(const Function& f, double a, double b) const override;

private:
    std::size_t n_;
};
