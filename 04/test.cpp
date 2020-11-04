#include <iostream>
#include <ostream>
#include <string>
#include "BigInt.h"
using namespace std;

void test1(BigInt& n)
{
    if (n.GetStr() == "1")
        cout << "test1 success" << endl;
    else
        cout << "fail1" << endl;
}
void test2(BigInt& n)
{
    if (n.GetStr() == "123456789012345678901234567890")
        cout << "test2 success" << endl;
    else
        cout << "fail2" << endl;
}
void test3(BigInt& n)
{
    if (n.GetStr() == "123456789012345678901234567892")
        cout << "test3 success" << endl;
    else
        cout << "fail3" << endl;
}
void test4(BigInt& n)
{
    if (n.GetStr() == "123456789012345678901234567892")
        cout << "test4 success" << endl;
    else
        cout << "fail4" << endl;
}
void test5(BigInt& n)
{
    if (n.GetStr() == "")
        cout << "test5 success" << endl;
    else
        cout << "fail5" << endl;
}
void test6(BigInt& n)
{
    if (n.GetStr() == "246913578024691357802469135782")
        cout << "test6 success" << endl;
    else
        cout << "fail6" << endl;
}
void test7(BigInt& n)
{
    if (n.GetStr() == "-123456789012345678901234567890")
        cout << "test7 success" << endl;
    else
        cout << "fail7" << endl;
}

int main()
{
    BigInt a = 1;
    test1(a); //проверим работу с int
    BigInt b("123456789012345678901234567890");
    test2(b); //проверим работу со string
    BigInt c = a * b + 2;
    test3(c); //проверим произведение и сумму с int
    BigInt d;
    d = std::move(c);
    test4(d); //проверим что там значение с
    test5(c); //проверим что с пустое
    a = d + b;
    test6(a); // проверим сумму
    c = d - a;
    test7(c); //проверим разность
    return 0;
}