//
// Created by Yuxuan Long on 24/11/19.
//


#include <stdexcept>
#include <cmath>
#include "Fitter.h"


Fitter::Fitter(std::vector<double>& x, std::vector<double>& y) {
    int n1 = x.size();
    int n2 = y.size();
    if (n1 != n2) {
        throw std::invalid_argument("Incompatible data size!");
    }

    N = n1;
    for (int i = 0; i < N; i ++) {
        data_x.push_back(x[i]);
        data_y.push_back(y[i]);
    }
}

std::vector<double> Fitter::polyfit(int degree) const {
    if (degree < 0) {
        throw std::invalid_argument("Degree should be positive!");
    }
    if (degree > N - 1) {
        throw std::invalid_argument("Degree should be equal or smaller than N - 1!");
    }
    std::vector<double> w;
    Matrix A(N, degree + 1);
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < degree + 1; j ++) {
            A[i][j] = pow(data_x[i], j);
        }
    }
    if (degree == N - 1) {
        w = gauss_solve(A, data_y);
    }
    else {
        w = least_squares(A, data_y, 0.0);
    }
    return w;
}

std::vector<double> Fitter::polyval(std::vector<double>& w, std::vector<double>& x_test) const {
    int m = x_test.size();
    int n = w.size();
    Matrix A(m, n);
    for (int i = 0; i < m; i ++) {
        for (int j = 0; j < n; j ++) {
            A[i][j] = pow(x_test[i], j);
        }
    }
//    std::cout << A << std::endl;
    std::vector<double> y_test;
    y_test = A * w;
    return y_test;
}

int Fitter::find_index(int start_index, double v) const {
    if (start_index == -1) {
        if (v < data_x[0]) {
            // extrapolation
            return start_index;
        }
        start_index += 1;
    }
    // v > data_x[start_index]
    int index = start_index + 1;
    while (index < N) {
        if (v < data_x[index]) {
            break;
        }
        index += 1;
    }
    return index - 1;
}

std::vector<double> Fitter::interp1(std::vector<double>& x_test) const{
    std::vector<double> y_test;
    std::vector<double> slope(N - 1);
    for (int i = 0; i < N - 1; i ++) {
        slope[i] = (data_y[i + 1] - data_y[i]) / (data_x[i + 1] - data_x[i]);
    }
    int index = -1; // start_index
    double interp_out;
    for (auto v: x_test) {

        if (index < N - 1) {
            index = find_index(index, v);
            if (index == -1) {
                // extrapolation
                interp_out = data_y[0] + slope[0] * (v - data_x[0]);
            }
            else {
                interp_out = data_y[index] + slope[index] * (v - data_x[index]);
            }
        }
        else {
            //extrapolation
            interp_out = data_y[N - 1] + slope[N - 2] * (v - data_x[N - 1]);
        }
        y_test.push_back(interp_out);
    }
    return y_test;
}

double spline_val(int index, double x, std::vector<double> param) {
    double result = 0.0;
    result += pow(x, 3) * param[4 * index];
    result += pow(x, 2) * param[4 * index + 1];
    result += x * param[4 * index + 2];
    result += param[4 * index + 3];
    return result;
}

std::vector<double> Fitter::spline(std::vector<double>& x_test) const {
    int m = 4 * (N - 1);
    Matrix A(m, m);
    std::vector<double> b(m);
//    std::cout << data_x[N - 1];

    // construct a linear system
    b[0] = 0.0; b[1] = data_y[0];
    A[0][0] = 6.0 * data_x[0]; A[0][1] = 2.0;
    A[1][0] = pow(data_x[0], 3);
    A[1][1] = pow(data_x[0], 2);
    A[1][2] = data_x[0]; A[1][3] = 1.0;

    int row = 2;
    int col = 0;
    double x, x_cube, x_sq;
    for (int i = 1; i < N - 1; i ++) {
        x = data_x[i];
        x_cube = pow(x, 3);
        x_sq = pow(x, 2);

        A[row][col] = x_cube; A[row][col + 1] = x_sq; A[row][col + 2] = x; A[row][col + 3] = 1.0;
        A[row + 1][col + 4] = x_cube; A[row + 1][col + 5] = x_sq; A[row + 1][col + 6] = x; A[row + 1][col + 7] = 1.0;

        A[row + 2][col] = 3.0 * x_sq; A[row + 2][col + 1] = 2.0 * x; A[row + 2][col + 2] = 1.0;
        A[row + 2][col + 4] = -3.0 * x_sq; A[row + 2][col + 5] = -2.0 * x; A[row + 2][col + 6] = -1.0;
        A[row + 3][col] = 6.0 * x; A[row + 3][col + 1] = 2.0;
        A[row + 3][col + 4] = -6.0 * x; A[row + 3][col + 5] = -2.0;

        b[row] = data_y[i]; b[row + 1] = data_y[i]; b[row + 2] = 0.0; b[row + 3] = 0.0;

        row += 4;
        col += 4;
    }

    b[m - 2] = 0.0; b[m - 1] = data_y[N - 1];
    A[m - 2][m - 4] = 6.0 * data_x[N - 1]; A[m - 2][m - 3] = 2.0;
    A[m - 1][m - 4] = pow(data_x[N - 1], 3);
    A[m - 1][m - 3] = pow(data_x[N - 1], 2);
    A[m - 1][m - 2] = data_x[N - 1]; A[m - 1][m - 1] = 1.0;

    std::cout << A << std::endl;

    std::vector<double> param;
    param = gauss_solve(A, b);

    std::vector<double> y_test;
    int index = -1; // start_index
    double interp_out;
    for (auto v: x_test) {

        if (index < N - 1) {
            index = find_index(index, v);
            if (index == -1) {
                // extrapolation
                interp_out = spline_val(0, v, param);
            }
            else {
                interp_out = spline_val(index, v, param);
            }
        }
        else {
            //extrapolation
            interp_out = spline_val(N - 2, v, param);
        }
        y_test.push_back(interp_out);
    }
    return y_test;


}