#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <string>
#include "TokenParser.h"
using namespace std;

void test_words(vector<string>& str) //проверяю что правильно распарсились слова и коллбэк работает
{
    string test_str[5];
    test_str[0] = "Hello";
    test_str[1] = "world!";
    test_str[2] = "123ab";
    test_str[3] = "ab123";
    test_str[4] = "a123b";
    int i = 0;
    for (const auto& e : str) {
        if (e != test_str[i]) {
            cout << "test_words fail" << endl;
            break;
        }
        else {
            i++;
        }
    }
    if (i == 5) {
        cout << "test_words success" << endl;
    }
}
void test_digits(vector<int>& x) //проверяю что правильно распарсились ч и коллбэк работает
{
    int i = 0;
    int test_digits[2];
    test_digits[0] = 123;
    test_digits[1] = 321;
    for (const auto& e : x) {
        if (e != test_digits[i]) {
            cout << "test_digits fail" << e << endl;
            break;
        }
        else {
            i++;
        }
    }
    if (i == 2) {
        cout << "test_digits success" << endl;
    }
}

void test_tokens(vector<string>& str)
{
    string test_str[7];
    test_str[0] = "Hello";
    test_str[1] = "world!";
    test_str[2] = "123";
    test_str[3] = "123ab";
    test_str[4] = "321";
    test_str[5] = "ab123";
    test_str[6] = "a123b";
    int i = 0;
    for (const auto& e : str) {
        if (e != test_str[i]) {
            cout << "test_tokens fail " << e << endl;
            break;
        }
        else {
            i++;
            // cout << "test_tokens success" << e << endl;
        }
    }
    if (i == 7)
        cout << "test_tokens success" << endl;
}

void print_tokens(vector<string>& str)
{
    for (const auto& e : str) {
        cout << e << endl;
    }
}

int main()
{
    ifstream input;
    input.open("TextFile1.txt", std::ios_base::in);
    string str;
    if (input.is_open()) {
        cout << "File success open" << endl;
    }
    TokenParser parser(input);
    parser.SetWordTokenCallback(&test_words);
    parser.SetDigitTokenCallback(&test_digits);
    parser.SetEndCallback(&test_tokens);
    input.close();
    return 0;
}
