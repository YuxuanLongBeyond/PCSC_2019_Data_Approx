//
// Created by yiting on 12/11/19.
//
#include <iostream>
#include <vector>
#include "../test/DataIO.h"
#include "../test/Test.h"
#include <gtest/gtest.h>

TEST(DebugTest, PolyTest){
    DataIO data_test;
    DataIO data_mat;
    Test test;
    std::vector<double> Y_test;
    std::vector<double> Y_mat;
    std::string out_file = "../data/Output.dat";
    std::string mat_file = "../data/poly_Matlab.dat";
    data_test.data_reader(out_file);
    data_mat.data_reader(mat_file);
    Y_test = data_test.get_data_y();
    Y_mat = data_mat.get_data_y();


    ASSERT_NEAR(test.compute_mse(Y_test, Y_mat), 0, 0.001);

}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}