//
// Created by yiting on 07.12.19.
//

#ifndef PROJECT_TEST_H
#define PROJECT_TEST_H

#include <iostream>
#include <fstream>
#include <vector>

class Test {
private:
public:
    Test();
    static void print_error_function(int choice_f, std::vector<double> x, std::vector<double> y, int N_test);
};


#endif //PROJECT_TEST_H
