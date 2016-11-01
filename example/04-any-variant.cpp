#include "any.hpp"
#include "variant.hpp"

#include <cassert>
#include <string>

using namespace nonstd;

int main()
{
    std::string hello = "hello, world";
    {
        any var;
        
        var =  'v' ; assert( any_cast<char>( var ) == 'v' );
        var =   7  ; assert( any_cast<int >( var ) ==  7  );
        var =  42L ; assert( any_cast<long>( var ) == 42L );
        var = hello; assert( any_cast<std::string>( var ) == hello );
    }{
        variant< char, int, long, std::string > var;
        
        var =  'v' ; assert( get<  0 >( var ) == 'v' );
        var =  'v' ; assert( get<char>( var ) == 'v' );
        var =   7  ; assert( get<int >( var ) ==  7  );
        var =  42L ; assert( get<long>( var ) == 42L );    
        var = hello; assert( get<std::string>( var ) == hello );
    }
}
 
// cl -nologo -EHsc -I../include/nonstd -I../../variant-lite/include/nonstd 04-any-variant.cpp && 04-any-variant
// g++ -Wall -I../include/nonstd -I../../variant-lite/include/nonstd -o 04-any-variant 04-any-variant.cpp && 04-any-variant
