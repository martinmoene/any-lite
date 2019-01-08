#include "nonstd/any.hpp"

using namespace nonstd;

int main()
{
    any var =  'v' ;

    char chr = any_cast<char>( var );   // ok
    int  val = any_cast<int >( var );   // asserts
}

// cl -nologo -I../include 05-no-exceptions.cpp && 05-no-exceptions
// g++ -Wall -fno-exceptions -I../include -o 05-no-exceptions 05-no-exceptions.cpp && 05-no-exceptions
