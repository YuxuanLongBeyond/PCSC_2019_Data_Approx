//
// Created by Yuxuan Long on 24/11/19.
//


#include <stdexcept>
#include <cmath>
#include "Approximator.h"

Approximator::Approximator(std::vector<double>& data_x, std::vector<double>& data_y) {
    int n1 = data_x.size();
    int n2 = data_y.size();
    if (n1 != n2) {
        throw std::invalid_argument("Incompatible data size");
    }
    N = n1;
    for (int i = 1; i < N; i ++) {
        x[i] = data_x[i];
        y[i] = data_y[i];
    }
}

std::vector<double> Approximator::polyfit(int degree) const {

}

std::vector<double> Approximator::polyval(std::vector<double>& x_test, std::vector<double>& w) const {

}

std::vector<double> Approximator::interp1(std::vector<double>& x_test) const{

}
std::vector<double> Approximator::spline(std::vector<double>& x_test) const {

}