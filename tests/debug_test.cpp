//
// Created by Yuxuan Long on 12/12/19.
//
#include <gtest/gtest.h>
#include <iostream>
#include "../core/test/DataIO.h"
#include "../core/test/Experiment_Test.h"
#include <cmath>

int choice_node = 1;
int N_gen = 41;
double x_min = -10;
double x_max = 10;
int choice_f = 2;
int N_test = 1001;
int poly_degree = 20;
double x_test_min = -10;
double x_test_max = 10;
double poly_lambda = 0;

double tol = 1e-7;


double compute_mse(std::vector<double> Y_test, std::vector<double> Y_matlab) {
    if (Y_test.size() != Y_matlab.size()){
        throw std::invalid_argument("Incompatible data size!");
    }
    double mse = 0.0;
    int N = Y_test.size();
    for (int i = 0; i < N; i++){
        // calculate the sum of square of error
        mse = mse + pow((Y_test[i] - Y_matlab[i]),2);
    }
    // calculate the mean value
    mse = mse / N;
    std::cout << "The MSE between data approximated by our implementation and Matlab built-in functions is " << mse << std::endl;
    return mse;
}


double compute_debug_mse(std::string& approx_method, std::string& mat_file) {

    std::vector<double> X; std::vector<double> Y; // input data
    std::vector<double> X_test(N_test); std::vector<double> Y_test(N_test); // test data
    std::vector<double> X_mat(N_test); std::vector<double> Y_mat(N_test); // Matlab data

    DataIO data_handler;
    Experiment_Test test;
    X = data_handler.gen_x(choice_node, N_gen, x_min, x_max);
    Y = data_handler.gen_y(choice_f, N_gen, X);

    Fitter approx(X, Y);

    X_test = data_handler.gen_x_test(N_test, x_test_min, x_test_max);
    Y_test = test.approx_test(approx_method, approx, X_test, poly_degree, poly_lambda);

    data_handler.data_reader(mat_file);
    X_mat = data_handler.get_data_x();
    Y_mat = data_handler.get_data_y();
    std::vector<double> Y_test_new = Y_test;
    if (approx_method == "dct") {
        Y_test_new = test.approx_test(approx_method, approx, X_mat, poly_degree, poly_lambda);
    }
    return compute_mse(Y_test_new, Y_mat);
}

TEST(DebugTest, Poly_Test) {

    double mse;
    std::string approx_method = "polynomial";
    std::string mat_file = "../../tests/matlab_data/poly_Matlab.dat";

    mse = compute_debug_mse(approx_method, mat_file);

    ASSERT_NEAR(mse, 0, tol);
}


TEST(DebugTest, Interp1_Test) {

    double mse;
    std::string approx_method = "interp1";
    std::string mat_file = "../../tests/matlab_data/interp_Matlab.dat";

    mse = compute_debug_mse(approx_method, mat_file);

    ASSERT_NEAR(mse, 0, tol);
}

TEST(DebugTest, Spline_Test) {

    double mse;
    std::string approx_method = "spline";
    std::string mat_file = "../../tests/matlab_data/spline_Matlab.dat";

    mse = compute_debug_mse(approx_method, mat_file);

    ASSERT_NEAR(mse, 0, tol);
}

TEST(DebugTest, DCT_Test) {

    double mse;
    std::string approx_method = "dct";
    std::string mat_file = "../../tests/matlab_data/ft_Matlab.dat";

    mse = compute_debug_mse(approx_method, mat_file);

    ASSERT_NEAR(mse, 0, tol);
}