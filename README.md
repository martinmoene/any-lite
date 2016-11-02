# any-lite: A single-file header-only version of a C++17-like any, a type-safe container for single values of any type for C++98, C++11 and later

[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)  [![Standard](https://img.shields.io/badge/c%2B%2B-98-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![Standard](https://img.shields.io/badge/c%2B%2B-11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![Standard](https://img.shields.io/badge/c%2B%2B-14-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![Standard](https://img.shields.io/badge/c%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT) [![Build Status](https://travis-ci.org/martinmoene/any-lite.svg?branch=master)](https://travis-ci.org/martinmoene/any-lite) [![Build status](https://ci.appveyor.com/api/projects/status/gpmw4gt271itoy2n?svg=true)](https://ci.appveyor.com/project/martinmoene/any-lite) [![Version](https://badge.fury.io/gh/martinmoene%2Fany-lite.svg)](https://github.com/martinmoene/any-lite/releases) [![download](https://img.shields.io/badge/latest%20version%20%20-download-blue.svg)](https://raw.githubusercontent.com/martinmoene/any-lite/master/include/nonstd/any.hpp)

**Contents**  
- [Example usage](#example-usage)
- [In a nutshell](#in-a-nutshell)
- [License](#license)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Synopsis](#synopsis)
- [Features](#features)
- [Reported to work with](#reported-to-work-with)
- [Building the tests](#building-the-tests)
- [Other implementations of any](#other-implementations-of-any)
- [Notes and references](#notes-and-references)
- [Appendix](#appendix)


Example usage
-------------

```Cpp
#include "any.hpp"

#include <cassert>
#include <string>

using namespace nonstd;

int main()
{
    std::string hello = "hello, world";
    
    any var;
    
    var =  'v' ; assert( any_cast<char>( var ) == 'v' );
    var =   7  ; assert( any_cast<int >( var ) ==  7  );
    var =  42L ; assert( any_cast<long>( var ) == 42L );
    var = hello; assert( any_cast<std::string>( var ) == hello );
}
```

### Compile and run

```
prompt> g++ -Wall -I../include/nonstd -o 01-basic 01-basic.cpp && 01-basic
```

In a nutshell
-------------
**any lite** is a single-file header-only library to represent a type-safe container for single values of any type. The library aims to provide a [C++17-like any](http://en.cppreference.com/w/cpp/utility/any) for use with C++98 and later.

**Features and properties of any lite** are ease of installation (single header), freedom of dependencies other than the standard library. *any lite* shares the approach to in-place tags with [variant-lite](https://github.com/martinmoene/variant-lite) and (later) with [optional-lite](https://github.com/martinmoene/optional-lite) and these libraries can be used together.

**Limitations of any lite** are the absence of small-object optimization: all contained objects are dynamically allocated. Move construction, move assignment and emplacement require C++11 and are not supported when compiling under C++98.


License
-------
*any lite* uses the [MIT](LICENSE) license.
 

Dependencies
------------
*any lite* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).


Installation
------------
*any lite* is a single-file header-only library. Put `any.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.


Synopsis
--------

**Contents**  
- [Types in namespace nonstd](#types-in-namespace-nonstd)  
- [Interface of *any lite*](#interface-of-any-lite)  
- [Algorithms for *any lite*](#algorithms-for-any-lite)  
- [Configuration macros](#configuration-macros)

### Types in namespace nonstd

| Purpose               | Type | Notes |
|-----------------------|------|-------|
| Type-safe container   | class any                        | &nbsp; |
| Error reporting       | class bad_any_cast               | &nbsp; |
| In-place construction | struct in_place_tag              | &nbsp; |
| &nbsp;                | in_place                         | select type or index for in-place construction |
| &nbsp;                | nonstd_lite_in_place_type_t( T)  | macro for alias template in_place_type_t&lt;T>  |
| &nbsp;                | nonstd_lite_in_place_index_t( T )| macro for alias template in_place_index_t&lt;T> |

### Interface of *any lite*

| Kind         | Std  | Method                                       | Result |
|--------------|------|----------------------------------------------|--------|
| Construction |&nbsp;| any()                                        | default-construct             |
| &nbsp;       |&nbsp;| any( any const & rhs )                       | copy-construct from other any |
| &nbsp;       | C++11| any( any && rhs ) noexcept                   | move-construct from other any |
| &nbsp;       | C++11| template< class ValueType ><br>any( ValueType && value ) noexcept | move-assign from value |
| &nbsp;       | C++11| template< class T ><br>explicit any( in_place_type_t&lt;T>, Args&&... args ) | in-place-construct type T |
| &nbsp;       | C++11| template< class T, class U, class... Args ><br>explicit any( in_place_type_t&lt;T>, std::initializer_list&lt;U> il, Args&&... args ) | in-place-construct type T |
| &nbsp;       |<C++11| template< class ValueType ><br>any( ValueType const & value ) | copy-assign from value |
| &nbsp;       |&nbsp;| ~any() | destroy current object |
| Assigment    |&nbsp;| any & operator=( any const & rhs ) | copy-assign from other |
| &nbsp;       | C++11| any & operator=( any && rhs ) noexcept | move-assign from other |
| &nbsp;       | C++11| template< class ValueType, ...><br>any & operator=( ValueType && rhs ) | (move-)assign from value |
| &nbsp;       |<C++11| template< class ValueType ><br>any & operator=( ValueType const & rhs ) | copy-assign from value |
| Modifiers    | C++11| template< class T, class... Args ><br>void emplace( Args && ... args ) | emplace type T |
| &nbsp;       | C++11| template< class T, class U, class... Args ><br>void emplace( std::initializer_list&lt;U> il, Args&&... args ) | emplace type T |
| &nbsp;       |&nbsp;| void reset() noexcept | destroy contained object |
| &nbsp;       |&nbsp;| void swap( any & rhs ) noexcept | exchange with other any |
| Observers    |&nbsp;| bool has_value() const noexcept | contains an object |
| &nbsp;       |&nbsp;| const std::type_info & type() const noexcept | Type of contained object |

### Algorithms for *any lite*

| Kind                      | Std  | Function | Result |
|---------------------------|------|----------|--------|
| Create                    |C++11 | template< class T, class ...Args ><br>any make_any( Args&& ...args ) | in-place construct |
| &nbsp;                    |C++11 | template< class T, class U, class ...Args ><br>any make_any( std::initializer_list&lt;U> il, Args&& ...args ) | in-place construct |
| Access                    |&nbsp;| T any_cast<T>( any const & )  | obtained value |
| &nbsp;                    |&nbsp;| T any_cast<T>( any & )        | obtained value |
| &nbsp;                    |C++11 | T any_cast<T>( any && )       | obtained value |
| &nbsp;                    |&nbsp;| T const \* any_cast<T>( any const * )  | pointer to obtained value |
| &nbsp;                    |&nbsp;| T \* any_cast<T>( any * )     | pointer to obtained value |
| Swap                      |&nbsp;| void swap( any & x, any & y ) | exchange contents |

### Configuration macros

Currently there are no configuration macros.


Reported to work with
---------------------
The table below mentions the compiler versions *any lite* is reported to work with.

OS        | Compiler   | Versions |
---------:|:-----------|:---------|
Windows   | Clang/LLVM | ? |
&nbsp;    | GCC        | 5.2.0 |
&nbsp;    | Visual C++<br>(Visual Studio)| 8 (2005), 10 (2010), 11 (2012),<br>12 (2013), 14 (2015) |
GNU/Linux | Clang/LLVM | 3.5.0 |
&nbsp;    | GCC        | 4.8.4 |
OS X      | ?          | ?   |


Building the tests
------------------
To build the tests you need:

- [CMake](http://cmake.org), version 2.8.12 or later to be installed and in your PATH.
- A [suitable compiler](#reported-to-work-with).

The [*lest* test framework](https://github.com/martinmoene/lest)  is included in the [test folder](test).

The following steps assume that the [*any lite* source code](https://github.com/martinmoene/any-lite) has been cloned into a directory named `c:\any-lite`.

1. Create a directory for the build outputs for a particular architecture.
Here we use c:\any-lite\build-win-x86-vc10.

        cd c:\any-lite
        md build-win-x86-vc10
        cd build-win-x86-vc10

2. Configure CMake to use the compiler of your choice (run `cmake --help` for a list).

        cmake -G "Visual Studio 10 2010" ..

3. Build the test suite in the Debug configuration (alternatively use Release).    

        cmake --build . --config Debug

4. Run the test suite.    

        ctest -V -C Debug

All tests should pass, indicating your platform is supported and you are ready to use *any lite*.


Other implementations of any
----------------------------
- Kevlin Henney. [Boost.Any](http://www.boost.org/doc/libs/1_62_0/doc/html/any.html). Safe, generic container for single values of different value types. 2001.
 

Notes and References
--------------------
[1] CppReference. [Any](http://en.cppreference.com/w/cpp/utility/any).  

[2] ISO/IEC WG21. [N4606, section 20.8 Storage for any type](http://wg21.link/n4606). July 2016.

[3] Beman Dawes and Kevlin Henney. [N3508: Any Library Proposal (Revision 2)](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3508.html). January 2013.

[4] Kevlin Henney. [Boost.Any](http://www.boost.org/doc/libs/1_62_0/doc/html/any.html). Safe, generic container for single values of different value types. 2001.

[5] Kevlin Henney. [Valued Conversions](http://www.two-sdg.demon.co.uk/curbralan/papers/ValuedConversions.pdf) (PDF). C++ report, July, August 2000.

[6] Kevlin Henney. [Substitutability. Principles, Idioms and Techniques for C++](http://www.two-sdg.demon.co.uk/curbralan/papers/accu/Substitutability.pdf#page=60) (PDF). Presented at JaCC, Oxford, 16th September 1999.

[7] Kevlin Henney. [Idioms. Breaking the Language Barrier](http://www.two-sdg.demon.co.uk/curbralan/papers/accu/Idioms.pdf#page=32) (PDF). Presented at the ACCU's C and C++ European Developers Forum, the Oxford Union, Oxford, UK, 12th September 1998.


Appendix
--------
### A.1 Any Lite test specification

```
any: Allows to default construct any
any: Allows to copy-construct from any
any: Allows to move-construct from any (C++11)
any: Allows to copy-construct from literal value
any: Allows to copy-construct from value
any: Allows to move-construct from value (C++11)
any: Allows to in-place construct from literal value (C++11)
any: Allows to in-place copy-construct from value (C++11)
any: Allows to in-place move-construct from value (C++11)
any: Allows to in-place copy-construct from initializer-list (C++11)
any: Allows to in-place move-construct from initializer-list (C++11)
any: Allows to copy-assign from any
any: Allows to move-assign from any (C++11)
any: Allows to copy-assign from literal value
any: Allows to copy-assign from value
any: Allows to move-assign from value (C++11)
any: Allows to copy-emplace content (C++11)
any: Allows to move-emplace content (C++11)
any: Allows to copy-emplace content from intializer-list (C++11)
any: Allows to move-emplace content from intializer-list (C++11)
any: Allows to reset content
any: Allows to swap with other any (member)
any: Allows to inspect if any contains a value
any: Allows to obtain type_info of any's content
swap: Allows to swap with other any (non-member)
make_any: Allows to in-place copy-construct any from arguments via make_any() (C++11)
make_any: Allows to in-place move-construct any from arguments via make_any() (C++11)
make_any: Allows to in-place copy-construct any from initializer-list via make_any() (C++11)
make_any: Allows to in-place move-construct any from initializer-list via make_any() (C++11)
any_cast: Allows to obtain any's content by value (any const &)
any_cast: Allows to obtain any's content by value (any &)
any_cast: Allows to obtain any's content by value (any &&)
any_cast: Allows to obtain any's content by pointer (any const *)
any_cast: Allows to obtain any's content by pointer (any *)
any_cast: Throws bad_any_cast if requested type differs from content type (any const &)
any_cast: Throws bad_any_cast if requested type differs from content type (any &)
any_cast: Throws bad_any_cast if requested type differs from content type (any &&)
```
