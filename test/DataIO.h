//
// Created by yiting on 25.11.19.
//

#ifndef PROJECT_DATAIO_H
#define PROJECT_DATAIO_H

#include <iostream>
#include <fstream>
#include <vector>

/**
 * This class is mainly used for data's input and output, which contains:
 * 1. read 2D data from a data file
 * 2. print a given vector for debugging
 * 3. write 2D data into a data file
 * 4. generate original data from given parameters
 * 5. generate approximated test data from given parameters
 *
 */

class DataIO {
private:
    /**
     * Input 1D vector X containing all scalar samples x_i
     */
    std::vector<double> data_x;

    /**
     * Input 1D vector Y containing all scalar samples y_i which corresponds to x_i
     */
    std::vector<double> data_y;
public:
    /**
     * Constructor with default setting
     */
    DataIO();

    /**
     * Read the 2D input data X and Y from a given data file
     * The data file here has two columns:
     * The first column is X, the second column is Y
     * X and Y are 1D vector having the same size
     * @param file_name file name of the data file we want to read
     */
    void data_reader(std::string &file_name);

    /**
     * Print an 1D vector
     * @param x 1D vector X containing all scalar samples x_i
     */
    static void print_vector(std::vector<double>& x);

    /**
     * Write the 2D data X and Y into a data file
     * The data file here has two columns:
     * The first column is X, the second column is Y
     * X and Y are 1D vector having the same size
     * X and Y are separated by a blank space in a row
     * @param file_name file name of the data file we want to save the data
     * @param x 1D vector X containing all scalar samples x_i
     * @param y 1D vector Y containing all scalar samples y_i which corresponds to x_i
     */
    static void data_writer(std::string &file_name, std::vector<double> x, std::vector<double> y);

    /**
     * Generate original data X from a certain type of choice of nodes and relative parameters
     * @param choice_node choice for type of nodes, which is 1 or 2:
     * 1 is for uniform distribution, 2 is for Chebyshev-Gauss-Lobatto nodes
     * @param N_gen number of data points to generate
     * @param x_min minimum value of data points
     * @param x_max maximum value of data points
     * @return 1D vector X containing all scalar samples x_i
     */
    std::vector<double> gen_x(int choice_node, int N_gen, double x_min, double x_max) const;

    /**
     * Generate original data Y from a certain type of function and relative parameters which corresponds to data X
     * @param choice_f choice for type of function used for generating data, which is 1, 2 or 3:
     * 1 is y = cos(3 * Pi * x), 2 is Runge function: y = 1 / (1 + x ^ 2), 3 is polynomial function: y = x ^ 3 - 2 * x + 3
     * @param N_gen number of data points to generate
     * @param x_gen 1D vector X already generated, which contains all scalar samples x_i
     * @return 1D vector Y containing all scalar samples y_i, which corresponds to x_i
     */
    std::vector<double> gen_y(int choice_f, int N_gen, std::vector<double> x_gen) const;

    /**
     * Get the data X
     * @return 1D vector X
     */
    std::vector<double> get_data_x() const;

    /**
     * Get the data Y
     * @return 1D vector Y
     */
    std::vector<double> get_data_y() const;

    /**
     * Generate test data X from relative parameters
     * Note: the test data points are uniformly distributed
     * @param N_test number of test data points
     * @param x_test_min minimum value of test data points
     * @param x_test_max maximum value of test data points
     * @return 1D vector X containing all scalar samples for test
     */
    std::vector<double> gen_x_test(int N_test, double x_test_min, double x_test_max) const;

};


#endif //PROJECT_DATAIO_H
