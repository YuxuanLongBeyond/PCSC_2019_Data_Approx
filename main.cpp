#include <iostream>
#include <cmath>
#include <stdexcept>
#include "Matrix.h"
#include <vector>

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


    std::cout << x[0] << std::endl;
    std::cout << x[1] << std::endl;
    std::cout << x[2] << std::endl;

    std::cout << b[0] << std::endl;
    std::cout << b[1] << std::endl;
    std::cout << b[2] << std::endl;


    Matrix P1;
    P1[0][0] = 2;
    Matrix P2;
    P2[0][0] = 2;
    Matrix P = P1 * P2;
    std::cout << P << std::endl;
    double s = 2.0;

    std::cout << A.transpose().diagonal_add(s) << std::endl;

    Matrix B(3, 2);
    B[0][0] = 0;
    B[0][1] = 1;
    B[1][0] = 5;
    B[1][1] = 0;
    B[2][0] = 2;
    B[2][1] = 3;
    std::cout << B;
//
    std::vector<double> y = least_squares(B, b);
    std::cout << y[0] << std::endl;
    std::cout << y[1] << std::endl;

    return 0;

}