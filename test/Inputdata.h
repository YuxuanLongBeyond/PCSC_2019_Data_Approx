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
<<<<<<< HEAD
    void Readtestdata();
//    Inputdata(int N);
    std::vector<double> gen_uni(int N_gen, double x_min, double x_max) const;
    std::vector<double> gen_cgl(int N_gen, double x_min, double x_max) const;
    std::vector<double> get_data_x() const;
    std::vector<double> get_data_y() const;
    std::vector<double> gen_x_test(int N_test) const;
=======
//    Inputdata(int N);
    std::vector<double> test_uni(int test_N) const;
    std::vector<double> test_cgl(int test_N) const;
    std::vector<double> get_data_x() const;
    std::vector<double> get_data_y() const;
>>>>>>> b729361cdd0487f98a2fb378a165525e442e7a18

};


#endif //PROJECT_INPUTDATA_H
