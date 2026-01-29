#pragma once
#include "Solver.h"
#include <cstddef>



class WeddleSolver : public Solver {
public:
    // constructor with explicit keyword to ensure no implicit creation
    explicit WeddleSolver(std::size_t n = 1000) : n_(n ? n : 1) {}
    // integrate method to be overridden
    double integrate(const Function& f, double a, double b) const override;

private:
    std::size_t n_;  // number of subintervals
};


