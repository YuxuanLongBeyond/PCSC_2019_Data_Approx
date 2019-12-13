#include <iostream>
#include "config/Config.h"
#include <stdexcept>
#include <vector>
#include "src/Fitter.h"
#include "experiment/DataIO.h"
#include "experiment/Experiment_Test.h"
#include "plot/gnuplot_i.hpp"


int main(int argc, char* argv[]) {

    std::string config_file_name;
    if (argc > 1) {
        std::cout << "Trying to use the configuration file provided ..." << std::endl;
        config_file_name = argv[1];
    }
    else {
        config_file_name = "config.txt"; // default name for configuration file
        std::cout << "No argument provided, the default configuration file " << config_file_name << " is to be used" << std::endl;
    }
    config_file_name = "../../core/config/" + config_file_name;
    std::cout << "Loading parameters from " << config_file_name << std::endl;
    Config configSettings(config_file_name);

    std::string approx_method = "polynomial";
    std::string file_name = "data.dat";
    std::string out_file = "Output.dat";

    // Define variables from configuration file (see the descriptions in example config.txt)
    int use_file = configSettings.Read("use_file", 0);
    int use_gnuplot = configSettings.Read("use_gnuplot",0);
    int choice_f = configSettings.Read("function_type", 2);
    int N_gen = configSettings.Read("num_input_points", 41);
    int N_test = configSettings.Read("num_test_points", 1001);
    int choice_node = configSettings.Read("node_type", 1);
    int poly_degree = configSettings.Read("polynomial_degree", 20);
    double x_min = configSettings.Read("x_input_min", -10);
    double x_max = configSettings.Read("x_input_max", 10);
    double x_test_min = configSettings.Read("x_test_min", -10);
    double x_test_max = configSettings.Read("x_test_max", 10);
    double poly_lambda = configSettings.Read("polynomial_lambda", 0);
    approx_method = configSettings.Read("approximation_method", approx_method);
    file_name = "../../core/data/" + configSettings.Read("use_file_name", file_name);
    out_file = "../../core/data/" + configSettings.Read("out_file_name", out_file);
    std::vector<double> X; std::vector<double> Y; // input data
    std::vector<double> X_test(N_test); std::vector<double> Y_test(N_test); // test data
    std::vector<double> X_mat(N_test); std::vector<double> Y_mat(N_test); // Matlab data
    DataIO data_handler;
    Experiment_Test test;

    // if use_file, then read the data file to extract the data; otherwise, use the generated data
    if (use_file) {
        std::cout << "Reading the file provided by the user" << std::endl;
        data_handler.data_reader(file_name);
        X = data_handler.get_data_x();
        Y = data_handler.get_data_y();
    }
    else {
        std::cout << "Generating the sample points X, Y for data fitting" << std::endl;
        X = data_handler.gen_x(choice_node, N_gen, x_min, x_max);
        Y = data_handler.gen_y(choice_f, N_gen, X);

        std::cout << "Writing the generated sample points X, Y into " << file_name << std::endl;
        DataIO::data_writer(file_name, X, Y);
    }
    Fitter approx(X, Y);

    std::cout << "Generating test data X_test" << std::endl;
    X_test = data_handler.gen_x_test(N_test, x_test_min, x_test_max);
    std::cout << "Data approximation using " << approx_method << std::endl;
    Y_test = test.approx_test(approx_method, approx, X_test, poly_degree, poly_lambda);

    std::cout << "Writing X_test with the approximated data Y_test into " << out_file << std::endl;
    DataIO::data_writer(out_file, X_test, Y_test);

    Experiment_Test::compute_error(choice_f, X_test, Y_test, N_test);

    // The following GNU plot is not related to the debug mode
    if (use_gnuplot){
        std::cout << "Using GNUPLOT to plot the data" << std::endl;
        Gnuplot g1 = Gnuplot("approx", "origin", "points", "X", "Y", X_test, Y_test, X, Y);
    }

    return 0;
}