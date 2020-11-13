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
    Error process_one(T object)
    {
        out_ << object << Separator;
        return Error::NoError;
    }

    template <>
    Error process_one(bool object)
    {
        string text;
        text = object ? "true" : "false";
        out_ << text << Separator;
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
    Error operator()(ArgsT&... args)
    {
        return process(args...);
    }

    template <class... ArgsT>
    Error process(ArgsT&... args)
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
        string text;
        in_ >> text;
        //cout << "!" << text << endl;
        try {
            object = stoull(text);
        }
        catch (std::out_of_range& ex) {
            return Error::CorruptedArchive;
        }
        catch (std::invalid_argument& ex) {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }
    template <>
    Error process_one(bool& object)
    {
        string text;
        in_ >> text;
        if (text == "true") {
            object = true;
        }

        else if (text == "false") {
            object = false;
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
        return deserializer(a, b, c);
    }
};
#endif