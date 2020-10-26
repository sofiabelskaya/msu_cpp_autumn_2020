#ifndef TOKENPARSER_H
#define TOKENPARSER_H
#include <iostream>
using namespace std;

class Helper
{
private:
	const size_t length;
	int* line;

public:
	Helper(const size_t l_length, int* matrix);
	int& operator[] (const size_t j);
};

class Matrix
{
private:
	size_t rows;
	size_t cols;
	int** matrix;	
	friend Helper;
public:
	bool mem_allocated;
	Matrix( size_t m, size_t n);
	Matrix(const Matrix& m);
	const size_t& getRows();
	const size_t& getColumns();
	Helper operator[] (size_t i);
	friend const Matrix operator+( const Matrix& m1, const Matrix& m2);
	friend ostream& operator<<(ostream &out, const Matrix& m);
	void operator= (const Matrix& m);//если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
	void operator+= (const Matrix& m);//если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
	void operator*= (const int& k);//если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
	bool friend operator== (const Matrix& m1, const Matrix& m2);//если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
	bool friend operator> (const Matrix& m1, const Matrix& m2);//если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
	bool friend operator<(const Matrix& m1, const Matrix& m2);//если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
};
#endif