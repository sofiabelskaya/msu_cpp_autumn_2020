#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>
#include <ostream>
#include <string>
using namespace std;

class BigInt {
private:
    bool is_positive;
    bool is_set;
    size_t size;
    char* number;

public:
    BigInt();
    BigInt(const string& str);
    BigInt(const int& intn1);
    BigInt(const BigInt& n);
    BigInt(BigInt&& other);
    ~BigInt();
    friend ostream& operator<<(ostream& out, const BigInt& n);
    BigInt operator-() const;
    bool friend operator>(const BigInt& n1, const BigInt& n2);
    bool friend operator<(const BigInt& n1, const BigInt& n2);
    friend bool operator==(const BigInt& n1, const BigInt& n2);
    friend bool operator!=(const BigInt& n1, const BigInt& n2);
    friend BigInt operator-(const BigInt& n1, const BigInt& n2);
    friend BigInt operator+(const BigInt& n1, const BigInt& n2);
    friend BigInt operator+(const BigInt& n1, const int& intn2);
    friend BigInt operator*(const BigInt& n1, const BigInt& n2);
    BigInt& operator=(const BigInt& other);
    BigInt& operator=(const int& intn1);
    BigInt& operator=(BigInt&& moved);
    BigInt& operator+=(const BigInt& other);
    BigInt& operator+=(const int& int_other);
    const string GetStr() const;
};
#endif