//
// Created by yiting on 25.11.19.
//

#ifndef PROJECT_DATAIO_H
#define PROJECT_DATAIO_H

#include <iostream>
#include <fstream>
#include <vector>

class DataIO {
private:
    std::vector<double> data_x;
    std::vector<double> data_y;
public:
    DataIO();
    void test_data_reader(std::string &file_name);
    static void print_vector(std::vector<double>& x);
    static void data_writer(std::string &file_name, std::vector<double> x, std::vector<double> y);
    std::vector<double> gen_uni(int N_gen, double x_min, double x_max) const;
    std::vector<double> gen_cgl(int N_gen, double x_min, double x_max) const;
    std::vector<double> get_data_x() const;
    std::vector<double> get_data_y() const;
    std::vector<double> gen_x_test(int N_test) const;

};


#endif //PROJECT_DATAIO_H
