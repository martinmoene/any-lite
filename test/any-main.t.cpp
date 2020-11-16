//
// Copyright (c) 2016-2018 Martin Moene
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

CASE( "any-lite configuration" "[.any][.config]" )
{
    any_PRESENT( any_HAVE_STD_ANY );
    any_PRESENT( any_USES_STD_ANY );
    any_PRESENT( any_ANY_DEFAULT );
    any_PRESENT( any_ANY_NONSTD );
    any_PRESENT( any_ANY_STD );
    any_PRESENT( any_CONFIG_SELECT_ANY );
    any_PRESENT( any_CONFIG_NO_EXCEPTIONS );
    any_PRESENT( any_CPLUSPLUS );
}

CASE( "__cplusplus" "[.stdc++]" )
{
    any_PRESENT( __cplusplus );

#ifdef _MSVC_LANG
    any_PRESENT( _MSVC_LANG );
#else
    any_ABSENT(  _MSVC_LANG );
#endif
}

CASE( "Compiler version" "[.compiler]" )
{
#if any_USES_STD_ANY
    std::cout << "(Compiler version not available: using std::any)\n";
#else
    any_PRESENT( any_COMPILER_CLANG_VERSION );
    any_PRESENT( any_COMPILER_GNUC_VERSION );
    any_PRESENT( any_COMPILER_MSVC_VERSION );
#endif
}

CASE( "Presence of C++ language features" "[.stdlanguage]" )
{
#if any_USES_STD_ANY
    std::cout << "(Presence of C++ language features not available: using std::any)\n";
#else
//  any_PRESENT( any_HAVE_AUTO );
    any_PRESENT( any_HAVE_NULLPTR );
    any_PRESENT( any_HAVE_STATIC_ASSERT );
    any_PRESENT( any_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
//  any_PRESENT( any_HAVE_ALIAS_TEMPLATE );
    any_PRESENT( any_HAVE_CONSTEXPR_11 );
    any_PRESENT( any_HAVE_CONSTEXPR_14 );
//  any_PRESENT( any_HAVE_ENUM_CLASS );
//  any_PRESENT( any_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
//  any_PRESENT( any_HAVE_EXPLICIT_CONVERSION );
    any_PRESENT( any_HAVE_INITIALIZER_LIST );
//  any_PRESENT( any_HAVE_IS_DEFAULT );
//  any_PRESENT( any_HAVE_IS_DELETE );
    any_PRESENT( any_HAVE_NOEXCEPT );
#endif
}

CASE( "Presence of C++ library features" "[.stdlibrary]" )
{
#if any_USES_STD_ANY
    std::cout << "(Presence of C++ library features not available: using std::any)\n";
#else
//  any_PRESENT( any_HAVE_ARRAY );
    any_PRESENT( any_HAVE_ADD_CONST );
    any_PRESENT( any_HAVE_TR1_ADD_CONST );
//  any_PRESENT( any_HAVE_CONDITIONAL );
//  any_PRESENT( any_HAVE_CONTAINER_DATA_METHOD );
//  any_PRESENT( any_HAVE_REMOVE_CV );
    any_PRESENT( any_HAVE_REMOVE_REFERENCE );
    any_PRESENT( any_HAVE_TR1_REMOVE_REFERENCE );
//  any_PRESENT( any_HAVE_SIZED_TYPES );
    any_PRESENT( any_HAVE_TYPE_TRAITS );
    any_PRESENT( any_HAVE_TR1_TYPE_TRAITS );
#endif

#if defined _HAS_CPP0X
    any_PRESENT( _HAS_CPP0X );
#else
    any_ABSENT(  _HAS_CPP0X );
#endif

#ifdef __cpp_exceptions
    any_PRESENT( __cpp_exceptions );
#else
    any_ABSENT(  __cpp_exceptions );
#endif

#ifdef __EXCEPTIONS
    any_PRESENT( __EXCEPTIONS );
#else
    any_ABSENT(  __EXCEPTIONS );
#endif

#ifdef _HAS_EXCEPTIONS
    any_PRESENT( _HAS_EXCEPTIONS );
#else
    any_ABSENT(  _HAS_EXCEPTIONS );
#endif

#ifdef _CPPUNWIND
    any_PRESENT( _CPPUNWIND );
#else
    any_ABSENT(  _CPPUNWIND );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include -o any-lite.t.exe any-main.t.cpp && any-lite.t.exe --pass
g++ -std=c++98 -I../include -o any-lite.t.exe any-main.t.cpp && any-lite.t.exe --pass
g++ -std=c++03 -I../include -o any-lite.t.exe any-main.t.cpp && any-lite.t.exe --pass
g++ -std=c++0x -I../include -o any-lite.t.exe any-main.t.cpp && any-lite.t.exe --pass
g++ -std=c++11 -I../include -o any-lite.t.exe any-main.t.cpp && any-lite.t.exe --pass
g++ -std=c++14 -I../include -o any-lite.t.exe any-main.t.cpp && any-lite.t.exe --pass
g++ -std=c++17 -I../include -o any-lite.t.exe any-main.t.cpp && any-lite.t.exe --pass

cl -EHsc -I../include any-main.t.cpp && any-lite.t.exe --pass
#endif

// end of file
