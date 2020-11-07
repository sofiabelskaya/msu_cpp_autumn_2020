#include <iostream>
#include <ostream>
#include <string>
#include <algorithm>
#include "BigInt.h"
using namespace std;

BigInt::BigInt()
    : number(nullptr)
    , is_positive(true)
    , is_set(false)
    , size(0)
{
}
BigInt::BigInt(const string& str)
{
    size_t pos = str.find_first_not_of("-0");
    if (str == "") {
        number = nullptr;
        is_positive = true;
        is_set = false;
        size = 0;
    }
    else if (pos == string::npos) {
        size = 1;
        number = new char[size];
        is_set = true;
        is_positive = true;
        number[0] = '0';
    }
    else {
        if (str[0] == '-')
            is_positive = false;
        else
            is_positive = true;
        size = (str.length() - pos);

        //cout << " size " << size << " " << pos <<" pos"<< endl;
        number = new char[size];
        for (size_t i = 0; i < size; i++) {
            number[i] = str[pos + i];
        }
        is_set = true;
    } //cout<<"size "<<size<<" "<<*this<<"!";
}
BigInt::BigInt(const int intn1)
{
    string str = to_string(intn1);
    *this = BigInt(str);
}

BigInt::BigInt(const BigInt& n)
    : is_positive(n.is_positive)
    , size(n.size)
    , is_set(n.is_set)
{
    if (is_set) {
        number = new char[size];
        for (size_t i = 0; i < size; i++) {
            number[i] = n.number[i];
        }
    }
    else
        number = nullptr;
}

BigInt::BigInt(BigInt&& other) noexcept
    : size(move(other.size)),
      number(other.number),
      is_positive(move(other.is_positive)),
      is_set(move(other.is_set))
{
    other.number = nullptr;
    other.size = 0;
    other.is_positive = true;
    other.is_set = false;
}
BigInt::~BigInt()
{
    if (this->is_set) {
        delete[] this->number;
        this->size = 0;
        this->is_positive = true;
        number = nullptr;
        is_set = false;
    }
}

ostream& operator<<(ostream& out, const BigInt& n)
{
    if (n.is_positive) {
        for (size_t i = 0; i < n.size; i++) {
            out << n.number[i];
        }
        out << endl;
    }
    else {
        out << "-";
        for (size_t i = 0; i < n.size; i++) {
            out << n.number[i];
        }
        out << endl;
    }
    return out;
}
BigInt BigInt::operator-() const
{
    BigInt copy(*this);
    copy.is_positive = !copy.is_positive;
    return copy;
}
bool operator>(const BigInt& n1, const BigInt& n2)
{
    if (!n1.is_set || !n2.is_set) {
        return false;
    }
    if (n1.is_positive && n2.is_positive) {
        if (n1.size > n2.size) {
            return true;
        }
        if (n1.size < n2.size) {
            return false;
        }
        int c = 0;
        size_t i = 0;
        while (n1.number[i] == n2.number[i]) {
            if (i < n1.size - 1) {
                i++;
            }
            else
                return false;
        }
        if (n1.number[i] > n2.number[i]) {
            return true;
        }
        else
            return false;
    }
    else if (!n1.is_positive && n2.is_positive)
        return false;
    else if (n1.is_positive && !n2.is_positive)
        return true;
    else
        return ((-n2) > (-n1));
}
bool operator<(const BigInt& n1, const BigInt& n2)
{
    if (!n1.is_set || !n2.is_set) {
        return false;
    }
    return (n2 > n1);
}

