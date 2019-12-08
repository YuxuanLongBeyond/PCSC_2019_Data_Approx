//
// Created by yiting on 07.12.19.
//

#include "Test.h"
#include <cmath>
#include <cassert>

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
