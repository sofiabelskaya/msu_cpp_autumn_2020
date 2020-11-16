#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include "format.h"

using namespace std;

int main()
{
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
    try {
        auto text = format("{2}+{1} = {0}", 2, "one");
    }
    catch (const FormatException& ex) {
        if (ex.get_error() == "invalid argument for {}: index out of range ")
            cout << "test1 success" << endl;
    }
    try {
        auto text = format("2}+{1} = {0}", 2, "one");
    }
    catch (const FormatException& ex) {
        if (ex.get_error() == "expected '{' before '}' ")
            cout << "test2 success" << endl;
    }
    try {
        auto text = format("{2", 2, "one");
    }
    catch (const FormatException& ex) {
        if (ex.get_error() == "expected '}' after '{' ")
            cout << "test3 success" << endl;
    }
    try {
        auto text = format("{gf}+{1} = {0}", 2, "one");
    }
    catch (const FormatException& ex) {
        if (ex.get_error() == "invalid argument for {} ")
            cout << "test4 success" << endl;
    }
}
