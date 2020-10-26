#include <iostream>
#include <ostream>
#include "Matrix.h"
using namespace std;

Helper::Helper(const size_t l_length, int* matrix) : length(l_length), line(matrix)
	{}
	int& Helper::operator[] (const size_t j)
	{
		if (j >= length || j < 0)
		{
			throw out_of_range("");
		}
		return line[j];
	}
Matrix::Matrix( size_t m=0, size_t n=0) : rows(m), cols(n)
	{
		if (rows != 0 && cols != 0)
		{
			matrix = new int* [rows];
			for (size_t i = 0; i < rows; i++)
			{
				matrix[i] = new int[cols];
			}
			mem_allocated = true;
		}
		else
		{
			matrix = nullptr;
			mem_allocated = false;
		}
			
	}
Matrix::Matrix(const Matrix& m) : rows(m.rows), cols(m.cols)
	{
		if (rows != 0 && cols != 0)
		{
			this->matrix = new int* [rows];
			for (size_t i = 0; i < rows; i++)
			{
				this->matrix[i] = new int[cols];
			}
			for (size_t i = 0; i < rows; i++)
			{
				for (size_t j = 0; j < rows; j++)
				{
					this->matrix[i][j] = m.matrix[i][j];
				}
			}
			mem_allocated = true;
		}
		else
		{
			matrix = nullptr;
			mem_allocated = false;
		}
	}
	const size_t& Matrix::getRows()
	{
		return rows;
	}
	const size_t& Matrix::getColumns()
	{
		return cols;
	}
	Helper Matrix::operator[] (size_t i)
	{
		if (i >= rows || i<0)
		{				
			throw out_of_range("");
		}
		Helper line(cols,matrix[i]);
		return line;	
	}
	const Matrix operator+( const Matrix& m1, const Matrix& m2)
	{
		if (m1.rows == m2.rows && m1.cols == m2.cols)
		{
			Matrix m3(m1.rows, m1.cols);
			for (size_t i = 0; i < m3.rows; i++)
			{
				for (size_t j = 0; j < m3.cols; j++)
				{
					m3[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
				}
			}
			return Matrix(m3); 
		}
		else
			throw "wrong sizes";
	}
	ostream& operator<<(ostream &out, const Matrix& m)
	{
		for (size_t i = 0; i < m.rows; i++)
		{
			for (size_t j = 0; j < m.cols; j++)
			{
				out << m.matrix[i][j] << " ";
			}
			out << endl;
		}
		return out;
	}
	void Matrix::operator= (const Matrix& m)//если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
	{
		if (m.rows == this->rows && m.cols == this->cols)
		{
			for (size_t i = 0; i < m.rows; i++)
			{
				for (size_t j = 0; j < m.cols; j++)
				{
					this->matrix[i][j] = m.matrix[i][j];
				}
			}
		}
		else if (this->rows == 0 && this->cols == 0)
		{
			this->matrix = m.matrix;
			this->rows = m.rows;
			this->cols = m.cols;
		}
		else
			throw "wrong sizes";
	}

	void Matrix::operator+= (const Matrix& m)//если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
	{
		if (m.rows == this->rows && m.cols == this->cols)
		{
			for (size_t i = 0; i < m.rows; i++)
			{
				for (size_t j = 0; j < m.cols; j++)
				{
					this->matrix[i][j] += m.matrix[i][j];
				}
			}
		}
		else
			throw "wrong sizes";
			
	}
	void Matrix::operator*= (const int& k)//если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
	{
		for (size_t i = 0; i < this->rows; i++)
		{
			for (size_t j = 0; j < this->cols; j++)
			{
				this->matrix[i][j] *= k;
			}
		}
		
	}
	bool operator== (const Matrix& m1, const Matrix& m2)//если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
	{
		if (m1.rows == m2.rows && m1.cols == m2.cols)
		{
			for (size_t i = 0; i < m1.rows; i++)
			{
				for (size_t j = 0; j < m1.cols; j++)
				{
					if (m1.matrix[i][j] != m2.matrix[i][j])
					{
						return false;
					}
				}
			}
			return true;
		}
		else
			throw "wrong sizes";
	}

	bool operator> (const Matrix& m1, const Matrix& m2)//если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
	{
		if (m1.rows == m2.rows && m1.cols == m2.cols)
		{
			for (size_t i = 0; i < m1.rows; i++)
			{
				for (size_t j = 0; j < m1.cols; j++)
				{
					if (m1.matrix[i][j] < m2.matrix[i][j])
					{
						return false;
					}
				}
			}
			return true;
		}
		else
			throw "wrong sizes";
	}
	bool operator<(const Matrix& m1, const Matrix& m2)//если матрица задана, то переприсвоит значения, если только обьявлен пустой обьект, то скопирует m3
	{
		if (m1.rows == m2.rows && m1.cols == m2.cols)
		{
			for (size_t i = 0; i < m1.rows; i++)
			{
				for (size_t j = 0; j < m1.cols; j++)
				{
					if (m1.matrix[i][j] > m2.matrix[i][j])
					{
						return false;
					}
				}
			}
			return true;
		}
		else
			throw "wrong sizes";
	}
