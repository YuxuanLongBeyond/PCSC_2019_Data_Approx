//
// Created by Yuxuan Long on 24/11/19.
//

#ifndef PROJECT_FITTER_H
#define PROJECT_FITTER_H


#include <iostream>
#include <vector>
#include "Matrix.h"

/**
 * In this class, we aim to solve data fitting problem. Given a set of 2D points {(x_i, y_i)},
 * we want to approximate a function f s.t. f(x_i) = y_i, where f can have its parameter w.
 *
 * This class provides the implementation of four methods for data fitting (or interpolation):
 * 1. Polynomial fitting, i.e. polyfit, polyval
 * 2. Linear piecewise interpolation, i.e. interp1
 * 3. Cubic spline interpolation, i.e. spline
 * 4. Fourier interpolation, i.e. dct_fit, dct_val
 *
 * Note that the usage of the previous three methods are very similar to the ones in Matlab.
 */
class Fitter {
private:
    /**
     * Input 1D vector X containing all scalar samples x_i
     */
    std::vector<double> data_x;

    /**
     * Input 1D vector Y containing all scalar samples y_i which corresponds to x_i
     */
    std::vector<double> data_y;

    /**
     * Number of samples provided for data fitting
     */
    int N;
public:
    /**
     * Constructor for reading the input data of x and y
     * x and y here are 1D vector having the same size
     * @param x
     * @param y
     */
    Fitter(std::vector<double>& x, std::vector<double>& y);

    /**
     * Polynomial fitting (non-piecewise) with some degree
     * @param degree degree of polynomial being approximated
     * @param lambda small non-negative number to be added on the diagonal when solving the linear system
     * @return the optimized parameter w for the polynomial. Note w has length of degree + 1
     */
    std::vector<double> polyfit(int degree, double lambda) const;

    /**
     * Evaluation of the approximated polynomial given the test sample points
     * @param w the optimized parameter w for the polynomial, usually obtained from polyfit()
     * @param x_test 1D vector containing the test sample points
     * @return 1D vector containing the evaluated polynomial values corresponding to the test sample points
     */
    std::vector<double> polyval(std::vector<double>& w, std::vector<double>& x_test) const;

    /**
     * Find the index of the largest sample point smaller than the input point;
     * It also assumes that the input data x are in increasing order;
     * This function is used in finding the interval for interpolation
     * @param start_index a lower bound of the returned index
     * @param v the scalar input point
     * @return the index of the largest sample point smaller than the input point v
     */
    int find_index(int start_index, double v) const;

    /**
     * Linear piecewise interpolation
     * @param x_test the test data points to be interpolated
     * @return the polynomial values evaluated at corresponding test data points
     */
    std::vector<double> interp1(std::vector<double>& x_test) const;

    /**
     * Evaluate the approximated polynomial given one test sample point
     * @param index the index for extracting the parameters for one piece of the cubic polynomial
     * @param x the sample point to be evaluated
     * @param param all the parameters for the piecewise polynomials
     * @return the evaluated polynomial value corresponding to the input sample point
     */
    double spline_val(int index, double x, std::vector<double> param) const;

    /**
     * Cubic spline interpolation by solving a large linear system
     * @param x_test a vector of test data points being evaluated for interpolation
     * @return the evaluated polynomial value corresponding to all input sample points
     */
    std::vector<double> spline(std::vector<double>& x_test) const;

    /**
     * Computation of real Fourier coefficients by discrete cosine transform (DCT);
     * It assumes that the data points stored are real, periodic and evenly spaced
     * @return the real coefficients for DCT
     */
    std::vector<double> dct_fit() const;

    /**
     * Inverse discrete cosine transform (IDCT) for Fourier interpolation
     * @param w the real coefficients of DCT, usually obtained from the function dct_fit()
     * @param x_test a vector of test data points being evaluated for Fourier interpolation
     * @return the interpolated values corresponding to the input test points
     */
    std::vector<double> dct_val(std::vector<double>& w, std::vector<double>& x_test) const;

    std::vector<double> approx_test(const std::string& approx_method, const Fitter& approx, std::vector<double> X_test, int poly_degree, double poly_lambda) const;
};

#endif //PROJECT_FITTER_H
