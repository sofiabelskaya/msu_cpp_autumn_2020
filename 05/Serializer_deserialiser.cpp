#include <iostream>
#include <ostream>
#include <string.h>
#include <sstream>
#include <cassert>
#include "Serializer_deserialiser.h"

using namespace std;

Serializer::Serializer(std::ostream& out)
    : out_(out)
{
}
Deserializer::Deserializer(istream& in)
    : in_(in)
{
}
Data::Data(uint64_t a, bool b, uint64_t c)
    : a(a)
    , b(b)
    , c(c)
{
}