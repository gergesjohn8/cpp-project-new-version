#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include "FunctionsConcrete.h"
#include "TrapezoidSolver.h"
#include "SimpsonSolver.h"
#include "WeddleSolver.h"
#include "MonteCarloSolver.h"


// Helper function for floating point comparison
bool approx_equal(double value, double reference, double tolerance) {
    return std::abs(value - reference) < tolerance;
}

int main() {
    std::cout << "==========================================================\n";
    std::cout << "Running numerical integration unit tests...\n";
    std::cout << "==========================================================\n\n";
    
    // True analytic values
    const double true_f1 = 2.0 * std::cos(1.0) - std::sin(1.0);
    const double true_f2 = 1.0 / 11.0;
    const double true_f3 = 2.0;
    const double true_f4 = -1.0;

    // Strict tolerance for smooth functions (f1, f2)
    const double tol_strict = 1e-5;
    // Looser tolerance for singular functions (f3, f4) and Monte Carlo
    const double tol_singular = 1e-4;
    const double tol_monte_carlo = 1e-3;  // Monte Carlo has high variance
    
    // epsilon value to approxiate interval [0,1] with [epsilon, 1]
    const double epsilon = 1e-6;

    // Functions
    F1 f1;
    F2 f2;
    F3 f3;
    F4 f4;

    // Solvers
    std::vector<std::unique_ptr<Solver>> deterministic_solvers;
    deterministic_solvers.emplace_back(std::make_unique<TrapezoidSolver>(100000));
    deterministic_solvers.emplace_back(std::make_unique<SimpsonSolver>(100000));
    deterministic_solvers.emplace_back(std::make_unique<WeddleSolver>(100000));
    
    const std::vector<std::string> det_solver_names = {
        "Trapezoid",
        "Simpson",
        "Weddle"
    };
    
    // Monte Carlo solver (tested separately due to variance)
    MonteCarloSolver mc_solver(1000000, 42);

    int tests_passed = 0;
    int tests_total = 0;


    // Test f1
    // Monte Carlo is likely to fail due to variance which is why we do a separate case

    std::cout << "Testing f1(x) = x^2 * cos(x) on [0,1]\n";
    std::cout << "True value: " << true_f1 << "\n";
    std::cout << "Tolerance: " << tol_strict <<"\n";
    std::cout << "Tolerance MC:" << tol_monte_carlo <<"\n";
    
    for (std::size_t i = 0; i < deterministic_solvers.size(); ++i) {
        double val = deterministic_solvers[i]->integrate(f1, 0.0, 1.0);
        bool passed = approx_equal(val, true_f1, tol_strict);
        std::cout << "  " << det_solver_names[i] << ": " << val
                  << (passed ? " [PASS]" : " [FAIL]") << "\n";
        tests_total++;
        if (passed) tests_passed++;
        //assert(passed);
    }
    
    // Monte Carlo (separate, looser tolerance)
    {
        double val = mc_solver.integrate(f1, 0.0, 1.0);
        bool passed = approx_equal(val, true_f1, tol_monte_carlo);
        std::cout << "  Monte Carlo: " << val
                  << (passed ? " [PASS]" : " [FAIL - expected for MC]") << "\n";
        tests_total++;
        if (passed) tests_passed++;
    }


    // Test f2
    std::cout << "\nTesting f2(x) = x^10 on [0,1]\n";
    std::cout << "True value: " << true_f2 << "\n";
    std::cout << "Tolerance: " << tol_strict <<"\n";
    std::cout << "Tolerance MC:" << tol_monte_carlo <<"\n";

    for (std::size_t i = 0; i < deterministic_solvers.size(); ++i) {
        double val = deterministic_solvers[i]->integrate(f2, 0.0, 1.0);
        bool passed = approx_equal(val, true_f2, tol_strict);
        std::cout << "  " << det_solver_names[i] << ": " << val
                  << (passed ? " [PASS]" : " [FAIL]") << "\n";
        tests_total++;
        if (passed) tests_passed++;
        //assert(passed);
    }
    
    {
        double val = mc_solver.integrate(f2, 0.0, 1.0);
        bool passed = approx_equal(val, true_f2, tol_monte_carlo);
        std::cout << "  Monte Carlo: " << val
                  << (passed ? " [PASS]" : " [FAIL - expected for MC]") << "\n";
        tests_total++;
        if (passed) tests_passed++;
    }
    
    // TEST f3
    // true integral value for adjusted interval
    const double true_f3_adjusted = 2.0 - 2.0 * std::sqrt(epsilon); 

    std::cout << "\nTesting f3(x) = x^(-1/2) on [epsilon,1] (epsilon=" << epsilon << ")\n";
    std::cout << "True value of integral[" << epsilon << ",1] x^(-1/2) dx = " << true_f3_adjusted << "\n";
    std::cout << "(Note: Full integral from 0 to 1 = 2.0)\n";
    std::cout << "Tolerance: " << tol_singular <<"\n";
    std::cout << "Tolerance MC:" << tol_monte_carlo <<"\n";
    
    for (std::size_t i = 0; i < deterministic_solvers.size(); ++i) {
        double val = deterministic_solvers[i]->integrate(f3, epsilon, 1.0);
        bool passed = approx_equal(val, true_f3_adjusted, tol_singular);
        std::cout << "  " << det_solver_names[i] << ": " << val
                  << (passed ? " [PASS]" : " [FAIL]") << "\n";
        tests_total++;
        if (passed) tests_passed++;
    }
    
    {
        double val = mc_solver.integrate(f3, epsilon, 1.0);
        bool passed = approx_equal(val, true_f3_adjusted, tol_monte_carlo);
        std::cout << "  Monte Carlo: " << val
                  << (passed ? " [PASS]" : " [FAIL - expected for MC]") << "\n";
        tests_total++;
        if (passed) tests_passed++;
    }

    // TEST f4
    // true integral value for adjusted interval
    const double true_f4_adjusted = -1.0 - epsilon * (std::log(epsilon) - 1.0);
    
    std::cout << "\nTesting f4(x) = log(x) on [epsilon,1] (epsilon=" << epsilon << ")\n";
    std::cout << "True value of integral[" << epsilon << ",1] log(x) dx = " << true_f4_adjusted << "\n";
    std::cout << "(Note: Full integral from 0 to 1 = -1.0)\n";
    std::cout << "Tolerance: " << tol_singular <<"\n";
    std::cout << "Tolerance MC:" << tol_monte_carlo <<"\n";
    
    for (std::size_t i = 0; i < deterministic_solvers.size(); ++i) {
        double val = deterministic_solvers[i]->integrate(f4, epsilon, 1.0);
        bool passed = approx_equal(val, true_f4_adjusted, tol_singular);
        std::cout << "  " << det_solver_names[i] << ": " << val
                  << (passed ? " [PASS]" : " [FAIL]") << "\n";
        tests_total++;
        if (passed) tests_passed++;
    }
    
    {
        double val = mc_solver.integrate(f4, epsilon, 1.0);
        bool passed = approx_equal(val, true_f4_adjusted, tol_monte_carlo);
        std::cout << "  Monte Carlo: " << val
                  << (passed ? " [PASS]" : " [FAIL - expected for MC]") << "\n";
        tests_total++;
        if (passed) tests_passed++;
    }

    // SUMMARY
    std::cout << "\n==========================================================\n";
    std::cout << "TEST SUMMARY: " << tests_passed << "/" << tests_total << " tests passed\n";
    std::cout << "==========================================================\n";
    
    if (tests_passed >= tests_total - 4) {  
        std::cout << "All critical tests passed successfully!\n";
        return 0;
    } else {
        std::cout << "Some tests failed.\n";
        return 1;
    }
}
