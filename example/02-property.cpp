#include "nonstd/any.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace nonstd;

struct property
{
    property( std::string const & name_, any const & value_ )
    : name( name_ ), value( value_ ) {}

    std::string name; any value;
};

std::ostream & operator<<( std::ostream & os, any const & v )
{
    if      ( v.type() == typeid( int         ) ) os << any_cast<int >( v );
    else if ( v.type() == typeid( std::string ) ) os << any_cast<std::string>( v );
    return os;
}

void print( std::ostream & os, property const & p )
{
    os << "[" << p.name << ":" << p.value << "] ";
}

int main()
{
    try
    {
        std::string hello = "hello, world";

        std::vector< property > db;
        db.push_back( property( "integral" ,  42    ) );
        db.push_back( property( "string"   ,  hello ) );

        for( auto & item : db )
        {
            print( std::cout, item );
        }
    }
    catch( std::exception const & e )
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// cl -nologo -EHsc -I../include 02-property.cpp && 02-property
// g++ -Wall -I../include -o 02-property 02-property.cpp && 02-property
