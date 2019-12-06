//
// Created by yiting on 25.11.19.
//

#include "Inputdata.h"
#include <cmath>
#include <cassert>

<<<<<<< HEAD
Inputdata::Inputdata() = default;

void Inputdata::Readtestdata() {
=======
Inputdata::Inputdata() {
//    std::ifstream infile("/home/yiting/Documents/yiting/PCSC_2019_Data_Approx-master/data.dat");
>>>>>>> b729361cdd0487f98a2fb378a165525e442e7a18
    std::ifstream infile("data.dat");
    assert(infile.is_open());
    double x[10000]; //assume there are no more than 10000 data points;
    double y[10000];
    int i = 0;
    while(!infile.eof()){
        infile >> x[i] >> y[i];
        data_x.push_back(x[i]);
        data_y.push_back(y[i]);
        i++;
    }
    infile.close();
}

<<<<<<< HEAD
std::vector<double> Inputdata::gen_uni(int N_gen, double x_min, double x_max) const{
    std::vector<double> x_gen;
    assert(N_gen > 1);
    assert(x_max >= x_min);
    double step = (x_max - x_min) / (N_gen - 1);
    double temp[N_gen];
    for (int i = 0; i < N_gen; i++){
        temp[i] =  x_min + i * step;
        x_gen.push_back(temp[i]);
    }
    return x_gen;
}

std::vector<double> Inputdata::gen_cgl(int N_gen, double x_min, double x_max) const{
    std::vector<double> x_gen;
    assert(N_gen > 1);
    assert(x_max >= x_min);
    double temp[N_gen];
    for (int i = 0; i < N_gen; i++){
        temp[i] = (x_min + x_max) / 2 - (x_max - x_min) / 2 * cos(M_PI * i / (N_gen- 1));
        x_gen.push_back(temp[i]);
    }
    return x_gen;
}

std::vector<double> Inputdata::get_data_x() const{
    return data_x;
}

std::vector<double> Inputdata::get_data_y() const{
    return data_y;
}

std::vector<double> Inputdata::gen_x_test(int N_test) const {
    double min = data_x[0];
    double max = data_x[0];
    std::vector<double> x_test;
    double test[N_test];
    int N = data_x.size();
    for (int i = 0; i < N_test; i++){
        if (min > data_x[i]){
=======
std::vector<double> Inputdata::test_uni(int test_N) const{
    double min = data_x[0];
    double max = data_x[0];
    std::vector<double> x_test;
    double test[test_N];
    int N = data_x.size();
    for (int i = 0; i < N; i++){
        if(min > data_x[i]){
            min = data_x[i];
        }
        if(max < data_x[i]){
            max = data_x[i];
        }
    }
    double step = (max - min) / (test_N - 1);
    for (int i = 0; i < test_N; i++){
        test[i] = min + i * step;
        x_test.push_back(test[i]);
    }
    return x_test;
}

std::vector<double> Inputdata::test_cgl(int test_N) const{
    double min = data_x[0];
    double max = data_x[0];
    std::vector<double> x_test;
    double test[test_N];
    int N = data_x.size();
    for (int i = 0; i < N; i++){
        if(min > data_x[i]){
>>>>>>> b729361cdd0487f98a2fb378a165525e442e7a18
            min = data_x[i];
        }
        if(max < data_x[i]){
            max = data_x[i];
        }
    }
<<<<<<< HEAD
    double step = (max - min) / (N_test - 1);
    for (int i = 0; i < N_test; i++){
        test[i] = min + i * step;
        x_test.push_back(test[i]);
    }
    return x_test;
=======
    for (int i = 0; i < test_N; i++){
        test[i] = (min + max) / 2 - (max - min) / 2 * cos(M_PI * i / (test_N - 1));
        x_test.push_back(test[i]);
    }
    return x_test;
}

std::vector<double> Inputdata::get_data_x() const{
    return data_x;
}

std::vector<double> Inputdata::get_data_y() const{
    return data_y;
>>>>>>> b729361cdd0487f98a2fb378a165525e442e7a18
}