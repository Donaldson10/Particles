#include "Matrices.h"

namespace Matrices
{
    ///Construct a matrix of the specified size.
    ///Initialize each element to 0.
    Matrix::Matrix(int _rows, int _cols) {
        cols = _cols;
        rows = _rows;
        a.resize(rows, vector<double>(cols));
    }
    ///Add each corresponding element.
    ///usage:  c = a + b;
    Matrix operator+(const Matrix& a, const Matrix& b) {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
            throw runtime_error("Error: dimensions must agree");
        }
        Matrix result(a.getRows(), a.getCols());
        // Add corresponding elements
        for (int i = 0; i < a.getRows(); ++i) {
            for (int j = 0; j < a.getCols(); ++j) {
                result(i, j) = a(i, j) + b(i, j);
            }
        }

        return result;
    }


    ///Matrix multiply.  See description.
    ///usage:  c = a * b;
    Matrix operator*(const Matrix& a, const Matrix& b) {
        // Check if the number of columns in 'a' is equal to the number of rows in 'b'
        if (a.getCols() != b.getRows()) {
            throw std::runtime_error("Error: dimensions must agree");
        }

        // Create a new matrix to store the result
        Matrix result(a.getRows(), b.getCols());

        // Perform matrix multiplication
        for (int i = 0; i < a.getRows(); ++i) {
            for (int k = 0; k < b.getCols(); ++k) {
                double sum = 0.0;
                for (int j = 0; j < a.getCols(); ++j) {
                    sum += a(i, j) * b(j, k);
                }
                result(i, k) = sum;
            }
        }

        return result;
    }

    ///Matrix comparison.  See description.
    ///usage:  a == b
    bool operator==(const Matrix& a, const Matrix& b) {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
            return false;
        }
        double countervar1, countervar2;

        for (int i = 0; i < a.getRows(); ++i) {
            for (int j = 0; j < a.getCols(); ++j) {
                countervar1 += a(i, j);
                countervar2 += b(i, j);
            }
        }
        if (abs(countervar1 - countervar2) < 0.001 * (a.getRows() + a.getCols())) {
            return true;
        }
        else {
            return false;
        }
    }

    ///Matrix comparison.  See description.
    ///usage:  a != b
    bool operator!=(const Matrix& a, const Matrix& b) {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
            return true;
        }
        double countervar1, countervar2;

        for (int i = 0; i < a.getRows(); ++i) {
            for (int j = 0; j < a.getCols(); ++j) {
                countervar1 += a(i, j);
                countervar2 += b(i, j);
            }
        }
        if (abs(countervar1 - countervar2) < 0.001 * (a.getRows() + a.getCols())) {
            return false;
        }
        else {
            return true;
        }
    }

    ///Output matrix.
    ///Separate columns by ' ' and rows by '\n'
    ostream& operator<<(ostream& os, const Matrix& a) {
        for (int i = 0; i < a.getRows(); ++i) {
            for (int j = 0; j < a.getCols(); ++j) {
                os << std::setw(8) << a(i, j); // Adjust the width as needed
                if (j < a.getCols() - 1) {
                    os << ' '; // Separate columns by space
                }
            }
            os << '\n'; // Separate rows by newline
        }
        return os;
    }
    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2) {
        (*this)(0, 0) = cos(theta);
        (*this)(0, 1) = -sin(theta);
        (*this)(1, 0) = sin(theta);
        (*this)(1, 1) = cos(theta);
    }
    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2){
        // Assign elements according to scaling matrix formula
        (*this)(0, 0) = scale;
        (*this)(1, 1) = scale;
    }
    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {
        // Assign elements according to translation matrix formula
        for (int j = 0; j < nCols; ++j)
        {
            (*this)(0, j) = xShift;
            (*this)(1, j) = yShift;
        }
    }
};
