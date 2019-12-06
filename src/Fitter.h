//
// Created by Yuxuan Long on 24/11/19.
//

#ifndef PROJECT_FITTER_H
#define PROJECT_FITTER_H


#include <iostream>
#include <vector>
#include "Matrix.h"

class Fitter {
private:
//    std::string method;
    std::vector<double> data_x;
    std::vector<double> data_y;
    int N;
public:
    /**
     *
     * @param x rehrth
     * @param y erh
     */
    Fitter(std::vector<double>& x, std::vector<double>& y);
    /**
     *
     * @param degree
     * @param lambda
     * @return
     */
    std::vector<double> polyfit(int degree, double lambda) const;
    std::vector<double> polyval(std::vector<double>& w, std::vector<double>& x_test) const;

    int find_index(int start_index, double v) const;

    std::vector<double> interp1(std::vector<double>& x_test) const;
    double spline_val(int index, double x, std::vector<double> param) const;
    std::vector<double> spline(std::vector<double>& x_test) const;

    std::vector<double> dct_fit() const;
    std::vector<double> dct_val(std::vector<double>& w, std::vector<double>& x_test) const;
};

#endif //PROJECT_FITTER_H
