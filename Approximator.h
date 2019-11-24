//
// Created by Yuxuan Long on 24/11/19.
//

#ifndef PROJECT_APPROXIMATOR_H
#define PROJECT_APPROXIMATOR_H

#include <iostream>
#include <vector>
#include "Matrix.h"

class Approximator {
private:
//    std::string method;
    std::vector<double> data_x;
    std::vector<double> data_y;
    int N;
public:
    Approximator(std::vector<double>& x, std::vector<double>& y);
    std::vector<double> polyfit(int degree) const;
    std::vector<double> polyval(std::vector<double>& x_test, std::vector<double>& w) const;

    int find_index(int start_index, double v) const;

    std::vector<double> interp1(std::vector<double>& x_test) const;
    std::vector<double> spline(std::vector<double>& x_test) const;
};


#endif //PROJECT_APPROXIMATOR_H
