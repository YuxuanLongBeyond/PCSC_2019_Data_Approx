#include <iostream>
#include <fstream>
#include "Config.h"
#include <cmath>
#include <stdexcept>
#include "Matrix.h"
#include <vector>
#include <map>
#include <cstdio>
#include "Fitter.h"
#include "Inputdata.h"
#include <cassert>


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
    Matrix P1;
    P1[0][0] = 2;
    Matrix P2;
    P2[0][0] = 2;
    Matrix P = P1 * P2;
    double s = 2.0;
    Matrix B(3, 2);
    B[0][0] = 0;
    B[0][1] = 1;
    B[1][0] = 5;
    B[1][1] = 0;
    B[2][0] = 2;
    B[2][1] = 3;
    std::vector<double> y = least_squares(B, b, 0.0);


    int choice_f;
    int choice_node;
    int N_gen;
    int N_test;
    double x_min;
    double x_max;
    std::string approx_method;
    const char ConfigFile[]= "config.txt";// read configuration file
    Config configSettings(ConfigFile);
    choice_f = configSettings.Read("function_type", 1);
    N_gen = configSettings.Read("num_input_points", 20);
    N_test = configSettings.Read("num_test_points", 1000);
    x_min = configSettings.Read("x_input_min", 0);
    x_max = configSettings.Read("x_input_max", 1);
    choice_node = configSettings.Read("node_type", 1);
    approx_method = configSettings.Read("approximation_method", approx_method);



    assert(choice_f == 1 || choice_f == 2);
    assert(N_gen >= 2);
    assert(choice_node == 1||choice_node == 2);
    assert(N_test >= 2);

    std::vector<double> x_gen(N_gen);
    std::vector<double> y_gen(N_gen);

    Inputdata fromfunction;
    if (choice_node == 1){
        x_gen = fromfunction.gen_uni(N_gen, x_min, x_max);
    }
    else{
        x_gen = fromfunction.gen_cgl(N_gen, x_min, x_max);
    }

    for (int i = 0; i < N_gen; i++) {
        if(choice_f == 1){
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


    std::vector<double> X;
    std::vector<double> Y;
    std::vector<double> X_test(N_test);
    Inputdata test;
    test.Readtestdata();
    X = test.get_data_x();
    Y = test.get_data_y();
    X_test = test.gen_x_test(N_test);

    Fitter approx(X, Y);
    std::vector<double> Y_test;
    std::vector<double> w;
    if (approx_method == "polynomial"){
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
    if (approx_method == "interpolation"){
        Y_test = approx.interp1(X_test);
    }
    if (approx_method == "spline"){
        Y_test = approx.spline(X_test);
    }
    if (approx_method == "dct"){
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

//    Gnuplot gp = Gnuplot("lines");
//    gp.set_style("points");
//    gp.plot_xy(X_test, Y_test, "Approximation");

    return 0;

}