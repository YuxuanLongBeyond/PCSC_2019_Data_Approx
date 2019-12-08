//
// Created by yiting on 25.11.19.
//

#include <stdexcept>
#include <cmath>
#include "DataIO.h"

DataIO::DataIO() = default;

void DataIO::data_reader(std::string &file_name) {
    std::ifstream infile(file_name);
    if (!infile.is_open()){
        throw std::invalid_argument("Can't open file!");
    }
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
    std::cout << '[';
    for (auto v: x) {
        std::cout << v << ' ';
    }
    std::cout << ']' << std::endl;
}

void DataIO::data_writer(std::string &file_name, std::vector<double> x, std::vector<double> y) {
    if (x.size() != y.size()){
        throw std::invalid_argument("Incompatible data size!");
    }
    int N_gen = x.size();
    std::ofstream generate_data(file_name);
    if (!generate_data.is_open()){
        throw std::invalid_argument("Can't open file!");
    }
    for (int i = 0 ; i < N_gen; i++){
        if (i < N_gen - 1) {
            generate_data << x[i] << " " << y[i] << "\n";
        }
        else {
            generate_data << x[i] << " " << y[i]; // avoid to generate an additional empty line in the end
        }

    }
    generate_data.close();
    std::cout << "Data is generated." << std::endl;
}


std::vector<double> DataIO::gen_x(int choice_node, int N_gen, double x_min, double x_max) const{
    if (choice_node != 1 && choice_node != 2){
        throw std::invalid_argument("Invalid input choice for node type!");
    }
    if (N_gen < 2) {
        throw std::invalid_argument("Too little input samples!");
    }
    if (x_max < x_min){
        throw std::invalid_argument("The maximum value should not smaller than the minimum value!");
    }
    double step = (x_max - x_min) / (double)(N_gen - 1);
    std::vector<double> x_gen(N_gen);
    for (int i = 0; i < N_gen; i++){
        if (choice_node == 1){// the uniform distribution nodes
            x_gen[i] = x_min + i * step;
        }
        else{// the Chebychev-Gauss-Lobatto nodes
            x_gen[i] = (x_min + x_max) / 2 - (x_max - x_min) / 2 * cos(M_PI * (double)i / (double)(N_gen- 1));
        }
    }
    return x_gen;
}

std::vector<double> DataIO::gen_y(int choice_f, int N_gen, std::vector<double> x_gen) const {
    if (choice_f != 1 && choice_f != 2 && choice_f != 3){
        throw std::invalid_argument("Invalid input choice for function type!");
    }
    std::vector<double> y_gen(N_gen);
    for (int i = 0; i < N_gen; i++) {
        // three different types of function
        if(choice_f == 1){
            y_gen[i] = cos(3.0 * x_gen[i] * M_PI);
        }
        if(choice_f == 2){
            y_gen[i] = 1.0 / (1.0 + x_gen[i] * x_gen[i]);
        }
        else{
            y_gen[i] = pow(x_gen[i], 3) - 2 * x_gen[i] + 3;
        }
    }
    return y_gen;
}

std::vector<double> DataIO::get_data_x() const{
    return data_x;
}

std::vector<double> DataIO::get_data_y() const{
    return data_y;
}

std::vector<double> DataIO::gen_x_test(int N_test, double x_test_min, double x_test_max) const {
    if (N_test < 2) {
        throw std::invalid_argument("Too little input test samples!");
    }
    std::vector<double> x_test(N_test);
    double step = (x_test_max - x_test_min) / (double)(N_test - 1); // calculate the step size
    for (int i = 0; i < N_test; i++){
        x_test[i] = x_test_min + i * step;
    }
    return x_test;
}
