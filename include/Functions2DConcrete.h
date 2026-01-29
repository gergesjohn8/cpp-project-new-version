#pragma once
#include "Function2D.h"
#include <cmath>

// G1(x,y) = x^2 + y^2
// Integral over [0,1] x [0,1] = 2/3
class G1 : public Function2D {
public:
    double operator()(double x, double y) const override {
        return x*x + y*y;
    }
};

// G2(x,y) = x * y
// Integral over [0,1] x [0,1] = 1/4
class G2 : public Function2D {
public:
    double operator()(double x, double y) const override {
        return x * y;
    }
};

// G3(x,y) = e^(x+y)
// Integral over [0,1] x [0,1] = (e-1)^2
class G3 : public Function2D {
public:
    double operator()(double x, double y) const override {
        return std::exp(x + y);
    }
};

// G4(x,y) = sin(x) * cos(y)
// Integral over [0,pi] x [0,pi] = 0
class G4 : public Function2D {
public:
    double operator()(double x, double y) const override {
        return std::sin(x) * std::cos(y);
    }
};