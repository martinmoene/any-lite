#include "nonstd/any.hpp"

#include <algorithm>
#include <list>
#include <string>

using namespace nonstd;

typedef std::list<any> many;

void append_nothing(many & values)
{
    values.push_back(any());
}

void append_any(many & values, const any & value)
{
    values.push_back(value);
}

void append_int(many & values, int value)
{
    any to_append = value;
    values.push_back(to_append);
}

void append_string(many & values, const std::string & value)
{
    values.push_back(value);
}

void append_char_ptr(many & values, const char * value)
{
    values.push_back(value);
}

bool is_empty(const any & operand)
{
    return ! operand.has_value();
}

bool is_char(const any & operand)
{
    return operand.type() == typeid(char);
}

bool is_int(const any & operand)
{
    return operand.type() == typeid(int);
}

bool is_string(const any & operand)
{
    return operand.type() == typeid(std::string);
}

bool is_char_ptr(const any & operand)
{
    try
    {
        any_cast<const char *>(operand);
        return true;
    }
    catch(const bad_any_cast &)
    {
        return false;
    }
}

#include <iostream>

void count_all(many & values, std::ostream & out)
{
    out << "# empty: "          << std::count_if( values.begin(), values.end(), is_empty    )
        << "\n# char: "         << std::count_if( values.begin(), values.end(), is_char     )
        << "\n# int: "          << std::count_if( values.begin(), values.end(), is_int      )
        << "\n# string: "       << std::count_if( values.begin(), values.end(), is_string   )
        << "\n# const char *: " << std::count_if( values.begin(), values.end(), is_char_ptr );
}

int main()
{
   try
   {
      many m;

      append_any     ( m, any('a') );
      append_int     ( m, 42       );
      append_string  ( m, "hello"  );
      append_char_ptr( m, "world"  );
      append_nothing ( m           );

      count_all( m, std::cout );
   }
   catch( std::exception const & e )
   {
      std::cerr << "Error: " << e.what() << std::endl;
   }
}

// cl -nologo -EHsc -I../include 03-example.cpp && 03-example
// g++ -Wall -I../include -o 03-example 03-example.cpp && 03-example
