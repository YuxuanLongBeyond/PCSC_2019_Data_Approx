//
// Created by yiting on 07.12.19.
//

#include "Test.h"
#include <cmath>
#include <cassert>
#include "../src/Fitter.h"

Test::Test() = default;

void Test::print_error_function(int choice_f, std::vector<double> x_test, std::vector<double> y_test, int N_test) {
    double e = 0.0;
    std::vector<double> y_real(N_test);
    for (int i = 0; i < N_test; i++){
        if (choice_f == 1){
            y_real[i] = cos(3.0 * x_test[i] * M_PI);
        }
        else{
            y_real[i] = 1.0 / (1.0 + x_test[i] * x_test[i]);
        }
        if (e < fabs(y_real[i] - y_test[i])){
            e = fabs(y_real[i] - y_test[i]);
        }
    }
    std::cout << e << std::endl;
}

std::vector<double> Test::approx_test(const std::string& approx_method, const Fitter& approx, std::vector<double> X_test, int poly_degree, double poly_lambda) const{
    std::vector<double> Y_test;
    std::vector<double> w;
    if (approx_method == "polynomial"){
        w = approx.polyfit(poly_degree, poly_lambda);
        Y_test = approx.polyval(w, X_test);
    }
    if (approx_method == "interpolation"){
        Y_test = approx.interp1(X_test);
    }
    if (approx_method == "spline"){
        Y_test = approx.spline(X_test);
    }
    if (approx_method == "dct"){
        w = approx.dct_fit();
        Y_test = approx.dct_val(w, X_test);
    }
    return Y_test;
}