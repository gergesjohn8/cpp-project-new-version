#pragma once
#include <functional>

// Abstract base for integrand functions
class Function {
public:
    // Evaluate function at x
    // All child classes have to overwrite the () operator. This will make objects "callable".
    // virtual allows for polymorphism
    // const means the object itself is not changed
    // =0 makes the class abstract, you can not instantiate the class directly
    virtual double operator()(double x) const = 0;
    virtual ~Function() = default;
};