#pragma once



class Function2D {
public:
    // Evaluate function at (x, y)
    // every derived class has to override the () operator
    // virtual allows for polymorphism
    // const ensure the object is not modified
    // = 0 makes it abstract
    virtual double operator()(double x, double y) const = 0;
    virtual ~Function2D() = default;
};