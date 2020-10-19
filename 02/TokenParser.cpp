#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <string>
#include <cstddef>
#include "TokenParser.h"
using namespace std;
TokenParser::TokenParser(ifstream& in) //считываем строки из исходного файла
{
    string new_line;
    string new_token;
    string my_line;
    while (getline(in, new_line)) //считываем строки в вектор строк
    {
        lines.push_back(new_line);
    }
    for (auto line : lines) //итерируемся по вектору строк и считываем все токены в вектор токенов
    {
        my_line = line;
        while (true) {
            size_t delimiter_pos = my_line.find_first_of(delimiter);
            if (delimiter_pos == string::npos) {
                if (my_line != "") {
                    tokens.push_back(my_line);
                }
                break;
            }
            else {
                if (delimiter_pos == 0) {
                    my_line = my_line.substr(delimiter_pos + 1);
                }
                else {
                    new_token = my_line.substr(0, delimiter_pos);
                    if (new_token.find_first_of(delimiter) == string::npos && new_token != "") {
                        tokens.push_back(new_token);
                    }
                    my_line = my_line.substr(delimiter_pos + 1);
                }
            }
        }
    }
    for (auto token : tokens) {
        size_t not_digit_pos = token.find_first_not_of("0123456789");
        size_t digit_pos = token.find_first_of("0123456789");
        size_t alphabetic_pos = token.find_first_of("abcdefghijklmnopqrstuvwxyz");
        if (not_digit_pos == string::npos && digit_pos != string::npos) {
            digits.push_back(stoi(token));
        }
        else if (alphabetic_pos != string::npos) {
            words.push_back(token);
        }
    }
}
TokenParser::~TokenParser()
{
    lines.clear();
    tokens.clear();
    words.clear();
    digits.clear();
}
void TokenParser::SetStartCallback(function<void(vector<string>)> user_function) //перед началом парсинга пользователь может вызвать функцию от исходных строк
{
    user_function(lines);
}
void TokenParser::SetDigitTokenCallback(function<void(vector<int>)> user_function) //вызовет функцию пользователя от числовых токенов
{
    user_function(digits);
}
void TokenParser::SetWordTokenCallback(function<void(vector<string>)> user_function) //вызовет функцию пользователя от токенов-слов
{
    user_function(words);
}
void TokenParser::SetEndCallback(function<void(vector<string>)> user_function) //после парсинга пользователь может вызвать функцию от всех токенов
{
    user_function(tokens);
}
