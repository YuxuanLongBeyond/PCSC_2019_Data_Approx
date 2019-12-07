#include <iostream>
#include <fstream>
#include "test/Config.h"
#include <cmath>
#include <stdexcept>
#include "src/Matrix.h"
#include <vector>
#include <map>
#include <cstdio>
#include "src/Fitter.h"
#include "test/DataIO.h"
#include <cassert>
#include "test/gnuplot_i.hpp"


int main(int argc, char* argv[]) {

    int choice_f;
    int choice_node;
    int N_gen;
    int N_test;
    double x_min;
    double x_max;
    double x_test_min;
    double x_test_max;
    std::string approx_method;
    int poly_degree;
    double poly_lambda;
    const char ConfigFile[]= "config.txt";// read configuration file
    Config configSettings(ConfigFile);
    choice_f = configSettings.Read("function_type", 1);
    N_gen = configSettings.Read("num_input_points", 20);
    N_test = configSettings.Read("num_test_points", 1000);
    x_min = configSettings.Read("x_input_min", 0);
    x_max = configSettings.Read("x_input_max", 1);
    x_test_min = configSettings.Read("x_test_min", 0);
    x_test_max = configSettings.Read("x_test_max", 1);
    choice_node = configSettings.Read("node_type", 1);
    approx_method = configSettings.Read("approximation_method", approx_method);
    poly_degree = configSettings.Read("polynomial_degree", 2);
    poly_lambda = configSettings.Read("polynomial_lambda", 0.001);

    assert(choice_f == 1 || choice_f == 2);
    assert(N_gen >= 2);
    assert(choice_node == 1||choice_node == 2);
    assert(N_test >= 2);

    std::vector<double> x_gen(N_gen);
    std::vector<double> y_gen(N_gen);

    DataIO data_handler;
    if (choice_node == 1){
        x_gen = data_handler.gen_uni(N_gen, x_min, x_max);
    }
    else{
        x_gen = data_handler.gen_cgl(N_gen, x_min, x_max);
    }

    for (int i = 0; i < N_gen; i++) {
        if(choice_f == 1){
            y_gen[i] = cos(3.0 * x_gen[i] * M_PI);
        }
        else{
            y_gen[i] = 1.0 / (1.0 + x_gen[i] * x_gen[i]);
        }
    }

    std::string file_name = "data.dat";

    DataIO::data_writer(file_name, x_gen, y_gen);

    std::vector<double> X;
    std::vector<double> Y;
    std::vector<double> X_test(N_test);
    DataIO test;

    test.test_data_reader(file_name);
    X = test.get_data_x();
    Y = test.get_data_y();
    std::cout << std::endl;
    X_test = test.gen_x_test(N_test, x_test_min, x_test_max);

    Fitter approx(X, Y);
    std::vector<double> Y_test;
    std::vector<double> w;
    if (approx_method == "polynomial"){
        w = approx.polyfit(poly_degree, poly_lambda);
        DataIO::print_vector(w);
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
        DataIO::print_vector(w);
        Y_test = approx.dct_val(w, X_test);
    }

    DataIO::print_vector(Y_test);


    std::string out_file = "Output.dat";
    DataIO::data_writer(out_file, X_test, Y_test);
    if(choice_f == 1){
        DataIO::print_error_function_one(X_test, Y_test, N_test);
    }
    else{
        DataIO::print_error_function_two(X_test, Y_test, N_test);
    }

    Gnuplot g1 = Gnuplot("approx", "origin", "points", "X", "Y", X_test, Y_test, x_gen, y_gen);

    return 0;

}