//
// Created by yiting on 25.11.19.
//

#ifndef PROJECT_INPUTDATA_H
#define PROJECT_INPUTDATA_H

#include <iostream>
#include <fstream>
#include <vector>

class Inputdata {
private:
    std::vector<double> data_x;
    std::vector<double> data_y;
public:
    Inputdata();
    void Readtestdata();
//    Inputdata(int N);
    std::vector<double> gen_uni(int N_gen, double x_min, double x_max) const;
    std::vector<double> gen_cgl(int N_gen, double x_min, double x_max) const;
    std::vector<double> get_data_x() const;
    std::vector<double> get_data_y() const;
    std::vector<double> gen_x_test(int N_test) const;

};


#endif //PROJECT_INPUTDATA_H
