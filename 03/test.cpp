#include <iostream>
#include "Matrix.h"
using namespace std;

bool test1()//проверим что действительно создалась матрица нужного размера и память аллоцировалась
{
	Matrix m(3, 2);
	if (m.getRows() != 3 || m.getColumns() != 2 or m.mem_allocated!= true)
	{
		return false;
	}
	else
		return true;
}

bool test2()//проверим что конструктор копирования верно создает размер матрицы и аллоцирует память
{
	Matrix m(2, 2);
	Matrix m2(m);
	if (m.getRows() != m2.getRows() || m.getColumns() != m2.getColumns() or m2.mem_allocated != true)
	{
		return false;
	}
	else
		return true;
}

bool test3()//проверим доступ по квадратным скобкам и работу конструктора копирования
{
	Matrix m(2, 2);
	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 3;
	m[1][1] = 4;
	Matrix m2(m);
	for (size_t i = 0; i < m2.getRows(); i++)
	{
		for (size_t j = 0; j < m2.getRows(); j++)
		{
			if (m[i][j] != m2[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool test4()//проверим работу конструктора по умолчанию и оператора присвоения
{
	Matrix m(2, 2);
	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 3;
	m[1][1] = 4;
	Matrix m2 = m;
	for (size_t i = 0; i < m2.getRows(); i++)
	{
		for (size_t j = 0; j < m2.getRows(); j++)
		{
			if (m[i][j] != m2[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool test5()//проверим работу  оператора присвоения между уже существующими матрицами
{
	Matrix m(2, 2);
	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 3;
	m[1][1] = 4;
	Matrix m2(2, 2);
	m2 = m;
	for (size_t i = 0; i < m2.getRows(); i++)
	{
		for (size_t j = 0; j < m2.getRows(); j++)
		{
			if (m[i][j] != m2[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

bool test6()//проверим работу *=
{
	Matrix m(2, 2);
	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 3;
	m[1][1] = 4;
	Matrix m2 = m;
	m *= 3;
	for (size_t i = 0; i < m.getRows(); i++)
	{
		for (size_t j = 0; j < m.getRows(); j++)
		{
			if (m[i][j] != m2[i][j]*3)
			{
				return false;
			}
		}
	}
	return true;
}


bool test7()//проверим работу >
{
	Matrix m(2, 2);
	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 3;
	m[1][1] = 4;
	Matrix m2 = m;
	m *= 3;
	if (m > m2)
	{
		return true;
	}
	else 
	{
		return false;
	}	
}
bool test8()//проверим работу <
{
	Matrix m(2, 2);
	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 3;
	m[1][1] = 4;
	Matrix m2 = m;
	m *= 3;
	if (m < m2)
	{
		return false;
	}
	else
		return true;
}
bool test9()//проверим работу ==
{
	Matrix m(2, 2);
	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 3;
	m[1][1] = 4;
	Matrix m2 = m;
	if (m == m2)
	{
		return true;
	}
	else
		return false;
}
bool test10()//проверим работу *=
{
	Matrix m(2, 2);
	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 3;
	m[1][1] = 4;
	Matrix m2 = m;
	m *= 3;
	for (size_t i = 0; i < m.getRows(); i++)
	{
		for (size_t j = 0; j < m.getRows(); j++)
		{
			if (m[i][j] != m2[i][j] * 3)
			{
				return false;
			}
		}
	}
	return true;
}
bool test11()//проверим работу  оператора +
{
	Matrix m(2, 2);
	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 3;
	m[1][1] = 4;
	Matrix m2(2, 2);
	m2 = m;
	m2 *= 3;
	Matrix m3 = m2 + m;
	for (size_t i = 0; i < m2.getRows(); i++)
	{
		for (size_t j = 0; j < m2.getRows(); j++)
		{
			if (m3[i][j] != m[i][j] + m2[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{

	if (test1() && test2() && test3() && test4() && test5() && test6() && test7() && test8() && test9() && test10()&& test11())
	{
		cout << "all tests success" << endl;
	}
	else
	{
		if (!test1())
		{
			cout << "Test1 fail" << endl;
		}
		if (!test2())
		{
			cout << "Test2 fail" << endl;
		}
		if (!test3())
		{
			cout << "Test3 fail" << endl;
		}
		if (!test4())
		{
			cout << "Test4 fail" << endl;
		}
		if (!test5())
		{
			cout << "Test5 fail" << endl;
		}
		if (!test6())
		{
			cout << "Test6 fail" << endl;
		}
		if (!test7())
		{
			cout << "Test7 fail" << endl;
		}
		if (!test8())
		{
			cout << "Test8 fail" << endl;
		}
		if (!test9())
		{
			cout << "Test9 fail" << endl;
		}
		if (!test10())
		{
			cout << "Test10 fail" << endl;
		}
		if (!test11())
		{
			cout << "Test11 fail" << endl;
		}
	}
	return 0;
}