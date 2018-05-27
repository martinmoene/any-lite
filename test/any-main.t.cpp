// Copyright (c) 2016 Martin Moene
//
// https://github.com/martinmoene/any-lite
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "any-main.t.hpp"

#define any_PRESENT( x ) \
    std::cout << #x << ": " << x << "\n"

#define any_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

// Suppress:
// - unused parameter, for cases without assertions such as [.std...]
#if defined __clang__
# pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined __GNUC__
# pragma GCC   diagnostic ignored "-Wunused-parameter"
#endif

lest::tests & specification() 
{ 
    static lest::tests tests; 
    return tests; 
}

CASE( "any-lite version" "[.any][.version]" )
{
    any_PRESENT( any_lite_MAJOR );
    any_PRESENT( any_lite_MINOR );
    any_PRESENT( any_lite_PATCH );
    any_PRESENT( any_lite_VERSION );
}

CASE( "any configuration" "[.any][.config]" )
{
    any_PRESENT( any_HAVE_STD_ANY );
    any_PRESENT( any_CONFIG_SELECT_ANY );
    any_PRESENT( any_ANY_DEFAULT );
    any_PRESENT( any_ANY_LITE );
    any_PRESENT( any_ANY_STD );
    any_PRESENT( any_CPLUSPLUS );
}

CASE( "__cplusplus" "[.stdc++]" )
{
    any_PRESENT( __cplusplus );
}

CASE( "compiler version" "[.compiler]" )
{
#ifdef any_COMPILER_CLANG_VERSION
    any_PRESENT( any_COMPILER_CLANG_VERSION );
#else
    any_ABSENT(  any_COMPILER_CLANG_VERSION );
#endif

#ifdef any_COMPILER_GNUC_VERSION
    any_PRESENT( any_COMPILER_GNUC_VERSION );
#else
    any_ABSENT(  any_COMPILER_GNUC_VERSION );
#endif

#ifdef any_COMPILER_MSVC_VERSION
    any_PRESENT( any_COMPILER_MSVC_VERSION );
#else
    any_ABSENT(  any_COMPILER_MSVC_VERSION );
#endif
}

CASE( "Presence of C++ language features" "[.stdlanguage]" )
{
#if any_HAVE_AUTO 
    any_PRESENT( any_HAVE_AUTO );
#else    
    any_ABSENT(  any_HAVE_AUTO );
#endif

#if any_HAVE_NULLPTR 
    any_PRESENT( any_HAVE_NULLPTR );
#else    
    any_ABSENT(  any_HAVE_NULLPTR );
#endif

#if any_HAVE_STATIC_ASSERT
    any_PRESENT( any_HAVE_STATIC_ASSERT );
#else    
    any_ABSENT(  any_HAVE_STATIC_ASSERT );
#endif

#if any_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG 
    any_PRESENT( any_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
#else    
    any_ABSENT(  any_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
#endif

#if any_HAVE_ALIAS_TEMPLATE 
    any_PRESENT( any_HAVE_ALIAS_TEMPLATE );
#else    
    any_ABSENT(  any_HAVE_ALIAS_TEMPLATE );
#endif

#if any_HAVE_CONSTEXPR_11 
    any_PRESENT( any_HAVE_CONSTEXPR_11 );
#else    
    any_ABSENT(  any_HAVE_CONSTEXPR_11 );
#endif

#if any_HAVE_CONSTEXPR_14
    any_PRESENT( any_HAVE_CONSTEXPR_14 );
#else    
    any_ABSENT(  any_HAVE_CONSTEXPR_14 );
#endif

#if any_HAVE_ENUM_CLASS 
    any_PRESENT( any_HAVE_ENUM_CLASS );
#else    
    any_ABSENT(  any_HAVE_ENUM_CLASS );
#endif

#if any_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE 
    any_PRESENT( any_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
#else    
    any_ABSENT(  any_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
#endif

#if any_HAVE_EXPLICIT_CONVERSION 
    any_PRESENT( any_HAVE_EXPLICIT_CONVERSION );
#else    
    any_ABSENT(  any_HAVE_EXPLICIT_CONVERSION );
#endif

#if any_HAVE_INITIALIZER_LIST 
    any_PRESENT( any_HAVE_INITIALIZER_LIST );
#else    
    any_ABSENT(  any_HAVE_INITIALIZER_LIST );
#endif

#if any_HAVE_IS_DEFAULT 
    any_PRESENT( any_HAVE_IS_DEFAULT );
#else    
    any_ABSENT(  any_HAVE_IS_DEFAULT );
#endif

#if any_HAVE_IS_DELETE 
    any_PRESENT( any_HAVE_IS_DELETE );
#else    
    any_ABSENT(  any_HAVE_IS_DELETE );
#endif

#if any_HAVE_NOEXCEPT 
    any_PRESENT( any_HAVE_NOEXCEPT );
#else    
    any_ABSENT(  any_HAVE_NOEXCEPT );
#endif
}

CASE( "Presence of C++ library features" "[.stdlibrary]" )
{
#if any_HAVE_ARRAY
    any_PRESENT( any_HAVE_ARRAY );
#else    
    any_ABSENT(  any_HAVE_ARRAY );
#endif

#if any_HAVE_CONDITIONAL
    any_PRESENT( any_HAVE_CONDITIONAL );
#else    
    any_ABSENT(  any_HAVE_CONDITIONAL );
#endif

#if any_HAVE_CONTAINER_DATA_METHOD
    any_PRESENT( any_HAVE_CONTAINER_DATA_METHOD );
#else    
    any_ABSENT(  any_HAVE_CONTAINER_DATA_METHOD );
#endif

#if any_HAVE_REMOVE_CV
    any_PRESENT( any_HAVE_REMOVE_CV );
#else    
    any_ABSENT(  any_HAVE_REMOVE_CV );
#endif

#if any_HAVE_SIZED_TYPES
    any_PRESENT( any_HAVE_SIZED_TYPES );
#else    
    any_ABSENT(  any_HAVE_SIZED_TYPES );
#endif

#if any_HAVE_TYPE_TRAITS
    any_PRESENT( any_HAVE_TYPE_TRAITS );
#else    
    any_ABSENT(  any_HAVE_TYPE_TRAITS );
#endif

#if _HAS_CPP0X
    any_PRESENT( _HAS_CPP0X );
#else    
    any_ABSENT(  _HAS_CPP0X );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include/nonstd -o any-lite.t.exe any-main.t.cpp && any-lite.t.exe --pass
g++ -std=c++98 -I../include/nonstd -o any-lite.t.exe any-main.t.cpp && any-lite.t.exe --pass
g++ -std=c++03 -I../include/nonstd -o any-lite.t.exe any-main.t.cpp && any-lite.t.exe --pass
g++ -std=c++0x -I../include/nonstd -o any-lite.t.exe any-main.t.cpp && any-lite.t.exe --pass
g++ -std=c++11 -I../include/nonstd -o any-lite.t.exe any-main.t.cpp && any-lite.t.exe --pass
g++ -std=c++14 -I../include/nonstd -o any-lite.t.exe any-main.t.cpp && any-lite.t.exe --pass
g++ -std=c++17 -I../include/nonstd -o any-lite.t.exe any-main.t.cpp && any-lite.t.exe --pass

cl -EHsc -I../include/nonstd any-main.t.cpp && any-lite.t.exe --pass
#endif

// end of file
