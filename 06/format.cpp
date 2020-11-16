#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include "format.h"

using namespace std;

FormatException::FormatException(const string& message, const char* fileName, int line)
    : f_message(message)
    , f_file(fileName)
    , f_line(line)
{
}
ostream& operator<<(ostream& out, const FormatException& ex)
{
    out << ex.f_message << " File " << ex.f_file << " Line " << ex.f_line;
    return out;
}
const string FormatException::get_error() const
{
    return this->f_message;
}
