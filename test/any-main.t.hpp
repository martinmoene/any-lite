// Copyright (c) 2016 Martin Moene
//
// https://github.com/martinmoene/any-lite
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#ifndef TEST_ANY_LITE_H_INCLUDED
#define TEST_ANY_LITE_H_INCLUDED

#include "any.hpp"
#include "lest_cpp03.hpp"

using namespace nonstd;

#define CASE( name ) lest_CASE( specification(), name )

extern lest::tests & specification();

namespace nonstd {

// use oparator<< instead of to_string() overload;
// see  http://stackoverflow.com/a/10651752/437272

inline std::ostream & operator<<( std::ostream & os, nonstd::any const & /*v*/ )
{
    return os << "[any:]";
}

}

namespace lest {

using ::nonstd::operator<<;

} // namespace lest

#endif // TEST_ANY_LITE_H_INCLUDED

// end of file
