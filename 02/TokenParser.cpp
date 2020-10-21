#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <string>
#include <cstddef>
#include <algorithm>
#include "TokenParser.h"
using namespace std;

TokenParser::TokenParser(ifstream& in) //считываем строки из исходного файла
{
    string new_line;
    while (getline(in, new_line)) //считываем строки в вектор строк
    {
        lines.push_back(new_line);
    }
    for ( auto& my_line : lines) //итерируемся по вектору строк и считываем все
    //токены в вектор токенов
    {
		size_t delimiter_pos =0;
		size_t delimiter_pos_old =-1;
        while (true) {
            delimiter_pos = my_line.find_first_of(delimiter,delimiter_pos_old+1);
            if (delimiter_pos == string::npos) {
                if (my_line.begin()+delimiter_pos_old+1 < my_line.end()) {
                    tokens.push_back(string(my_line.begin()+delimiter_pos_old+1, my_line.end()));
                }
                break;
            }
            else {
                if (delimiter_pos == delimiter_pos_old+1) {
					delimiter_pos_old ++;
                }
                else {
                    tokens.push_back(string(my_line.begin()+delimiter_pos_old+1, my_line.begin() + delimiter_pos));
                    delimiter_pos_old = delimiter_pos;
                }
            }
        }
    }
	
    for (const auto& token : tokens) {
        bool is_digit = true;
        for (const auto& t : token) {
            if (!isdigit(t)) {
                words.push_back(token);
                is_digit = false;
                break;
            }
        }
        if (is_digit)
            digits.push_back(stoi(token));
    }
}
TokenParser::~TokenParser()
{
    lines.clear();
    tokens.clear();
    words.clear();
    digits.clear();
}
void TokenParser::SetStartCallback(function<void()> user_function) //перед началом парсинга пользователь может вызвать функцию без параметров
{
    user_function();
}
void TokenParser::SetDigitTokenCallback(function<void(vector<int>&)> user_function) //вызовет функцию пользователя от числовых токенов
{
    user_function(digits);
}
void TokenParser::SetWordTokenCallback(function<void(vector<string>&)> user_function) //вызовет функцию пользователя от токенов-слов
{
    user_function(words);
}
void TokenParser::SetEndCallback(
    function<void(vector<string>&)> user_function) //после парсинга пользователь может вызвать функцию от всех токенов
{
    user_function(tokens);
}