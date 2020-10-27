#include <iostream>
#include <ostream>
#include "Matrix.h"
using namespace std;

Helper::Helper(const size_t l_length, int* matrix)
    : length(l_length)
    , line(matrix)
{
}

int& Helper::operator[](size_t j)
{
    if (j >= length || j < 0) {
        throw out_of_range("");
    }
    return line[j];
}
const int& Helper::operator[](const size_t j) const
{
    if (j >= length || j < 0) {
        throw out_of_range("");
    }
    return line[j];
}

Matrix::Matrix()
    : rows(0)
    , cols(0)
{
    matrix = nullptr;
    mem_allocated = false;
}
Matrix::Matrix(const size_t m, const size_t n)
    : rows(m)
    , cols(n)
{
    if (rows != 0 && cols != 0) {
        matrix = new int*[rows];
        for (size_t i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
        }
        mem_allocated = true;
    }
    else {
        matrix = nullptr;
        mem_allocated = false;
    }
}
Matrix::Matrix(const Matrix& m)
    : rows(m.rows)
    , cols(m.cols)
{
    if (rows != 0 && cols != 0) {
        this->matrix = new int*[rows];
        for (size_t i = 0; i < rows; i++) {
            this->matrix[i] = new int[cols];
        }
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                this->matrix[i][j] = m.matrix[i][j];
            }
        }
        mem_allocated = true;
    }
    else {
        matrix = nullptr;
        mem_allocated = false;
    }
}
Matrix::~Matrix()
{
    if (mem_allocated) {
        for (size_t i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        mem_allocated = false;
    }
}
const size_t Matrix::getRows() const
{
    return rows;
}
const size_t Matrix::getColumns() const
{
    return cols;
}
Helper Matrix::operator[](size_t i)
{
    if (i >= rows || i < 0) {
        throw out_of_range("");
    }
    Helper line(cols, matrix[i]);
    return line;
}
const Helper Matrix::operator[](const size_t i) const
{
    if (i >= rows || i < 0) {
        throw out_of_range("");
    }
    const Helper line(cols, matrix[i]);
    return line;
}
const Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    if (m1.rows == m2.rows && m1.cols == m2.cols) {
        Matrix m3(m1.rows, m1.cols);
        for (size_t i = 0; i < m3.rows; i++) {
            for (size_t j = 0; j < m3.cols; j++) {
                m3[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
            }
        }
        return Matrix(m3);
    }
    else
        throw "wrong sizes";
}
ostream& operator<<(ostream& out, const Matrix& m)
{
    for (size_t i = 0; i < m.rows; i++) {
        for (size_t j = 0; j < m.cols; j++) {
            out << m.matrix[i][j] << " ";
        }
        out << endl;
    }
    return out;
}
Matrix& Matrix::operator=(const Matrix& m) //если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то аллоцирует память и скопирует m3
{
    if (m.rows == this->rows && m.cols == this->cols) {
        for (size_t i = 0; i < m.rows; i++) {
            for (size_t j = 0; j < m.cols; j++) {
                this->matrix[i][j] = m.matrix[i][j];
            }
        }
    }
    else if (!mem_allocated) {
        this->rows = m.rows;
        this->cols = m.cols;
        this->matrix = new int*[rows];
        for (size_t i = 0; i < this->rows; i++) {
            this->matrix[i] = new int[cols];
        }
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                this->matrix[i][j] = m.matrix[i][j];
            }
        }
        mem_allocated = true;
    }
    else
        throw "wrong sizes";
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
    if (m.rows == this->rows && m.cols == this->cols) {
        for (size_t i = 0; i < m.rows; i++) {
            for (size_t j = 0; j < m.cols; j++) {
                this->matrix[i][j] += m.matrix[i][j];
            }
        }
    }
    else
        throw "wrong sizes";
    return *this;
}
Matrix& Matrix::operator*=(const int& k) //если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
{
    for (size_t i = 0; i < this->rows; i++) {
        for (size_t j = 0; j < this->cols; j++) {
            this->matrix[i][j] *= k;
        }
    }
    return *this;
}
const bool operator==(const Matrix& m1, const Matrix& m2) //если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
{
    if (m1.rows == m2.rows && m1.cols == m2.cols) {
        for (size_t i = 0; i < m1.rows; i++) {
            for (size_t j = 0; j < m1.cols; j++) {
                if (m1.matrix[i][j] != m2.matrix[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    else
        throw "wrong sizes";
}

const bool operator>(const Matrix& m1, const Matrix& m2) //если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
{
    if (m1.rows == m2.rows && m1.cols == m2.cols) {
        for (size_t i = 0; i < m1.rows; i++) {
            for (size_t j = 0; j < m1.cols; j++) {
                if (m1.matrix[i][j] < m2.matrix[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    else
        throw "wrong sizes";
}
const bool operator<(const Matrix& m1, const Matrix& m2) //если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
{
    if (m1.rows == m2.rows && m1.cols == m2.cols) {
        for (size_t i = 0; i < m1.rows; i++) {
            for (size_t j = 0; j < m1.cols; j++) {
                if (m1.matrix[i][j] > m2.matrix[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    else
        throw "wrong sizes";
}
const bool operator!=(const Matrix& m1, const Matrix& m2) //если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
{
    if (m1.rows == m2.rows && m1.cols == m2.cols) {
        for (size_t i = 0; i < m1.rows; i++) {
            for (size_t j = 0; j < m1.cols; j++) {
                if (m1.matrix[i][j] == m2.matrix[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    else
        throw "wrong sizes";
}
