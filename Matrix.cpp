//
// Created by Yuxuan Long on 23/11/19.
//


#include "Matrix.h"
#include <stdexcept>
#include <cmath>

Matrix::Matrix() {
    size0 = 2;
    size1 = 2;
    A = Matrix::define();
    Matrix::make_zero();
}

Matrix::Matrix(int s1, int s2) {
    size0 = s1;
    size1 = s2;
    A = Matrix::define();
    Matrix::make_zero();
}

Matrix::Matrix(const Matrix &B) {
    size0 = B.size0;
    size1 = B.size1;
    A = Matrix::define();
    for (int i = 0; i < size0; i ++) {
        for (int j = 0; j < size1; j ++) {
            A[i][j] = B.A[i][j];
        }
    }
}

Matrix::~Matrix() {
    Matrix::del();
}

double** Matrix::define() {
    double** array;
    array = new double* [size0];
    for (int i = 0; i < size0; i ++) {
        array[i] = new double [size1];
    }
    return array;
}

void Matrix::del() {
    for (int i = 0; i < size0; i ++) {
        delete[] A[i];
    }
    delete[] A;
}

void Matrix::make_zero() {
    for (int i = 0; i < size0; i ++ ) {
        for (int j = 0; j < size1; j ++) {
            A[i][j] = 0.0;
        }
    }
}

double* Matrix::operator[](int i) const
{
    return A[i];
}

