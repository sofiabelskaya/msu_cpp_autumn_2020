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
void test8(BigInt& n)
{
    if (n.GetStr() == "-99999980000001")
        cout << "test8 success" << endl;
    else
        cout << "fail8" << endl;
}
void test9(BigInt& n)
{
    if (n.GetStr() == "19999998")
        cout << "test9 success" << endl;
    else
        cout << "fail9" << endl;
}
void test10(BigInt& n)
{
    if (n.GetStr() == "123456789012345678901254567888")
        cout << "test10 success" << endl;
    else
        cout << "fail10" << endl;
}
void test11(BigInt& n)
{
    if (n.GetStr() == "1254567888")
        cout << "test11 success" << endl;
    else
        cout << "fail11" << endl;
}
void test12(BigInt& n)
{
    if (n.GetStr() == "139257035568")
        cout << "test12 success" << endl;
    else
        cout << "fail12" << endl;
}
void test13(BigInt& n)
{
    if (n.GetStr() == "-139257035568")
        cout << "test13 success" << endl;
    else
        cout << "fail13" << endl;
}
void test14(BigInt& n)
{
    if (n.GetStr() == "-139257035428742964432")
        cout << "test14 success" << endl;
    else
        cout << "fail14" << endl;
}
void test15(BigInt& n)
{
    string str = "17192226441411067339257035581908511331751159288480";
    //cout<<n<<n.GetStr()<<endl<<str;
    if (n.GetStr() == str)
        cout << "test15 success" << endl;
    else
        cout << "fail15" << endl;
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
    BigInt w("-9999999");
    BigInt v("9999999");
    BigInt res;
    res = v * w;
    test8(res);
    res = v - w;
    test9(res);
    res += b;
    test10(res);
    res -= BigInt("123456789012345678900000000000");
    test11(res);
    res *= 111;
    test12(res);
    res *= -1;
    test13(res);
    res *= BigInt("999999999");
    test14(res);
    res *= (-b);
    test15(res);
    return 0;
}