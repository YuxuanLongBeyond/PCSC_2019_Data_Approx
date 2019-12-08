//
// Created by Yuxuan Long on 23/11/19.
//

#ifndef PROJECT_MATRIX_H
#define PROJECT_MATRIX_H

#include <iostream>
#include <vector>

/**
 * This class builds mainly for matrix operations, which contain:
 * 1. Construction of matrix based on 2D array in C++.
 * 2. Basic matrix operations, like assignment, addition, subtraction and multiplication.
 * 3. Auxiliary matrix operations, like transpose, diagonal element addition and row exchange.
 * 4. Advanced matrix operations, like Gaussian elimination for solving linear system and least squares.
 */
class Matrix {
private:
    /**
     * Number of rows
     */
    int size0;

    /**
     * Number of columns
     */
    int size1;

    /**
     * 2D array for storing the elements in the matrix
     */
    double** A;

    /**
     * Dynamically allocated memory for creating a 2D array (used in constructor)
     * @return an empty 2D array with memory reserved
     */
    double** define();

    /**
     * Erase the allocated memory for the matrix (used in destructor)
     */
    void del();
public:

    /**
     * Construct a 2 by 2 square matrix of zeros if no size provided
     */
    Matrix();

    /**
     * Construct a matrix of zeros given the matrix size
     * @param s1 number of rows of the matrix
     * @param s2 number of columns of the matrix
     */
    Matrix(int s1, int s2);

    /**
     * Construct a matrix by assigning another matrix (with same size) to it
     * @param B a matrix that assigned to the new matrix
     */
    Matrix(const Matrix& B);

    /**
     * Destruct the memory of the matrix if matrix goes out of the block
     */
    ~Matrix();

    /**
     * Set all entries of the matrix to zeros (usually used in constructor)
     */
    void make_zero();

    /**
     * Indexing operator
     * @param i index of the row of the matrix
     * @return i th row of the matrix, in the form of 1D array
     */
    double* operator[](int i) const;

    /**
     * Assignment operator
     * @param B a matrix
     * @return the matrix itself by assigning B to it
     */
    Matrix& operator=(const Matrix& B);

    /**
     * Addition operator
     * @param B a matrix
     * @return the addition of the matrix and B
     */
    Matrix operator+(const Matrix& B) const;

    /**
     * Subtraction operator
     * @param B a matrix
     * @return the subtraction of B from the matrix
     */
    Matrix operator-(const Matrix &B) const;

    /**
     * Opposite sign operator
     * @return -1 times the matrix
     */
    Matrix operator-() const;

    /**
     * Matrix multiplication operator (for matrix times matrix)
     * @param B a matrix
     * @return the matrix times B
     */
    Matrix operator*(const Matrix& B) const;

    /**
     * Matrix multiplication operator
     * @param x a vector
     * @return the matrix times the input vector x
     */
    std::vector<double> operator*(const std::vector<double> &x) const;

    /**
     * Matrix multiplication operator
     * @param s a scalar
     * @return the matrix scaled by s
     */
    Matrix operator*(double s) const;

    /**
     * Add constant to the diagonal
     * @param s a scalar
     * @return the matrix which its diagonal is incremented by s
     */
    Matrix diagonal_add(double s) const;

    /**
     * Transpose operator
     * @return the transpose of the matrix
     */
    Matrix transpose() const;

    /**
     * A friend function for multiplication operator
     * @param s a scalar
     * @param B the input matrix
     * @return B scaled by s
     */
    friend Matrix operator*(double s, const Matrix& B);

    /**
     * A friend function for stream
     * @param output the output stream, e.g. std::cout
     * @param B the matrix
     * @return printing of matrix B
     */
    friend std::ostream& operator<<(std::ostream& output, const Matrix& B);

    /**
     * Row exchange (currently used in Gaussian elimination)
     * @param i index for one row in the matrix
     * @param j index for the another row in the matrix
     */

    /**
     * Judge if the input scalar is zero or not (this function is heavily used in Gaussian elimination)
     * @param a the input scalar
     * @param threshold a small positive number for the threshold
     * @return if the absolute value of the input is smaller than the threshold, 1 is returned; otherwise, 0.
     */
    static int is_zero(double a, double threshold = 1e-15);

    /**
     * Exchange the i th row and the j th row
     * @param i row index i for the matrix
     * @param j row index j for the matrix
     */
    void row_exchange(int i, int j);

    /**
     * Gauss elimination and back substitution for solving the linear system: Ax = b, including pivoting
     * @param A a matrix
     * @param b a vector
     * @return the solution x (a vector) for Ax = b
     */
    friend std::vector<double> gauss_solve(const Matrix& A, const std::vector<double> &b);

    /**
     * Solve least squares Ax = b, where A is non-square. In fact, we solve the normal equation
     * @param A a non-square matrix
     * @param b a vector
     * @param s a non-negative scalar to be added on the diagonal of A.T * A
     * @return the solution of the normal equation, i.e. x = (A.T * A + sI)^(-1) A.T * b
     */
    friend std::vector<double> least_squares(const Matrix& A, const std::vector<double> &b, double s);
};


#endif //PROJECT_MATRIX_H
