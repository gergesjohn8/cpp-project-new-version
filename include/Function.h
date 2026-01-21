#pragma once
#include <functional>

// Abstract base for integrand functions
class Function {
public:
    // Evaluate function at x
    virtual double operator()(double x) const = 0;
    virtual ~Function() = default;
};

// A small utility wrapper so you can create a Function from std::function
class FunctionFromStd : public Function {
public:
    explicit FunctionFromStd(std::function<double(double)> fn) : fn_(std::move(fn)) {}
    double operator()(double x) const override { return fn_(x); }
private:
    std::function<double(double)> fn_;
};