bool operator==(const BigInt& n1, const BigInt& n2)
{
    if (!n1.is_set || !n2.is_set) {
        return false;
    }
    if (n1 < n2)
        return false;
    else if (n2 < n1)
        return false;
    else
        return true;
}
bool operator!=(const BigInt& n1, const BigInt& n2)
{
    if (!n1.is_set || !n2.is_set) {
        return false;
    }
    if (n1 == n2)
        return false;
    else
        return true;
}
BigInt operator-(const BigInt& n1, const BigInt& n2)
{
    if (!n1.is_set || !n2.is_set) {
        return n1;
    }
    int tmp = 0;
    int v1 = 0;
    int v2 = 0;
    string str = "";
    if (n1.is_positive && !n2.is_positive)
        return (n1 + (-n2));
    if (!n1.is_positive && n2.is_positive)
        return -((-n1) + n2);
    if (!n1.is_positive && !n2.is_positive)
        return ((-n2) - (-n1));
    if (n1 > n2) {
        for (size_t i = 0; i < n2.size; i++) {
            v1 = n1.number[n1.size - 1 - i] - '0';
            v2 = n2.number[n2.size - 1 - i] - '0';
            if (v1 >= v2 + tmp) {
                char s = ('0' + ((v1 - v2 - tmp) % 10));
                str += s;
                tmp = 0;
            }
            else {
                char s = ('0' + ((10 + v1 - v2 - tmp) % 10));
                str += s;
                tmp = 1;
            }
        }
        for (size_t i = n2.size; i < n1.size; i++) {
            v1 = n1.number[n1.size - 1 - i] - '0';
            if (v1 >= tmp) {
                char s = ('0' + ((v1 - tmp) % 10));
                str += s;
                tmp = 0;
            }
            else {
                char s = ('0' + ((10 + v1 - tmp) % 10));
                str += s;
                tmp = 1;
            }
        }
        reverse(str.begin(), str.end());
        return BigInt(str);
    }
    else if (n2 > n1)
        return -(n2 - n1);
    else
        return BigInt("0");
}

BigInt operator+(const BigInt& n1, const BigInt& n2)
{
    if (!n1.is_set || !n2.is_set) {
        return n1;
    }
    if (n1.is_positive && !n2.is_positive) {
        return n1 - (-n2);
    }
    if (!n1.is_positive && n2.is_positive) {
        return n2 - (-n1);
    }
    if (!n1.is_positive && !n2.is_positive) {
        return -((-n1) + (-n2));
    }
    int tmp = 0;
    int v1 = 0;
    int v2 = 0;
    string str = "";
    for (size_t i = 0; i < min(n1.size, n2.size); i++) {
        v1 = n1.number[n1.size - 1 - i] - '0';
        v2 = n2.number[n2.size - 1 - i] - '0';
        char s = ('0' + ((v1 + v2 + tmp) % 10));
        str += s;
        tmp = (v1 + v2 + tmp) / 10;
    }
    for (size_t i = min(n1.size, n2.size); i < max(n1.size, n2.size); i++) {

        if (n1.size > n2.size) {
            v1 = n1.number[n1.size - 1 - i] - '0';
            char s = ('0' + ((v1 + tmp) % 10));
            str += s;
            tmp = (v1 + tmp) / 10;
        }
        else {

            v1 = n2.number[n2.size - 1 - i] - '0';
            char s = ('0' + ((v1 + tmp) % 10));
            str += s;
            tmp = (v1 + tmp) / 10;
        }
    }
    if (tmp != 0)
        str += '0' + tmp;
    reverse(str.begin(), str.end());
    return BigInt(str);
}

BigInt operator+(const BigInt& n1, const int intn2)
{
    if (n1.is_set) {
        return (n1 + BigInt(to_string(intn2)));
    }
    else
        return n1;
}
BigInt operator*(const BigInt& n1, const BigInt& n2)
{
    if (!n1.is_set || !n2.is_set) {
        return n1;
    }
    int tmp = 0;
    int v1 = 0;
    int v2 = 0;
    string str_i = "";
    BigInt tmp_s("0");
    string zero_str = "";
    /*
    for (size_t i = 0; i < min(n1.size, n2.size); i++) {
        if (n1.size < n2.size) {
            v1 = n1.number[n1.size - 1 - i] - '0';
        }
        else {
            v1 = n2.number[n2.size - 1 - i] - '0';
        }
        str_i = "";
        for (size_t j = 0; j < max(n1.size, n2.size); j++) {
            if (n1.size >= n2.size) {
                v2 = n1.number[n1.size - 1 - j] - '0';
                char s = ('0' + ((v1 * v2 + tmp) % 10));
                str_i += s;
                tmp = (v1 * v2 + tmp) / 10;
            }
            else {
                v2 = n2.number[n2.size - 1 - j] - '0';
                char s = ('0' + ((v1 * v2 + tmp) % 10));
                str_i += s;
                tmp = (v1 * v2 + tmp) / 10;
            }
        }
        reverse(str_i.begin(), str_i.end());
        str_i += zero_str;
        BigInt tmp_ss(str_i);
        tmp_s += tmp_ss;
        zero_str += '0';
        if (n1.is_positive != n2.is_positive) {
            tmp_s.is_positive = false;
        }
    }*/
    if (n1 < n2 || n1 == n2) {
        for (size_t i = 0; i < n1.size; i++) {
            tmp = 0;
            v1 = n1.number[n1.size - 1 - i] - '0';
            str_i = "";
            for (size_t j = 0; j < n2.size; j++) {
                v2 = n2.number[n2.size - 1 - j] - '0';
                char s = ('0' + ((v1 * v2 + tmp) % 10));
                str_i += s;
                tmp = (v1 * v2 + tmp) / 10;
            }
            str_i += (tmp + '0');
            //cout<<"str_i "<<str_i<<endl;
            reverse(str_i.begin(), str_i.end());
            str_i += zero_str;
            BigInt tmp_ss(str_i);
            //cout<<"tmp_ss "<<tmp_ss;
            tmp_s += tmp_ss;
            //cout<<"tmp_s "<<tmp_s;
            zero_str += '0';
        }

        if (n1.is_positive != n2.is_positive) {
            tmp_s.is_positive = false;
        }
        return tmp_s;
    }
    else
        return n2 * n1;
}

