//
// Created by yiting on 07.12.19.
//

#ifndef PROJECT_TEST_H
#define PROJECT_TEST_H

#include <iostream>
#include <fstream>
#include <vector>
#include "../src/Fitter.h"
/**
 * This class used for analysis the result of data approximation
 * We calculate the error between the real value and the approximation value
 */

class Test {
private:
public:
    /**
     * Constructor with default setting
     */
    Test();

    /**
     * Print the error between real value and the result from approximation
     * @param choice_f choice for type of function used for generating data, which is 1 or 2:
     * 1 is y = cos(3 * Pi * x), 2 is Runge function: y = 1 / (1 + x ^ 2)
     * @param x 1D vector X containing all scalar samples x_i for test
     * @param y 1D vector Y containing all scalar approximated samples y_i
     * @param N_test number of test data points
     */
    static void print_error_function(int choice_f, std::vector<double> x, std::vector<double> y, int N_test);


    std::vector<double> approx_test(const std::string& approx_method, const Fitter& approx, std::vector<double> X_test, int poly_degree, double poly_lambda) const;
};


#endif //PROJECT_TEST_H
