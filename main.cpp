#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>
#include <cmath>

#include "FunctionsConcrete.h"
#include "TrapezoidSolver.h"
#include "SimpsonSolver.h"
#include "WeddleSolver.h"
#include "MonteCarloSolver.h"

int main() {
    // Create function objects
    F1 f1;
    F2 f2;
    F3 f3;
    F4 f4;

    // Create a collection of solvers (polymorphic)
    std::vector<std::unique_ptr<Solver>> solvers;

    
    solvers.emplace_back(std::make_unique<TrapezoidSolver>(10000));
    solvers.emplace_back(std::make_unique<SimpsonSolver>(10000));
    solvers.emplace_back(std::make_unique<WeddleSolver>(10000));
    solvers.emplace_back(std::make_unique<MonteCarloSolver>(1000000, 42));
    



    // Names for printing
    const std::vector<std::string> solver_names = {
        "Trapezoid (n=10000)",
        "Simpson   (n=10000)",
        "Weddle      (n=10000)",
        "Monte Carlo (n=1000000)"
    };

    R"(std::cout << std::setprecision(12);

    const double a = 0.0, b = 1.0;
    std::cout << "Integrate f1(x)=x^2*cos(x) over [0,1]\n";
    for (std::size_t i = 0; i < solvers.size(); ++i) {
        double val = solvers[i]->integrate(f1, a, b);
        std::cout << "  " << solver_names[i] << " -> " << val << "\n";
    }

    std::cout << "\nIntegrate f2(x)=x^10 over [0,1]\n";
    for (std::size_t i = 0; i < solvers.size(); ++i) {
        double val = solvers[i]->integrate(f2, a, b);
        std::cout << "  " << solver_names[i] << " -> " << val << "\n";
    }

    // Example: also show usage with std::function wrapper
    FunctionFromStd halfPower([](double x){ return std::sqrt(x); });
    std::cout << "\nIntegrate sqrt(x) over [0,1] with Simpson (for demo): "
              << std::make_unique<SimpsonSolver>(1000)->integrate(halfPower, 0.0, 1.0)
              << "\n";
    return 0;
})"

//============================================
//option 2 for display :

// True values for comparison
    const double true_f1 = 2.0 * std::cos(1.0) - std::sin(1.0);  // ≈ 0.38177329
    const double true_f2 = 1.0 / 11.0;                            // ≈ 0.09090909
    const double true_f3 = 2.0;                                   // exactly 2
    const double true_f4 = -1.0;                                  // exactly -1

    // Set output precision to 12 decimal places
    std::cout << std::setprecision(12) << std::fixed;


    std::cout << "============================================================\n";
    std::cout << "INTEGRAL 1: integral of x^2 * cos(x) from 0 to 1\n";
    std::cout << "True value: " << true_f1 << "\n";
    std::cout << "============================================================\n";
    
    for (std::size_t i = 0; i < solvers.size(); ++i) {
        double result = solvers[i]->integrate(f1, 0.0, 1.0);
        double error = std::abs(result - true_f1);
        std::cout << "  " << solver_names[i]
                  << " -> " << result
                  << "  (error: " << std::scientific << error << std::fixed << ")\n";
    }

    std::cout << "\n============================================================\n";
    std::cout << "INTEGRAL 2: integral of x^10 from 0 to 1\n";
    std::cout << "True value: " << true_f2 << "\n";
    std::cout << "============================================================\n";
    
    for (std::size_t i = 0; i < solvers.size(); ++i) {
        double result = solvers[i]->integrate(f2, 0.0, 1.0);
        double error = std::abs(result - true_f2);
        std::cout << "  " << solver_names[i]
                  << " -> " << result
                  << "  (error: " << std::scientific << error << std::fixed << ")\n";
    }


    const double epsilon = 1e-10;  // 0.0000000001
    
    std::cout << "\n============================================================\n";
    std::cout << "INTEGRAL 3: integral of x^(-1/2) from 0 to 1\n";
    std::cout << "(using epsilon=" << epsilon << " to avoid singularity at x=0)\n";
    std::cout << "True value: " << true_f3 << "\n";
    std::cout << "============================================================\n";
    
    for (std::size_t i = 0; i < solvers.size(); ++i) {
        double result = solvers[i]->integrate(f3, epsilon, 1.0);
        double error = std::abs(result - true_f3);
        std::cout << "  " << solver_names[i]
                  << " -> " << result
                  << "  (error: " << std::scientific << error << std::fixed << ")\n";
    }


    std::cout << "\n============================================================\n";
    std::cout << "INTEGRAL 4: integral of log(x) from 0 to 1\n";
    std::cout << "(using epsilon=" << epsilon << " to avoid singularity at x=0)\n";
    std::cout << "True value: " << true_f4 << "\n";
    std::cout << "============================================================\n";
    
    for (std::size_t i = 0; i < solvers.size(); ++i) {
        double result = solvers[i]->integrate(f4, epsilon, 1.0);
        double error = std::abs(result - true_f4);
        std::cout << "  " << solver_names[i]
                  << " -> " << result
                  << "  (error: " << std::scientific << error << std::fixed << ")\n";
    }


    std::cout << "\n============================================================\n";
    std::cout << "SUMMARY\n";
    std::cout << "============================================================\n";
    std::cout << "Methods implemented:\n";
    std::cout << "  1. Trapezoid Rule  - Composite trapezoidal quadrature, O(h^2)\n";
    std::cout << "  2. Simpson's Rule  - Composite Simpson's 1/3 rule, O(h^4)\n";
    std::cout << "  3. Weddle's Rule   - Endpoint + midpoint weighted sum, O(h^2)\n";
    std::cout << "  4. Monte Carlo     - Random sampling, O(n^(-0.5))\n";
    std::cout << "\nNote: Monte Carlo has higher variance but works well in higher dimensions.\n";
    std::cout << "Simpson's Rule typically gives the best accuracy for smooth functions.\n";

    return 0;
};
