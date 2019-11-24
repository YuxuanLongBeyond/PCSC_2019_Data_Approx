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
    Matrix();
    Matrix(int s1, int s2);
    Matrix(const Matrix& B);
    ~Matrix();

    void make_zero();
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
    friend std::vector<double> least_squares(const Matrix& A, const std::vector<double> &b);
};


#endif //PROJECT_MATRIX_H
