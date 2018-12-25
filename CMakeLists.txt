# Copyright 2018 by Martin Moene
#
# https://github.com/martinmoene/any-lite
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required( VERSION 3.5 )

# any-lite project and version, updated by script/update-version.py:

project(
    any_lite
    VERSION 0.1.0
#   DESCRIPTION "A C++17-like any, a type-safe container for single values of any type for C++98, C++11 and later in a single-file header-only library"
#   HOMEPAGE_URL "https://github.com/martinmoene/any-lite"
    LANGUAGES CXX )

message( STATUS "${PROJECT_NAME} version: '${${PROJECT_NAME}_VERSION}'")

# Toplevel or subproject:

if ( CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME )
    set( any_IS_TOPLEVEL_PROJECT TRUE )
else()
    set( any_IS_TOPLEVEL_PROJECT FALSE )
endif()

# If toplevel project, enable building and performing of tests, disable building of examples:

option( ANY_LITE_OPT_BUILD_TESTS    "Build and perform any-lite tests" ${any_IS_TOPLEVEL_PROJECT} )
option( ANY_LITE_OPT_BUILD_EXAMPLES "Build any-lite examples" OFF )

option( ANY_LITE_OPT_SELECT_STD      "Select std::any"    OFF )
option( ANY_LITE_OPT_SELECT_NONSTD   "Select nonstd::any" OFF )

include( GNUInstallDirs )

set( package_name "any-lite" )
set( include_source_dir "${PROJECT_SOURCE_DIR}/include" )

# Interface library:

add_library(
    ${package_name} INTERFACE )

target_include_directories(
    ${package_name} INTERFACE "$<BUILD_INTERFACE:${include_source_dir}>" )

# Installation:

install(
    DIRECTORY   ${CMAKE_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

# If requested, build and perform tests, build examples:

enable_testing()

if ( ANY_LITE_OPT_BUILD_TESTS )
    add_subdirectory( test )
endif()

if ( ANY_LITE_OPT_BUILD_EXAMPLES )
    add_subdirectory( example )
endif()

# end of file
