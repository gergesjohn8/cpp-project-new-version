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

    std::cout << std::setprecision(12);

    

//============================================

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


    const double epsilon_f3 = 1e-6;
    const double true_f3_adjusted = 2.0 - 2.0 * std::sqrt(epsilon_f3); 
    
    std::cout << "\n============================================================\n";
    std::cout << "INTEGRAL 3: integral of x^(-1/2) from " << epsilon_f3 << " to 1\n";
    std::cout << "True value of integral[" << epsilon_f3 << ",1] x^(-1/2) dx = " << true_f3_adjusted << "\n";
    std::cout << "(Note: Full integral from 0 to 1 = 2.0)\n";
    std::cout << "============================================================\n";

    // Create higher-resolution solvers for this difficult function
    std::vector<std::unique_ptr<Solver>> solvers_f3;
    solvers_f3.emplace_back(std::make_unique<TrapezoidSolver>(100000));     // 100,000 intervals
    solvers_f3.emplace_back(std::make_unique<SimpsonSolver>(100000));       // 100,000 intervals
    solvers_f3.emplace_back(std::make_unique<WeddleSolver>(100000));      // 100,000 intervals
    solvers_f3.emplace_back(std::make_unique<MonteCarloSolver>(1000000, 42));
    
        const std::vector<std::string> solver_names_f3 = {
        "Trapezoid   (n=100000)",
        "Simpson     (n=100000)",
        "Midpoint    (n=100000)",
        "Monte Carlo (M=1000000)"
    };
    
    for (std::size_t i = 0; i < solvers_f3.size(); ++i) {
        double result = solvers_f3[i]->integrate(f3, epsilon_f3, 1.0);
        double error = std::abs(result - true_f3_adjusted);
        std::cout << "  " << solver_names_f3[i] 
                  << " -> " << result 
                  << "  (error: " << std::scientific << error << std::fixed << ")\n";
    }


    const double epsilon_f4 = 1e-10;
    const double true_f4_adjusted = -1.0 - epsilon_f4 * (std::log(epsilon_f4) - 1.0);

    std::cout << "\n============================================================\n";
    std::cout << "INTEGRAL 4: integral of log(x) from " << epsilon_f4 << " to 1\n";
    std::cout << "True value of integral[" << epsilon_f4 << ",1] log(x) dx = " << true_f4_adjusted << "\n";
    std::cout << "(Note: Full integral from 0 to 1 = -1.0)\n";
    std::cout << "============================================================\n";

    // Create higher-resolution solvers for this function too
    std::vector<std::unique_ptr<Solver>> solvers_f4;
    solvers_f4.emplace_back(std::make_unique<TrapezoidSolver>(100000));
    solvers_f4.emplace_back(std::make_unique<SimpsonSolver>(100000));
    solvers_f4.emplace_back(std::make_unique<WeddleSolver>(100000));
    solvers_f4.emplace_back(std::make_unique<MonteCarloSolver>(1000000, 42));
    
     const std::vector<std::string> solver_names_f4 = {
        "Trapezoid   (n=100000)",
        "Simpson     (n=100000)",
        "Midpoint    (n=100000)",
        "Monte Carlo (M=1000000)"
    };
    
    for (std::size_t i = 0; i < solvers_f4.size(); ++i) {
        double result = solvers_f4[i]->integrate(f4, epsilon_f4, 1.0);
        double error = std::abs(result - true_f4_adjusted);
        std::cout << "  " << solver_names_f4[i] 
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




    
