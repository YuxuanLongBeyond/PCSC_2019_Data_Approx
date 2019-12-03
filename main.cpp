#include <iostream>
#include <cmath>
#include <stdexcept>
#include "Matrix.h"
#include <vector>
#include "Fitter.h"
#include "Inputdata.h"
#include <fstream>
#include <cassert>

int main() {
    Matrix A(3, 3);
    A[0][0] = 0;
    A[0][1] = 1;
    A[0][2] = 2;
    A[1][0] = 5;
    A[1][1] = 0;
    A[1][2] = 3;
    A[2][0] = 2;
    A[2][1] = 3;
    A[2][2] = 1;

    std::vector<double> b(3);
    b[0] = 3; b[1] = 8; b[2] = 6;
    std::vector<double> x = gauss_solve(A, b);


//    std::cout << x[0] << std::endl;
//    std::cout << x[1] << std::endl;
//    std::cout << x[2] << std::endl;
//
//    std::cout << b[0] << std::endl;
//    std::cout << b[1] << std::endl;
//    std::cout << b[2] << std::endl;


    Matrix P1;
    P1[0][0] = 2;
    Matrix P2;
    P2[0][0] = 2;
    Matrix P = P1 * P2;
//    std::cout << P << std::endl;
    double s = 2.0;

//    std::cout << A.transpose().diagonal_add(s) << std::endl;

    Matrix B(3, 2);
    B[0][0] = 0;
    B[0][1] = 1;
    B[1][0] = 5;
    B[1][1] = 0;
    B[2][0] = 2;
    B[2][1] = 3;
//    std::cout << B;
//
    std::vector<double> y = least_squares(B, b, 0.0);
//    std::cout << y[0] << std::endl;
//    std::cout << y[1] << std::endl;

    //generate data
    int N_gen = 20;
    double x_gen[N_gen];
    double y_gen[N_gen];
    for (int i = 0; i < N_gen; i++) {
        x_gen[i] = (double) i;
        y_gen[i] = cos(3 * x_gen[i] * M_PI / N_gen);
    }
    std::ofstream generate_data("data.dat");
    assert(generate_data.is_open());
    for (int i = 0 ; i < N_gen; i++){
        generate_data << x_gen[i] << " " << y_gen[i] << "\n";
    }
    generate_data.close();

    // brief test
    int N_test = 1000;
    std::vector<double> X;
    std::vector<double> Y;
    std::vector<double> X_test(N_test);
//    for (int i = 0; i < N; i ++) {
//        X[i] = (double)i * 0.1;
//        Y[i] = sin(X[i] * M_PI);
//        X_test[i + 1] = X[i] + 0.05;
//    }
//    X_test[0] = -0.05;
    Inputdata train;
    X = train.get_data_x();
    Y = train.get_data_y();
    X_test = train.test_cgl(N_test);



    Fitter approx(X, Y);
    std::vector<double> Y_test;
    std::vector<double> w;
//    w = approx.polyfit(2, 0.001);
//    std::cout << w[0] << w[1] << w[2] << std::endl;
    Y_test = approx.polyval(w, X_test);
//    Y_test = approx.interp1(X_test);
    Y_test = approx.spline(X_test);

//    w = approx.dct_fit();
//    std::cout << w[0] << w[1] << w[2] << std::endl;
//    Y_test = approx.dct_val(w, X_test);
//    for (int i = 0; i < N + 1; i ++) {
//        std::cout << Y_test[i] << ' ';
//    }

    for (int i = 0; i < N_test; i ++) {
        std::cout << Y_test[i] << ' ';
    }

    std::ofstream write_output("Output.dat");
    assert(write_output.is_open());
    for (int i = 0; i < N_test; i++){
        write_output << X_test[i] << " " << Y_test[i] << "\n";
    }
    write_output.close();

    return 0;

}