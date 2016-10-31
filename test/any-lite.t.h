// Copyright (c) 2016 Martin Moene
//
// https://github.com/martinmoene/any-lite
//
// This code is licensed under the MIT License (MIT).

#pragma once

#ifndef TEST_ANY_LITE_H_INCLUDED
#define TEST_ANY_LITE_H_INCLUDED

#include "any.hpp"
#include "lest_cpp03.hpp"

using namespace nonstd;

#define CASE( name ) lest_CASE( specification(), name )

extern lest::tests & specification();

namespace nonstd { namespace any_lite {

// use oparator<< instead of to_string() overload;
// see  http://stackoverflow.com/a/10651752/437272

inline std::ostream & operator<<( std::ostream & os, nonstd::any_lite::any const & v )
{
    os << "[any:";
    return os << "]";
}

}}

namespace lest {

using ::nonstd::any_lite::operator<<;

} // namespace lest

#endif // TEST_ANY_LITE_H_INCLUDED

// end of file
