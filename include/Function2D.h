#pragma once



class Function2D {
public:
    // Evaluate function at (x, y)
    virtual double operator()(double x, double y) const = 0;
    virtual ~Function2D() = default;
};