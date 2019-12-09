#include <iostream>
#include <fstream>
#include "config/Config.h"
#include <cmath>
#include <stdexcept>
#include "src/Matrix.h"
#include <vector>
#include <map>
#include <cstdio>
#include "src/Fitter.h"
#include "test/DataIO.h"
#include "test/Test.h"
#include "test/gnuplot_i.hpp"


int main(int argc, char* argv[]) {

    // Define variables (see the comments in configuration file, like config.txt)
    int use_file;
    int choice_f;
    int choice_node;
    int N_gen;
    int N_test;
    double x_min;
    double x_max;
    double x_test_min;
    double x_test_max;
    std::string approx_method;
    std::string file_name;
    std::string out_file;
    std::string matlab_file;
    int poly_degree;
    double poly_lambda;

    std::string config_file_name;
    if (argc > 1) {
        config_file_name = argv[1];
    }
    else {
        config_file_name = "../config/config.txt"; // default name for configuration file
    }
    Config configSettings(config_file_name);

    use_file = configSettings.Read("use_file", 0);
    choice_f = configSettings.Read("function_type", 1);
    N_gen = configSettings.Read("num_input_points", 20);
    N_test = configSettings.Read("num_test_points", 1000);
    x_min = configSettings.Read("x_input_min", 0);
    x_max = configSettings.Read("x_input_max", 1);
    x_test_min = configSettings.Read("x_test_min", 0);
    x_test_max = configSettings.Read("x_test_max", 1);
    choice_node = configSettings.Read("node_type", 1);
    approx_method = configSettings.Read("approximation_method", approx_method);
    file_name = configSettings.Read("use_file_name", file_name);
    out_file = configSettings.Read("out_file_name", out_file);
    poly_degree = configSettings.Read("polynomial_degree", 2);
    poly_lambda = configSettings.Read("polynomial_lambda", 0);
    matlab_file = configSettings.Read("MATLAB_generated_file_name", matlab_file);


    std::vector<double> X;
    std::vector<double> Y;
    std::vector<double> X_test(N_test);
    std::vector<double> Y_test(N_test);
    std::vector<double> X_matlab(N_test);
    std::vector<double> Y_matlab(N_test);
    DataIO data_handler;
    Test test;

    // if use_file, then read the data file to extract the data; otherwise, use the generated data
    if (use_file) {
        data_handler.data_reader(file_name);
        X = data_handler.get_data_x();
        Y = data_handler.get_data_y();
    }
    else {
        // generate sample points (x, y) for data fitting
        X = data_handler.gen_x(choice_node, N_gen, x_min, x_max);
        Y = data_handler.gen_y(choice_f, N_gen, X);

        // write the sample points
        DataIO::data_writer(file_name, X, Y);
    }

    // generate test data
    X_test = data_handler.gen_x_test(N_test, x_test_min, x_test_max);

    // load the data into Fitter
    Fitter approx(X, Y);

    // interpolate the test data
    Y_test = test.approx_test(approx_method, approx, X_test, poly_degree, poly_lambda);
    DataIO::print_vector(Y_test);

    // write the test data with interpolated values
    DataIO::data_writer(out_file, X_test, Y_test);
    Test::print_error_function(choice_f, X_test, Y_test, N_test);
    //Gnuplot g1 = Gnuplot("approx", "origin", "points", "X", "Y", X_test, Y_test, X, Y);

    DataIO matlab_data;
    matlab_data.data_reader(matlab_file);
    Y_matlab = matlab_data.get_data_y();
    Test::print_mse(Y_test, Y_matlab);

    return 0;
}