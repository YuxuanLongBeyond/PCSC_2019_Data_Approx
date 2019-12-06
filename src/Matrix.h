//
// Created by Yuxuan Long on 23/11/19.
//

#ifndef PROJECT_MATRIX_H
#define PROJECT_MATRIX_H

#include <iostream>
#include <vector>

class Matrix {
private:
    int size0;
    int size1;
    double** A;
    double** define();
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
     * Set all entries of the matrix to zeros
     */
    void make_zero();

    /**
     *
     * @param i index of the row of the matrix
     * @return i th row of the matrix, in the form of 1D array
     */
    double* operator[](int i) const;


    Matrix& operator=(const Matrix& B);

    Matrix operator+(const Matrix& B) const;

    Matrix operator-(const Matrix &B) const;

    Matrix operator-() const;

    Matrix operator*(const Matrix& B) const;

    std::vector<double> operator*(const std::vector<double> &x) const;

    Matrix operator*(double s) const;

    Matrix diagonal_add(double s) const;

    Matrix transpose() const;

    friend Matrix operator*(double s, const Matrix& B);

    friend std::ostream& operator<<(std::ostream& output, const Matrix& B);

    void row_exchange(int i, int j);

    friend std::vector<double> gauss_solve(const Matrix& A, const std::vector<double> &b);

    /**
     *
     * @param A
     * @param b
     * @param s
     * @return
     */
    friend std::vector<double> least_squares(const Matrix& A, const std::vector<double> &b, double s);
};


#endif //PROJECT_MATRIX_H
