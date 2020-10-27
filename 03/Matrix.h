#ifndef TOKENPARSER_H
#define TOKENPARSER_H
#include <iostream>
using namespace std;

class Helper {
private:
    const size_t length;
    int* line;

public:
    Helper(const size_t l_length, int* matrix);
    int& operator[](size_t j);
    const int& operator[](const size_t j) const;
};

class Matrix {
private:
    size_t rows;
    size_t cols;
    int** matrix;
    friend Helper;

public:
    bool mem_allocated;
    Matrix();
    Matrix(const size_t m, const size_t n);
    Matrix(const Matrix& m);
    ~Matrix();
    const size_t getRows() const;
    const size_t getColumns() const;
    Helper operator[](size_t i);
    const Helper operator[](const size_t i) const;
    friend Matrix operator+(const Matrix& m1, const Matrix& m2);
    friend ostream& operator<<(ostream& out, const Matrix& m);
    Matrix& operator=(const Matrix& m); //если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
    Matrix& operator+=(const Matrix& m); //если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
    Matrix& operator*=(const int& k); //если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
    bool friend operator==(const Matrix& m1, const Matrix& m2); //если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
    bool friend operator>(const Matrix& m1, const Matrix& m2); //если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
    bool friend operator<(const Matrix& m1, const Matrix& m2); //если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
    bool friend operator!=(const Matrix& m1, const Matrix& m2);
};
#endif
