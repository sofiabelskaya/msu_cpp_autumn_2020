#include <iostream>
#include <ostream>
#include <string.h>
#include <sstream>
#include <cassert>
using namespace std;
#include "Serializer_deserialiser.h"

Error test_deserialise_error()
{
    stringstream stream;
    stream << "false";
    Deserializer deserializer(stream);
    uint64_t a;
    return deserializer(&a);
}
Error test2_deserialise_error()
{
    stringstream stream;
    stream << "1";
    Deserializer deserializer(stream);
    bool a;
    return deserializer(&a);
}
int main()
{
    Data x{ 1, false, 3 };

    stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y{ 0, true, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    //проверим, что если в потоке булева переменная, получим ошибку при попытке считать ее в инт
    assert(test_deserialise_error() != Error::NoError);
    //проверим, что если в потоке будет интовая переменная, получим ошибку при попытке считать ее в bool
    assert(test2_deserialise_error() != Error::NoError);
    cout << "All tests success" << endl;
    return 0;
}