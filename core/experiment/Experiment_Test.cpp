//
// Created by yiting on 07.12.19.
//

#include <stdexcept>
#include "Experiment_Test.h"
#include <cmath>
#include <vector>
#include "../src/Fitter.h"

Experiment_Test::Experiment_Test() = default;

std::vector<double> Experiment_Test::approx_test(const std::string& approx_method, const Fitter& approx, std::vector<double> X_test, int poly_degree, double poly_lambda) const{
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

void Experiment_Test::compute_error(int choice_f, std::vector<double> x_test, std::vector<double> y_test, int N_test) {
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

