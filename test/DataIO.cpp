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
        std::cout << x << y << std::endl;
        data_x.push_back(x);
        data_y.push_back(y);
    }
    std::cout << data_x.size() << std::endl;
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
        if (i < N_gen - 1) {
            generate_data << x[i] << " " << y[i] << "\n";
        }
        else {
            generate_data << x[i] << " " << y[i];
        }

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

std::vector<double> DataIO::gen_x_test(int N_test) const {
    double min = data_x[0];
    double max = data_x[0];
    std::vector<double> x_test(N_test);
    int N = data_x.size();
    for (int i = 0; i < N; i++){
        if (min > data_x[i]){
            min = data_x[i];
        }
        if(max < data_x[i]){
            max = data_x[i];
        }
    }
    double step = (max - min) / (double)(N_test - 1);
    for (int i = 0; i < N_test; i++){
        x_test[i] = min + i * step;
    }
    return x_test;
}