Matrix& Matrix::operator=(const Matrix& B) {
    if ((size0 != B.size0) || (size1 != B.size1)) {
        throw std::invalid_argument( "Inconsistent matrix size!" );
    }
    for (int i = 0; i < size0; i ++) {
        for (int j = 0; j < size1; j ++) {
            A[i][j] = B.A[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &B) const
{
    if ((size0 != B.size0) || (size1 != B.size1)) {
        throw std::invalid_argument( "Inconsistent matrix size!" );
    }
    Matrix C(size0, size1);
    for (int i = 0; i < size0; i ++) {
        for (int j = 0; j < size1; j ++) {
            C.A[i][j] = A[i][j] + B.A[i][j];
        }
    }
    return C;
}

Matrix Matrix::operator-(const Matrix &B) const
{
    if ((size0 != B.size0) || (size1 != B.size1)) {
        throw std::invalid_argument( "Inconsistent matrix size!" );
    }
    Matrix C(size0, size1);
    for (int i = 0; i < size0; i ++) {
        for (int j = 0; j < size1; j ++) {
            C.A[i][j] = A[i][j] - B.A[i][j];
        }
    }
    return C;
}

Matrix Matrix::operator-() const
{
    Matrix C(size0, size1);
    for (int i = 0; i < size0; i ++) {
        for (int j = 0; j < size1; j ++) {
            C.A[i][j] = - A[i][j];
        }
    }
    return C;
}

Matrix Matrix::operator*(const Matrix &B) const {
    if (size1 != B.size0) {
        throw std::invalid_argument( "Inconsistent matrix size!" );
    }


    Matrix C(size0, B.size1);
    for (int i = 0; i < size0; i ++) {
        for (int j = 0; j < B.size1; j++) {
            for (int k = 0; k < size1; k++) {
                C.A[i][j] += A[i][k] * B.A[k][j];
            }

        }
    }
    return C;
}

Matrix Matrix::operator*(double s) const {
    Matrix C(size0, size1);
    for (int i = 0; i < size0; i ++) {
        for (int j = 0; j < size1; j++) {
            C[i][j] = A[i][j] * s;
        }
    }
    return C;
}

Matrix operator*(double s, const Matrix& B) {
    Matrix C(B.size0, B.size1);
    for (int i = 0; i < B.size0; i ++) {
        for (int j = 0; j < B.size1; j++) {
            C.A[i][j] = s * B.A[i][j];
        }
    }
    return C;
}

std::vector<double> Matrix::operator*(const std::vector<double> &x) const {
    if (x.size() != size1) {
        throw std::invalid_argument( "Inconsistent matrix size!" );
    }


    std::vector<double> out(size0);
    for (int i = 0; i < size0; i ++) {
        out[i] = 0;
        for (int j = 0; j < size1; j ++) {
            out[i] += A[i][j] * x[j];
        }
    }
    return out;
}


int is_zero(double a, double threshold = 1e-10) {
    if (abs(a) < threshold) {
        return 1;
    }
    else {
        return 0;
    }
}

void Matrix::row_exchange(int i, int j) {
    for (int k = 0; k < size1; k ++) {
        double tem = A[i][k];
        A[i][k] = A[j][k];
        A[j][k] = tem;
    }
}

Matrix Matrix::diagonal_add(double s) const {
    if (size0 != size1) {
        throw std::invalid_argument( "Not a square matrix!" );
    }


    Matrix B = *this;
    for (int i = 0; i < size0; i ++) {
        B[i][i] += s;
    }
    return B;
}

std::vector<double> gauss_solve(const Matrix& A, const std::vector<double>& b) {
    // solve Ax = b
    if ((A.size0 != A.size1) || (b.size() != A.size0)) {
        throw std::invalid_argument( "Inconsistent matrix size!" );
    }
    Matrix B = A;
    int n = A.size0;
    std::vector<double> x(n);
    for (int i = 0; i < n; i ++) {
        x[i] = b[i];
    }

    // ensure the first row has pivot
    int flag = 1;
    int row = 0;
    if (is_zero(B[0][0])) {
        for (int i = 1; i < n; i ++) {
            if (! is_zero(B[i][0])) {
                flag = 0;
                row = i;
                break;
            }
        }
        if (flag) {
            throw std::invalid_argument( "Singular Matrix" );
        }
        B.row_exchange(0, row);
        double tem = x[0];
        x[0] = x[row];
        x[row] = tem;
    }

    // convert to upper triangular matrix
    double mul;
    for (int i = 1; i < n; i ++) {
        for (int j = 0; j < i; j ++) {

            if (is_zero(B[j][j])) {
                if (! is_zero(B[i][j])) {
                    // pivoting
                    // exchange row i and row j
                    B.row_exchange(i, j);
                    double tem = x[i];
                    x[i] = x[j];
                    x[j] = tem;
                }
            }
            else {
                if (! is_zero(B[i][j])) {
                    // row elimination
                    mul = B[i][j] / B[j][j];
                    B[i][j] = 0;
                    for (int k = (j + 1); k < n; k ++) {
                        B[i][k] -= mul * B[j][k];
                    }
                    x[i] -= mul * x[j];
                }
            }
        }
    }
    double d = 1; // store determinant
    for (int i = 0; i < n; i ++) {
        d *= B[i][i];
    }
    if (is_zero(d)) {
        throw std::invalid_argument( "Singular Matrix" );
    }
    // back substitution
    for (int i = n - 1; i >= 0; i --) {
        for (int j = n - 1; j > i; j --) {
            x[i] -= x[j] * B[i][j];
        }
        x[i] /= B[i][i];
    }

    return x;
}

Matrix Matrix::transpose() const {
    Matrix B(size1, size0);
    for (int i = 0; i < size1; i ++) {
        for (int j = 0; j < size0; j ++) {
            B[i][j] = A[j][i];
        }
    }
    return B;
}

std::ostream& operator<<(std::ostream& output, const Matrix& B) {
    output << '[';
    for (int i = 0; i < B.size0; i ++) {
        for (int j = 0; j < B.size1; j ++) {
            output << B.A[i][j] << " ";
        }
        if (i != (B.size0 - 1)) {
            output << '\n';
        }
    }
    output << ']';
    return output;
}

std::vector<double> least_squares(const Matrix& A, const std::vector<double> &b, double s) {
    if (b.size() != A.size0) {
        throw std::invalid_argument( "Inconsistent matrix size!" );
    }
    Matrix A_T = A.transpose();
    std::vector<double> x(A.size1);
    x = gauss_solve((A_T * A).diagonal_add(s), A_T * b);
    return x;
}