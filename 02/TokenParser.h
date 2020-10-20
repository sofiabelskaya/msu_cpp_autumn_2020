#ifndef TOKENPARSER_H
#define TOKENPARSER_H
#include <cstddef>
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <string>
using namespace std;

class TokenParser {
private:
    vector<string> lines;
    vector<string> tokens;
    vector<string> words;
    vector<int> digits;
    string delimiter = " \t\n\r";

public:
    TokenParser(ifstream& in); //считываем строки из исходного файла
    ~TokenParser();
    void SetStartCallback(function<void()> user_function); //перед началом парсинга пользователь может вызвать функцию 

    void SetDigitTokenCallback(function<void(vector<int>)> user_function); //вызовет функцию пользователя от числовых токенов

    void SetWordTokenCallback(function<void(vector<string>)> user_function); //вызовет функцию пользователя от токенов-слов

    void SetEndCallback(function<void(vector<string>)> user_function); //после парсинга пользователь может вызвать функцию от всех токенов
};
#endif