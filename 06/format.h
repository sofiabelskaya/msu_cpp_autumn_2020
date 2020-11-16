#ifndef FORMAT_H
#define FORMAT_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <exception>

using namespace std;

class FormatException {
private:
    string f_message;
    const char* f_file;
    int f_line;

public:
    FormatException(const string& message, const char* fileName, int line);
    friend ostream& operator<<(ostream& out, const FormatException& ex);
    const string get_error() const;
};

template <class T>
int str_args(stringstream& stream, T arg)
{
    stream << arg << endl;
    return 0;
}

template <class... Args>
string format(string format_arg, Args... args)
{
    size_t pos_op = 0;
    size_t pos_cl = 0;
    size_t curr_pos = 0;
    string text = "";
    stringstream stream;
    string e;
    vector<string> arg_vec;
    int l[] = { str_args(stream, args)... };
    unsigned int i;
    while (getline(stream, e)) {
        arg_vec.push_back(e);
    }
    while (curr_pos < format_arg.size()) {
        pos_op = format_arg.find_first_of("{", curr_pos);
        pos_cl = format_arg.find_first_of("}", curr_pos);
        if (pos_op == pos_cl && pos_op == string::npos) {
            text += format_arg;
            return text;
        }
        if (pos_op > pos_cl) {
            throw FormatException("expected '{' before '}' ", __FILE__, __LINE__);
        }
        if (pos_cl == string::npos && pos_op != string::npos) {
            throw FormatException("expected '}' after '{' ", __FILE__, __LINE__);
        }
        text += string(format_arg.begin() + curr_pos, format_arg.begin() + pos_op);
        try {
            i = stoi(string(format_arg.begin() + pos_op + 1, format_arg.begin() + pos_cl));
        }
        catch (const std::invalid_argument) {
            throw FormatException("invalid argument for {} ", __FILE__, __LINE__);
        }
        catch (const std::out_of_range) {
            throw FormatException("invalid argument for {} ", __FILE__, __LINE__);
        }

        if (i >= arg_vec.size()) {
            throw FormatException("invalid argument for {}: index out of range ", __FILE__, __LINE__);
        }
        text += arg_vec[i];
        curr_pos = pos_cl + 1;
    }
    return text;
}
#endif