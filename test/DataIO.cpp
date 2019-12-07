//
// Created by yiting on 25.11.19.
//

#include "DataIO.h"
#include <cmath>
#include <cassert>

DataIO::DataIO() = default;

void DataIO::test_data_reader(std::string &file_name) {
    std::ifstream infile(file_name);
    assert(infile.is_open());
    double x;
    double y;
    while(!infile.eof()){
        infile >> x >> y;
        data_x.push_back(x);
        data_y.push_back(y);
    }
    infile.close();
}

void DataIO::print_vector(std::vector<double>& x) {
    for (auto v: x) {
        std::cout << v << ' ';
    }
}

void DataIO::data_writer(std::string &file_name, std::vector<double> x, std::vector<double> y) {
    assert(x.size() == y.size());
    int N_gen = x.size();
    std::ofstream generate_data(file_name);
    assert(generate_data.is_open());
    for (int i = 0 ; i < N_gen; i++){
        generate_data << x[i] << " " << y[i] << "\n";
    }
    generate_data.close();
    std::cout << "Data is generated." << std::endl;
}

std::vector<double> DataIO::gen_uni(int N_gen, double x_min, double x_max) const{
    assert(N_gen > 1);
    assert(x_max > x_min);
    double step = (x_max - x_min) / (double)(N_gen - 1);
    std::vector<double> x_gen(N_gen);
    for (int i = 0; i < N_gen; i++){
        x_gen[i] = x_min + i * step;
    }
    return x_gen;
}

std::vector<double> DataIO::gen_cgl(int N_gen, double x_min, double x_max) const{
    assert(N_gen > 1);
    assert(x_max > x_min);
    double temp;
    std::vector<double> x_gen(N_gen);
    for (int i = 0; i < N_gen; i++){
        temp = (x_min + x_max) / 2 - (x_max - x_min) / 2 * cos(M_PI * (double)i / (double)(N_gen- 1));
        x_gen[i] = temp;
    }
    return x_gen;
}

std::vector<double> DataIO::get_data_x() const{
    return data_x;
}

std::vector<double> DataIO::get_data_y() const{
    return data_y;
}


std::vector<double> DataIO::gen_x_test(int N_test, double x_test_min, double x_test_max) const {
    std::vector<double> x_test(N_test);
    double step = (x_test_max - x_test_min) / (double)(N_test - 1);
    for (int i = 0; i < N_test; i++){
        x_test[i] = x_test_min + i * step;
    }
    return x_test;
}

void DataIO::print_error_function_one(std::vector<double> x_test, std::vector<double> y_test, int N_test) {
    double e = 0.0;
    std::vector<double> y_real(N_test);
    for (int i = 0; i < N_test; i++){
        y_real[i] = cos(3.0 * x_test[i] * M_PI);
        if (e < fabs(y_real[i] - y_test[i])){
            e = fabs(y_real[i] - y_test[i]);
        }
    }
    std::cout << e << std::endl;
}

void DataIO::print_error_function_two(std::vector<double> x_test, std::vector<double> y_test, int N_test) {

    double e = 0.0;
    std::vector<double> y_real(N_test);
    for (int i = 0; i < N_test; i++){
        y_real[i] = 1.0 / (1.0 + x_test[i] * x_test[i]);
        if (e < fabs(y_real[i] - y_test[i])){
            e = fabs(y_real[i] - y_test[i]);
        }
    }
    std::cout << e << std::endl;
}