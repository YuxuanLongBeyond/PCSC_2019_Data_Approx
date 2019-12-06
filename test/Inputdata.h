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
//    Inputdata(int N);
    std::vector<double> test_uni(int test_N) const;
    std::vector<double> test_cgl(int test_N) const;
    std::vector<double> get_data_x() const;
    std::vector<double> get_data_y() const;

};


#endif //PROJECT_INPUTDATA_H
