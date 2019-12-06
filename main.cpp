#include <iostream>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include "Matrix.h"
#include <vector>
#include <map>
#include <cstdio>
#include "Fitter.h"
#include "Inputdata.h"
#include <cassert>
#include "gnuplot_i.hpp"

int main(int argc, char* argv[]) {
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
    int N_gen;
    double x_min;
    double x_max;
    double x_step;
    int choice;
    std::cout << "Please select your test function (1/2):" << std::endl;
    std::cout << "1. cos(3 * Pi * x)" << std::endl;
    std::cout << "2. 1 / (1 + x ^ 2)" << std::endl;
    std::cin >> choice;
    assert(choice == 1 || choice == 2);
    std::cout << "Please input the number of data points to generate, which is must be an integer larger than 1:";
    std::cin >> N_gen;
    assert(N_gen >= 2);
    std::cout << "Please input the range of x:" << std::endl;
    std::cout << "The minimum of x is:";
    std::cin >> x_min;
    std::cout << "The maximum of x is:";
    std::cin >> x_max;
    x_step = (x_max - x_min) / (N_gen - 1);
    std::vector<double> x_gen(N_gen);
    std::vector<double> y_gen(N_gen);
    for (int i = 0; i < N_gen; i++) {
        x_gen[i] = x_min + (double) i * x_step;
        if(choice == 1){
            y_gen[i] = cos(3 * x_gen[i] * M_PI);
        }
        else{
            y_gen[i] = 1 / (1 + x_gen[i] * x_gen[i]);
        }

    }
    std::ofstream generate_data("data.dat");
    assert(generate_data.is_open());
    for (int i = 0 ; i < N_gen; i++){
        generate_data << x_gen[i] << " " << y_gen[i] << "\n";
    }
    generate_data.close();
    std::cout << "Data is generated." << std::endl;

    // brief test
    int N_test;
    std::cout << "Please input the number of test data points, which is must be an integer larger than 1:";
    std::cin >> N_test;
    assert(N_test >= 2);
    std::vector<double> X;
    std::vector<double> Y;
    std::vector<double> X_test(N_test);
    Inputdata train;
    X = train.get_data_x();
    Y = train.get_data_y();
    X_test = train.test_cgl(N_test);



    Fitter approx(X, Y);
    std::vector<double> Y_test;
    std::vector<double> w;
    int choice_m;
    std::cout << "Please select the approximation method (1/2/3/4):" << std::endl;
    std::cout << "1. Polynomial\n2. Interpolation\n3. Spline\n4. DCT\n";
    std::cin >> choice_m;
    if (choice_m == 1){
        int degree;
        double lambda_;
        std::cout << "Degree: ";
        std::cin >> degree;
        std::cout << "lambda: ";
        std::cin >> lambda_;
        w = approx.polyfit(degree, lambda_);
        for (int i_w = 0; i_w < degree; i_w++){
            std::cout << w[i_w] << " ";
        }
        std::cout << std::endl;
        Y_test = approx.polyval(w, X_test);
    }
    if (choice_m == 2){
        Y_test = approx.interp1(X_test);
    }
    if (choice_m == 3){
        Y_test = approx.spline(X_test);
    }
    if (choice_m == 4){
        w = approx.dct_fit();
        std::cout << w[0] << w[1] << w[2] << std::endl;
        Y_test = approx.dct_val(w, X_test);
    }


    for (int i = 0; i < N_test; i ++) {
        std::cout << Y_test[i] << ' ';
    }

    std::ofstream write_output("Output.dat");
    assert(write_output.is_open());
    for (int i = 0; i < N_test; i++){
        write_output << X_test[i] << " " << Y_test[i] << "\n";
    }
    write_output.close();

    Gnuplot gp = Gnuplot("lines");
    gp.set_style("points");
    gp.plot_xy(X_test, Y_test, "Approximation");

    return 0;

}