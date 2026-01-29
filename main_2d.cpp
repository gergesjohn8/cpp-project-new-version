#include <iostream>
#include <iomanip>
#include <cmath>
#include <memory>
#include <vector>
#include <string>
 

#include "Function2D.h"
#include "Functions2DConcrete.h"
#include "Solver2D.h"
#include "Trapezoid2DSolver.h"
#include "Simpson2DSolver.h"
#include "Weddle2DSolver.h"
#include "MonteCarlo2DSolver.h"


/*
File for evaluating the integration algorithms in the two dimensional case.
*/


int main() {

    // Create objects of the test functions.
    G1 g1;
    G2 g2;
    G3 g3;
    G4 g4;
    
    // Create a vector of solver objects.
    // Use smartpointers.
    std::vector<std::unique_ptr<Solver2D>> solvers;
    solvers.emplace_back(std::make_unique<Trapezoid2DSolver>(100, 100));
    solvers.emplace_back(std::make_unique<Simpson2DSolver>(100, 100));
    solvers.emplace_back(std::make_unique<Weddle2DSolver>(100, 100));
    solvers.emplace_back(std::make_unique<MonteCarlo2DSolver>(1000000, 42));
    
    // for printing
    const std::vector<std::string> solver_names = {
        "Trapezoid 2D (100x100)",
        "Simpson 2D   (100x100)",
        "Weddle 2D    (100x100)",
        "Monte Carlo 2D (1M)"
    };
    
    std::cout << std::setprecision(12) << std::fixed;
    
    // true values of the integrals to be tested
    const double true_g1 = 2.0 / 3.0;
    const double true_g2 = 0.25;
    const double true_g3 = (std::exp(1.0) - 1.0) * (std::exp(1.0) - 1.0);
    const double pi = 3.14159265; // Pi rounded
    const double true_g4 = 0.0;
    
    /*
    For each function we iterate over the vector of solvers and run the integrate method of that solver for this specific function.
    Then the result is compare with the true value and the error is calculated.
    The results are printed in the console.
    */


    // TEST 1
    std::cout << "============================================================\n";
    std::cout << "2D INTEGRAL 1: x^2 + y^2 over [0,1] x [0,1]\n";
    std::cout << "True value: " << true_g1 << "\n";
    std::cout << "============================================================\n";
    for (std::size_t i = 0; i < solvers.size(); ++i) {
        double result = solvers[i]->integrate(g1, 0.0, 1.0, 0.0, 1.0);
        double error = std::abs(result - true_g1);
        std::cout << "  " << solver_names[i] << " -> " << result
                  << "  (error: " << std::scientific << error << std::fixed << ")\n";
    }
    
    // TEST 2
    std::cout << "\n============================================================\n";
    std::cout << "2D INTEGRAL 2: x*y over [0,1] x [0,1]\n";
    std::cout << "True value: " << true_g2 << "\n";
    std::cout << "============================================================\n";
    for (std::size_t i = 0; i < solvers.size(); ++i) {
        double result = solvers[i]->integrate(g2, 0.0, 1.0, 0.0, 1.0);
        double error = std::abs(result - true_g2);
        std::cout << "  " << solver_names[i] << " -> " << result
                  << "  (error: " << std::scientific << error << std::fixed << ")\n";
    }
    
    // TEST 3
    std::cout << "\n============================================================\n";
    std::cout << "2D INTEGRAL 3: e^(x+y) over [0,1] x [0,1]\n";
    std::cout << "True value: " << true_g3 << "\n";
    std::cout << "============================================================\n";
    for (std::size_t i = 0; i < solvers.size(); ++i) {
        double result = solvers[i]->integrate(g3, 0.0, 1.0, 0.0, 1.0);
        double error = std::abs(result - true_g3);
        std::cout << "  " << solver_names[i] << " -> " << result
                  << "  (error: " << std::scientific << error << std::fixed << ")\n";
    }
    
    // TEST 4
    std::cout << "\n============================================================\n";
    std::cout << "2D INTEGRAL 4: sin(x)*cos(y) over [0,pi] x [0,pi]\n";
    std::cout << "True value: " << true_g4 << "\n";
    std::cout << "============================================================\n";
    for (std::size_t i = 0; i < solvers.size(); ++i) {
        double result = solvers[i]->integrate(g4, 0.0, pi, 0.0, pi);
        double error = std::abs(result - true_g4);
        std::cout << "  " << solver_names[i] << " -> " << result
                  << "  (error: " << std::scientific << error << std::fixed << ")\n";
    }
    
    std::cout << "\n============================================================\n";
    std::cout << "ALL 4 TESTS COMPLETED WITH 4 METHODS EACH\n";
    std::cout << "============================================================\n";
    
    return 0;
}