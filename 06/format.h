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
string str_args(T& arg)
{
    stringstream stream;
    stream << arg;
    return stream.str();
}

template <class... Args>
string format(const string& format_arg, const Args&... args)
{
    size_t pos_op = 0;
    size_t pos_cl = 0;
    size_t curr_pos = 0;
    string text = "";
    vector<string> arg_vec = { str_args(args)... };
    unsigned int i;
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
        catch (const std::logic_error) {
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
