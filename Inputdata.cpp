//
// Created by yiting on 25.11.19.
//

#include "Inputdata.h"
#include <cmath>
#include <cassert>

Inputdata::Inputdata() {
//    std::ifstream infile("/home/yiting/Documents/yiting/PCSC_2019_Data_Approx-master/data.dat");
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
            min = data_x[i];
        }
        if(max < data_x[i]){
            max = data_x[i];
        }
    }
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
}