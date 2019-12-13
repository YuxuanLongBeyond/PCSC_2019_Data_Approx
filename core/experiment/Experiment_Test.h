//
// Created by yiting on 07.12.19.
//

#ifndef PROJECT_EXPERIMENT_TEST_H
#define PROJECT_EXPERIMENT_TEST_H

#include <iostream>
#include <fstream>
#include <vector>
#include "../src/Fitter.h"
#include "DataIO.h"
/**
 * This class is used for approximating test data and analysis of the result of data approximation
 * The main functions of this class are:
 * 1. Generate approximated data by a given type of approximation method and relevant parameters
 * 2. Calculate the error between the actual values and the approximated values
 */

class Experiment_Test {
private:
public:
    /**
     * Constructor with default setting
     */
    Experiment_Test();

    /**
     * Generate approximated data Y according to a set of test data X
     * @param approx_method the name of the data fitting method
     * @param approx the fitter used for approximation
     * @param X_test 1D vector X containing all scalar test samples x_i
     * @param poly_degree degree of polynomial being approximated
     * @param poly_lambda small non-negative number to be added on the diagonal when solving the linear system
     * @return 1D vector Y approximated from corresponding data X
     */
    std::vector<double> approx_test(const std::string& approx_method, const Fitter& approx, std::vector<double> X_test, int poly_degree, double poly_lambda) const;

    /**
     * Calculate the error between actual value and the interpolated values from approximation
     * @param choice_f choice for type of function used for generating data, which is 1 or 2:
     * 1 for y = cos(3 * Pi * x); 2 for Runge function: y = 1 / (1 + x ^ 2); 3 for polynomial y = x^3 - 2x + 3
     * @param x 1D vector X containing all scalar samples x_i for test
     * @param y 1D vector Y containing all scalar approximated samples y_i
     * @param N_test number of test data points
     */
    static void compute_error(int choice_f, std::vector<double> x, std::vector<double> y, int N_test);

};


#endif //PROJECT_EXPERIMENT_TEST_H