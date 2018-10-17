# Copyright 2018 by Martin Moene
#
# https://github.com/martinmoene/any-lite
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.5 )

# any-lite version, updated by script/update-version.py:

set( any_lite_version "0.1.0" )

# At default, enable building and performing of tests and building of examples:

option( ANY_LITE_OPT_BUILD_TESTS    "Build and perform any-lite tests" OFF )
option( ANY_LITE_OPT_BUILD_EXAMPLES "Build any-lite examples" OFF )

option( ANY_LITE_OPT_SELECT_STD      "Select std::any"    OFF )
option( ANY_LITE_OPT_SELECT_NONSTD   "Select nonstd::any" OFF )

include( GNUInstallDirs )

project( any_lite LANGUAGES CXX )

set( package_name "any-lite" )

# Interface library:

add_library(
    ${package_name} INTERFACE )

target_include_directories(
    ${package_name} INTERFACE "$<BUILD_INTERFACE:${include_source_dir}>" )

# Installation:

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

# If requested, build and perform tests, build examples:

enable_testing()

if ( ANY_LITE_OPT_BUILD_TESTS )
    add_subdirectory( test )
endif()

if ( ANY_LITE_OPT_BUILD_EXAMPLES )
    add_subdirectory( example )
endif()

# end of file
