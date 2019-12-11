//
// Created by yiting on 07.12.19.
//

#include <stdexcept>
#include "Test.h"
#include <cmath>
#include <vector>
#include "../src/Fitter.h"

Test::Test() = default;

std::vector<double> Test::approx_test(const std::string& approx_method, const Fitter& approx, std::vector<double> X_test, int poly_degree, double poly_lambda) const{
    if (approx_method != "polynomial" && approx_method != "interp1" && approx_method != "spline" && approx_method != "dct"){
        throw std::invalid_argument("Invalid input approximation method!");
    }
    std::vector<double> Y_test;
    std::vector<double> w;
    if (approx_method == "polynomial"){
        w = approx.polyfit(poly_degree, poly_lambda);
        Y_test = approx.polyval(w, X_test);
    }
    if (approx_method == "interp1"){
        Y_test = approx.interp1(X_test);
    }
    if (approx_method == "spline"){
        Y_test = approx.spline(X_test);
    }
    if (approx_method == "dct"){
        w = approx.dct_fit();
//        std::cout << w[0] << ' ' << w[1] << ' ' << w[2] << std::endl;
        Y_test = approx.dct_val(w, X_test);
    }
    return Y_test;
}

void Test::compute_error(int choice_f, std::vector<double> x_test, std::vector<double> y_test, int N_test) {
    if (choice_f != 1 && choice_f != 2 && choice_f != 3){
        throw std::invalid_argument("Invalid input choice for function type!");
    }
    if (x_test.size() != y_test.size()){
        throw std::invalid_argument("Incompatible data size!");
    }
    if (N_test < 2) {
        throw std::invalid_argument("Too little input test samples!");
    }
    double e = 0.0;
    std::vector<double> y_real(N_test); // ground-truth data y
    for (int i = 0; i < N_test; i++){
        // different choice of function
        if (choice_f == 1){
            y_real[i] = cos(3.0 * x_test[i] * M_PI);
        }
        else if(choice_f == 2){
            y_real[i] = 1.0 / (1.0 + x_test[i] * x_test[i]);
        }
        else{
            y_real[i] = pow(x_test[i], 3) - 2 * x_test[i] + 3;
        }
        // the error of approximation is the maximum value among the error between the actual value and the approximated value for each test point
        if (e < fabs(y_real[i] - y_test[i])){
            e = fabs(y_real[i] - y_test[i]);
        }
    }
    std::cout << "The error of the approximation w.r.t. the true data is "<< e << std::endl;
}

double Test::compute_mse(std::vector<double> Y_test, std::vector<double> Y_matlab) {
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

void Test::debug(int use_debug_mode, int N_test, int poly_degree, double poly_lambda, const std::vector<double>& Y_test, const std::string& mat_file, const std::string& approx_method, Test test, const Fitter& approx, DataIO data_handler){
    if (use_debug_mode){
        double mse;
        std::cout << "Debug mode is open" << std::endl;
        std::vector<double> X_mat(N_test); std::vector<double> Y_mat(N_test); // Matlab data
        data_handler.data_reader(const_cast<std::string &>(mat_file));
        X_mat = data_handler.get_data_x();
        Y_mat = data_handler.get_data_y();

        std::vector<double> Y_test_new = Y_test;
        // Fourier interpolation is a special one that uses different X_test to match with Matlab's built-in function
        if (approx_method == "dct") {
            Y_test_new = test.approx_test(approx_method, approx, X_mat, poly_degree, poly_lambda);
        }
        mse = test.compute_mse(Y_test_new, Y_mat);

    }
}