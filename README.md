# any-lite: A single-file header-only version of a C++17-like any, a type-safe container for single values of any type for C++98, C++11 and later

[![Language](https://img.shields.io/badge/C%2B%2B-98/11/14/17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status](https://github.com/martinmoene/any-lite/actions/workflows/ci.yml/badge.svg)](https://github.com/martinmoene/any-lite/actions/workflows/ci.yml) [![Build status](https://ci.appveyor.com/api/projects/status/gpmw4gt271itoy2n?svg=true)](https://ci.appveyor.com/project/martinmoene/any-lite) [![Version](https://badge.fury.io/gh/martinmoene%2Fany-lite.svg)](https://github.com/martinmoene/any-lite/releases) [![download](https://img.shields.io/badge/latest-download-blue.svg)](https://raw.githubusercontent.com/martinmoene/any-lite/master/include/nonstd/any.hpp) [![Conan](https://img.shields.io/badge/on-conan-blue.svg)](https://conan.io/center/any-lite) [![Try it online](https://img.shields.io/badge/on-wandbox-blue.svg)](https://wandbox.org/permlink/GzoTkzwF7t5ncDg0) [![Try it on godbolt online](https://img.shields.io/badge/on-godbolt-blue.svg)](https://godbolt.org/z/2KN7Vx)

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

## Example usage

```Cpp
#include "nonstd/any.hpp"

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

```Text
prompt> g++ -Wall -I../include -o 01-basic 01-basic.cpp && 01-basic
```

## In a nutshell

**any lite** is a single-file header-only library to represent a type-safe container for single values of any type. The library aims to provide a [C++17-like any](http://en.cppreference.com/w/cpp/utility/any) for use with C++98 and later. If available, std::any is used.

**Features and properties of any lite** are ease of installation (single header), freedom of dependencies other than the standard library. *any lite* shares the approach to in-place tags with [expected-lite](https://github.com/martinmoene/expected-lite), [optional-lite](https://github.com/martinmoene/optional-lite) and with [variant-lite](https://github.com/martinmoene/variant-lite) and these libraries can be used together.

**Limitations of any lite** are the absence of small-object optimization: all contained objects are dynamically allocated. Move construction, move assignment and emplacement require C++11 and are not supported when compiling under C++98.


## License

*any lite* is distributed under the [Boost Software License](https://github.com/martinmoene/any-lite/blob/master/LICENSE.txt).

## Dependencies

*any lite* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).

## Installation

*any lite* is a single-file header-only library. Put `any.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.

## Synopsis

**Contents**  
- [Types in namespace nonstd](#types-in-namespace-nonstd)  
- [Interface of *any lite*](#interface-of-any-lite)  
- [Algorithms for *any lite*](#algorithms-for-any-lite)  
- [Configuration](#configuration)

### Types and values in namespace nonstd

| Purpose               | Type / value | Notes |
|-----------------------|--------------|-------|
| Type-safe container   | class **any**                        | &nbsp; |
| Error reporting       | class **bad_any_cast**               | &nbsp; |
| In-place construction | struct **in_place_tag**              | &nbsp; |
| &nbsp;                | **in_place**                         | select type or index for in-place construction |
| &nbsp;                | **in_place_type**                    | select type for in-place construction |
| &emsp;(variant)       | **in_place_index**                   | select index for in-place construction |
| &nbsp;                | **nonstd_lite_in_place_type_t**( T)  | macro for alias template in_place_type_t&lt;T>  |
| &emsp;(variant)       | **nonstd_lite_in_place_index_t**( T )| macro for alias template in_place_index_t&lt;T> |

### Interface of *any lite*

| Kind         | Std  | Method                                       | Result |
|--------------|------|----------------------------------------------|--------|
| Construction |&nbsp;| **any**()                                        | default-construct             |
| &nbsp;       |&nbsp;| **any**( any const & rhs )                       | copy-construct from other any |
| &nbsp;       | C++11| **any**( any && rhs ) noexcept                   | move-construct from other any |
| &nbsp;       | C++11| template< class ValueType ><br>**any**( ValueType && value ) noexcept | move-assign from value |
| &nbsp;       | C++11| template< class T ><br>explicit **any**( in_place_type_t&lt;T>, Args&&... args ) | in-place-construct type T |
| &nbsp;       | C++11| template< class T, class U, class... Args ><br>explicit **any**( in_place_type_t&lt;T>, std::initializer_list&lt;U> il, Args&&... args ) | in-place-construct type T |
| &nbsp;       |<C++11| template< class ValueType ><br>**any**( ValueType const & value ) | copy-assign from value |
| &nbsp;       |&nbsp;| ~**any**() | destroy current object |
| Assignment   |&nbsp;| any & **operator=**( any const & rhs ) | copy-assign from other |
| &nbsp;       | C++11| any & **operator=**( any && rhs ) noexcept | move-assign from other |
| &nbsp;       | C++11| template< class ValueType, ...><br>any & **operator=**( ValueType && rhs ) | (move-)assign from value |
| &nbsp;       |<C++11| template< class ValueType ><br>any & **operator=**( ValueType const & rhs ) | copy-assign from value |
| Modifiers    | C++11| template< class T, class... Args ><br>void **emplace**( Args && ... args ) | emplace type T |
| &nbsp;       | C++11| template< class T, class U, class... Args ><br>void **emplace**( std::initializer_list&lt;U> il, Args&&... args ) | emplace type T |
| &nbsp;       |&nbsp;| void **reset**() noexcept | destroy contained object |
| &nbsp;       |&nbsp;| void **swap**( any & rhs ) noexcept | exchange with other any |
| Observers    |&nbsp;| bool **has_value**() const noexcept | contains an object |
| &nbsp;       |&nbsp;| const std::type_info & **type**() const noexcept | Type of contained object |

### Algorithms for *any lite*

| Kind                      | Std  | Function | Result |
|---------------------------|------|----------|--------|
| Create                    |C++11 | template< class T, class ...Args ><br>any **make_any**( Args&& ...args ) | in-place construct |
| &nbsp;                    |C++11 | template< class T, class U, class ...Args ><br>any **make_any**( std::initializer_list&lt;U> il, Args&& ...args ) | in-place construct |
| Access                    |&nbsp;| T **any_cast&lt;T>**( any const & )  | obtained value |
| &nbsp;                    |&nbsp;| T **any_cast&lt;T>**( any & )        | obtained value |
| &nbsp;                    |C++11 | T **any_cast&lt;T>**( any && )       | obtained value |
| &nbsp;                    |&nbsp;| T const \* **any_cast&lt;T>**( any const * )  | pointer to obtained value |
| &nbsp;                    |&nbsp;| T \* **any_cast&lt;T>**( any * )     | pointer to obtained value |
| Swap                      |&nbsp;| void **swap**( any & x, any & y ) | exchange contents |

### Configuration

#### Tweak header

If the compiler supports [`__has_include()`](https://en.cppreference.com/w/cpp/preprocessor/include), *any lite* supports the [tweak header](https://vector-of-bool.github.io/2020/10/04/lib-configuration.html) mechanism. Provide your *tweak header* as `nonstd/any.tweak.hpp` in a folder in the include-search-path. In the tweak header, provide definitions as documented below, like `#define any_CPLUSPLUS 201103L`.
#### Standard selection macro

\-D<b>any\_CPLUSPLUS</b>=199711L  
Define this macro to override the auto-detection of the supported C++ standard, if your compiler does not set the `__cpluplus` macro correctly.

#### Select `std::any` or `nonstd::any`

At default, *any lite* uses `std::any` if it is available and lets you use it via namespace `nonstd`. You can however override this default and explicitly request to use `std::any` or any lite's `nonstd::any` as `nonstd::any` via the following macros.

-D<b>any\_CONFIG\_SELECT\_ANY</b>=any_ANY_DEFAULT  
Define this to `any_ANY_STD` to select `std::any` as `nonstd::any`. Define this to `any_ANY_NONSTD` to select `nonstd::any` as `nonstd::any`. Default is undefined, which has the same effect as defining to `any_ANY_DEFAULT`.

#### Disable exceptions

-D<b>any_CONFIG_NO_EXCEPTIONS</b>=0
Define this to 1 if you want to compile without exceptions. If not defined, the header tries and detect if exceptions have been disabled (e.g. via `-fno-exceptions`). Default is undefined.

## Reported to work with

The table below mentions the compiler versions *any lite* is reported to work with.

OS        | Compiler   | Versions |
---------:|:-----------|:---------|
Windows   | Clang/LLVM | ? |
&nbsp;    | GCC        | 5.2.0 |
&nbsp;    | Visual C++<br>(Visual Studio)| 8 (2005), 10 (2010), 11 (2012),<br>12 (2013), 14 (2015) |
GNU/Linux | Clang/LLVM | 3.5.0 |
&nbsp;    | GCC        | 4.8.4 |
OS X      | ?          | ?   |

## Building the tests

To build the tests you need:

- [Buck](https://buckbuild.com/) or [CMake](http://cmake.org) version 2.8.12 or later to be installed and in your PATH.
- A [suitable compiler](#reported-to-work-with).

The [*lest* test framework](https://github.com/martinmoene/lest)  is included in the [test folder](test).

The following steps assume that the [*any lite* source code](https://github.com/martinmoene/any-lite) has been cloned into a directory named `c:\any-lite`.

### Buck

```Text
any-lite> buck run test/
```

### CMake

1. Create a directory for the build outputs for a particular architecture.
Here we use c:\any-lite\build-win-x86-vc10.

        ~> cd c:\any-lite
        any-lite> md build-win-x86-vc10
        any-lite> cd build-win-x86-vc10

2. Configure CMake to use the compiler of your choice (run `cmake --help` for a list).

        any-lite\build> cmake -G "Visual Studio 10 2010" ..

3. Build the test suite in the Debug configuration (alternatively use Release).    

        any-lite\build> cmake --build . --config Debug

4. Run the test suite.    

        any-lite\build> ctest -V -C Debug

All tests should pass, indicating your platform is supported and you are ready to use *any lite*.

## Other implementations of any

- Isabella Muerte. [MNMLSTC Core](https://github.com/mnmlstc/core) (C++11).
- Kevlin Henney. [Boost.Any](http://www.boost.org/doc/libs/1_62_0/doc/html/any.html). Safe, generic container for single values of different value types. 2001.

## Notes and References

[1] CppReference. [Any](http://en.cppreference.com/w/cpp/utility/any).  

[2] ISO/IEC WG21. [N4606, section 20.8 Storage for any type](http://wg21.link/n4606). July 2016.

[3] Beman Dawes and Kevlin Henney. [N3508: Any Library Proposal (Revision 2)](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3508.html). January 2013.

[4] Kevlin Henney. [Boost.Any](http://www.boost.org/doc/libs/1_62_0/doc/html/any.html). Safe, generic container for single values of different value types. 2001.

[5] Kevlin Henney. [Valued Conversions](http://www.two-sdg.demon.co.uk/curbralan/papers/ValuedConversions.pdf) (PDF). C++ report, July, August 2000.

[6] Kevlin Henney. [Substitutability. Principles, Idioms and Techniques for C++](http://www.two-sdg.demon.co.uk/curbralan/papers/accu/Substitutability.pdf#page=60) (PDF). Presented at JaCC, Oxford, 16th September 1999.

[7] Kevlin Henney. [Idioms. Breaking the Language Barrier](http://www.two-sdg.demon.co.uk/curbralan/papers/accu/Idioms.pdf#page=32) (PDF). Presented at the ACCU's C and C++ European Developers Forum, the Oxford Union, Oxford, UK, 12th September 1998.

## Appendix

### A.1 Compile-time information

The version of *any lite* is available via tag `[.version]`. The following tags are available for information on the compiler and on the C++ standard library used: `[.compiler]`, `[.stdc++]`, `[.stdlanguage]` and `[.stdlibrary]`.

### A.2 Any lite test specification

```Text
any: Allows to default construct any
any: Allows to copy-construct from any
any: Allows to move-construct from any (C++11)
any: Allows to copy-construct from literal value
any: Allows to copy-construct from const value
any: Allows to copy-construct from lvalue references
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
make_any: Allows to in-place copy-construct any from arguments (C++11)
make_any: Allows to in-place move-construct any from arguments (C++11)
make_any: Allows to in-place copy-construct any from initializer-list and arguments (C++11)
make_any: Allows to in-place move-construct any from initializer-list and arguments (C++11)
any_cast: Allows to obtain any's content by value (any const &)
any_cast: Allows to obtain any's content by value (any &)
any_cast: Allows to obtain any's content by value (any &&)
any_cast: Allows to obtain any's content by pointer (any const *)
any_cast: Allows to obtain any's content by pointer (any *)
any_cast: Throws bad_any_cast if requested type differs from content type (any const &)
any_cast: Throws bad_any_cast if requested type differs from content type (any &)
any_cast: Throws bad_any_cast if requested type differs from content type (any &&)
any_cast: Throws bad_any_cast with non-empty what()
tweak header: reads tweak header if supported [tweak]
```
