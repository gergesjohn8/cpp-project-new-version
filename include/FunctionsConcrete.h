#pragma once
#include "Function.h"
#include <cmath>

/*
Several derived Function classes. These implement the operator () and represent the test functions.
*/


// f1(x) = x^2 * cos(x)
class F1 : public Function {
public:
    double operator()(double x) const override {
        return x * x * std::cos(x);
    }
};

// f2(x) = x^10
class F2 : public Function {
public:
    double operator()(double x) const override {
        // pow could be used but this is faster & exact for integer exponent
        double x2 = x*x;
        double x4 = x2*x2; // x^4
        double x8 = x4*x4; // x^8
        return x8 * x2;    // x^10
    }
};

// f3(x) = x^(-1/2) = 1/sqrt(x)
class F3 : public Function {
public:
    double operator()(double x) const override {
        return 1.0 / std::sqrt(x);  // 1/√x = x^(-1/2)
    }
};

// f4(x) = log(x) = natural logarithm

class F4 : public Function {
public:
    double operator()(double x) const override {
        return std::log(x);  // Natural logarithm (ln)
    }
};