BigInt& BigInt::operator=(const BigInt& other)
{
    if (this == &other) {
        return *this;
    }
    if (this->is_set) {
        delete[] this->number;
        this->size = 0;
        this->is_positive = true;
        this->number = nullptr;
        this->is_set = false;
    }
    if (other.is_set) {
        this->size = other.size;
        this->is_positive = other.is_positive;
        this->number = new char[this->size];
        for (size_t i = 0; i < this->size; i++) {
            this->number[i] = other.number[i];
        }
        this->is_set = true;
    }
    return *this;
}
BigInt& BigInt::operator=(const int intn1)
{
    BigInt other(to_string(intn1));
    if (this->is_set) {
        delete[] this->number;
        this->size = 0;
        this->is_positive = true;
        this->number = nullptr;
        this->is_set = false;
    }
    if (other.is_set) {
        this->size = other.size;
        this->is_positive = other.is_positive;
        this->number = new char[this->size];
        for (size_t i = 0; i < this->size; i++) {
            this->number[i] = other.number[i];
        }
        this->is_set = true;
    }
    return *this;
}
BigInt& BigInt::operator=(BigInt&& moved) noexcept
{
    //cout <<"move "<< moved;
    if (this == &moved) {
        return *this;
    }
    if (this->is_set) {
        delete[] this->number; //удаляем высвобожденную память под обьект
        this->size = 0;
        this->is_positive = true;
        this->number = nullptr;
        this->is_set = false;
    }
    if (moved.is_set) {
        size = move(moved.size);
        number = moved.number; //перемещаем указатель на нужную память
        is_set = move(moved.is_set);
        is_positive = move(moved.is_positive);
        moved.number = nullptr;
        moved.size = 0;
        moved.is_set = false;
        moved.is_positive = true;
    }
    return *this;
}
BigInt& BigInt::operator+=(const BigInt& other)
{
    if (this->is_set) {
        *this = BigInt(*this + other);
    }
    return *this;
}
BigInt& BigInt::operator+=(const int int_other)
{
    BigInt tmp(to_string(int_other));
    if (this->is_set) {
        *this = BigInt(*this + tmp);
    }
    return *this;
}
BigInt& BigInt::operator*=(const BigInt& other)
{
    if (this->is_set) {
        *this = BigInt(*this * other);
    }
    return *this;
}
BigInt& BigInt::operator*=(const int int_other)
{
    BigInt tmp(to_string(int_other));
    if (this->is_set) {
        *this = BigInt(*this * tmp);
    }
    return *this;
}
BigInt& BigInt::operator-=(const int int_other)
{
    BigInt tmp(to_string(int_other));
    if (this->is_set) {
        *this = BigInt(*this - tmp);
    }
    return *this;
}
BigInt& BigInt::operator-=(const BigInt& other)
{
    if (this->is_set) {
        *this = BigInt(*this - other);
    }
    return *this;
}
string BigInt::GetStr() const
{
    string str = "";
    if (!is_positive)
        str += '-';
    if (this->is_set) {
        str += string(this->number, this->size);
    }
    return str;
}
