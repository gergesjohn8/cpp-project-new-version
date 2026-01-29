#pragma once
#include "Function.h"
#include <stdexcept>

// Abstract base class for numerical integrators
class Solver {
public:
    // Integrate f on [a,b] and return approximate integral.
    // Concrete classes implement this.
    // Inputs: A reference to a Function object that will be integrated and two double that specify the interval.
    // virtual -> polymorphism
    // all derived classes need to implement the method integrate which takes a function object and an interval
    // const -> method does not change the solver object
    // = 0 makes the Solver class abstract
    virtual double integrate(const Function& f, double a, double b) const = 0;
    virtual ~Solver() = default;

protected:
    // Optional helper: validate interval
    // just a method to check if a given interval is valid, i.e. a<b
    // the method is static, meaning it is a class method not a method of an object
    static void validate_interval(double a, double b) {
        if (!(a < b)) throw std::invalid_argument("Invalid interval: require a < b");
    }
};
