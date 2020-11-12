#pragma once
#ifndef SERIALIZER_DESERIALISER_H
#define SERIALIZER_DESERIALISER_H
#include <iostream>
#include <ostream>
#include <string.h>
#include <sstream>
#include <cassert>
using namespace std;

enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
    static constexpr char Separator = ' ';

public:
    explicit Serializer(ostream& out);

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }

    template <class... ArgsT>
    Error process(ArgsT... args)
    {
        Error err[] = { process_one(args)... };
        for (auto& e : err) {
            if (e != Error::NoError) {
                return Error::CorruptedArchive;
            }
        }
        return Error::NoError;
    }

    template <class T>
    Error process_one(T& object)
    {
        const char* sep = &Separator;
        const auto curr_pos = out_.tellp();
        string txt = to_string(object);
        out_.write(txt.data(), txt.length());
        out_.write(sep, 1);
        return Error::NoError;
    }

    template <>
    Error process_one(bool& object)
    {
        string txt;
        txt = object ? "true" : "false";
        const char* sep = &Separator;
        const auto curr_pos = out_.tellp();
        out_.write(txt.data(), txt.length());
        out_.write(sep, 1);
        return Error::NoError;
    }

private:
    ostream& out_;
};

class Deserializer {
public:
    explicit Deserializer(istream& in);

    template <class T>
    Error load(T& object)
    {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }

    template <class... ArgsT>
    Error process(ArgsT... args)
    {
        Error err[] = { process_one(args)... };
        for (auto& e : err) {
            if (e != Error::NoError) {
                return Error::CorruptedArchive;
            }
        }
        return Error::NoError;
    }

    template <class T>
    Error process_one(T* object)
    {
        string text;
        try {
            in_ >> text;
        }
        catch (...) {
            return Error::CorruptedArchive;
        }

        //cout << "!" << text << endl;
        try {
            *object = stoi(text);
        }
        catch (...) {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }
    template <>
    Error process_one(bool* object)
    {
        string text;
        try {
            in_ >> text;
        }
        catch (...) {
            return Error::CorruptedArchive;
        }
        if (text == "true") {
            try {
                *object = true;
            }
            catch (...) {
                return Error::CorruptedArchive;
            }
        }

        else if (text == "false") {
            try {
                *object = false;
            }
            catch (...) {
                return Error::CorruptedArchive;
            }
        }
        else
            return Error::CorruptedArchive;

        return Error::NoError;
    }

private:
    istream& in_;
};

struct Data {
    uint64_t a;
    bool b;
    uint64_t c;
    Data(uint64_t a, bool b, uint64_t c);
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(&a, &b, &c);
    }
};
#endif