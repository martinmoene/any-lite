//
// Copyright (c) 2016 Martin Moene
//
// https://github.com/martinmoene/any-lite
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#ifndef NONSTD_ANY_LITE_HPP
#define NONSTD_ANY_LITE_HPP

#define  any_lite_VERSION "0.1.0"

// any-lite configuration:

// any-lite alignment configuration:

// Compiler detection:

#define any_CPP11_OR_GREATER  ( __cplusplus >= 201103L )
#define any_CPP14_OR_GREATER  ( __cplusplus >= 201402L )
#define any_CPP17_OR_GREATER  ( __cplusplus >= 201703L )

// use C++17 std::any if available:

#if defined( __has_include )
# define any_HAS_INCLUDE( arg )  __has_include( arg )
#else
# define any_HAS_INCLUDE( arg )  0
#endif

#if any_HAS_INCLUDE( <any> ) && any_CPP17_OR_GREATER

#define any_HAVE_STD_ANY  1

#include <any>

namespace nonstd {

    using std::any;
    using std::any_cast;
    using std::make_any;
    using std::swap;
    using std::bad_any_cast;

    using std::in_place;
    using std::in_place_type;
    using std::in_place_t;
    using std::in_place_type_t;
};

#else // C++17 std::any

#include <typeinfo>
#include <utility>

// half-open range [lo..hi):
#define any_BETWEEN( v, lo, hi ) ( lo <= v && v < hi )

#if defined(_MSC_VER) && !defined(__clang__)
# define any_COMPILER_MSVC_VERSION   (_MSC_VER / 100 - 5 - (_MSC_VER < 1900))
#else
# define any_COMPILER_MSVC_VERSION   0
#endif

#if defined __GNUC__
# define any_COMPILER_GNUC_VERSION  __GNUC__
#else
# define any_COMPILER_GNUC_VERSION    0
#endif

// Presence of C++11 language features:

#if any_CPP11_OR_GREATER || any_COMPILER_MSVC_VERSION >= 10
# define any_HAVE_NULLPTR  1
#endif

#if any_CPP11_OR_GREATER || any_COMPILER_MSVC_VERSION >= 12
# define any_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG  1
# define any_HAVE_INITIALIZER_LIST  1
#endif

#if any_CPP11_OR_GREATER || any_COMPILER_MSVC_VERSION >= 14
# define any_HAVE_CONSTEXPR_11  1
# define any_HAVE_NOEXCEPT  1
#endif

// Presence of C++14 language features:

#if any_CPP14_OR_GREATER
# define any_HAVE_CONSTEXPR_14  1
#endif

// Presence of C++17 language features:

// Presence of C++ library features:

#if any_COMPILER_GNUC_VERSION
# define any_HAVE_TR1_TYPE_TRAITS  1
# define any_HAVE_TR1_ADD_CONST  1
# define any_HAVE_TR1_REMOVE_REFERENCE  1
#endif

#if any_CPP11_OR_GREATER || any_COMPILER_MSVC_VERSION >= 9
# define any_HAVE_TYPE_TRAITS  1
# define any_HAVE_STD_ADD_CONST  1
# define any_HAVE_STD_REMOVE_REFERENCE  1
#endif

// For the rest, consider VC14 as C++11 for any-lite:

#if any_COMPILER_MSVC_VERSION >= 14
# undef  any_CPP11_OR_GREATER
# define any_CPP11_OR_GREATER  1
#endif

// C++ feature usage:

#if any_HAVE_CONSTEXPR_11
# define any_constexpr constexpr
#else
# define any_constexpr /*constexpr*/
#endif

#if any_HAVE_CONSTEXPR_14
# define any_constexpr14 constexpr
#else
# define any_constexpr14 /*constexpr*/
#endif

#if any_HAVE_NOEXCEPT
# define any_noexcept noexcept
#else
# define any_noexcept /*noexcept*/
#endif

#if any_HAVE_NULLPTR
# define any_nullptr nullptr
#else
# define any_nullptr NULL
#endif

// additional includes:

#if ! any_HAVE_NULLPTR
# include <cstddef>
#endif

#if any_HAVE_INITIALIZER_LIST
# include <initializer_list>
#endif

#if any_HAVE_TYPE_TRAITS
# include <type_traits>
#elif any_HAVE_TR1_TYPE_TRAITS
# include <tr1/type_traits>
#endif

//
// in_place: code duplicated in any-lite, optional-lite, variant-lite:
//

#if ! nonstd_lite_HAVE_IN_PLACE_TYPES

namespace nonstd {

namespace detail {

template< class T >
struct in_place_type_tag {};

template< std::size_t I >
struct in_place_index_tag {};

} // namespace detail

struct in_place_t {};

template< class T >
inline in_place_t in_place( detail::in_place_type_tag<T> = detail::in_place_type_tag<T>() )
{
    return in_place_t();
}

template< std::size_t I >
inline in_place_t in_place( detail::in_place_index_tag<I> = detail::in_place_index_tag<I>() )
{
    return in_place_t();
}

template< class T >
inline in_place_t in_place_type( detail::in_place_type_tag<T> = detail::in_place_type_tag<T>() )
{
    return in_place_t();
}

template< std::size_t I >
inline in_place_t in_place_index( detail::in_place_index_tag<I> = detail::in_place_index_tag<I>() )
{
    return in_place_t();
}

// mimic templated typedef:

#define nonstd_lite_in_place_type_t( T)  nonstd::in_place_t(&)( nonstd::detail::in_place_type_tag<T>  )
#define nonstd_lite_in_place_index_t(T)  nonstd::in_place_t(&)( nonstd::detail::in_place_index_tag<I> )

#define nonstd_lite_HAVE_IN_PLACE_TYPES  1

} // namespace nonstd

#endif // nonstd_lite_HAVE_IN_PLACE_TYPES

//
// any:
//

namespace nonstd {  namespace any_lite {

namespace detail {

// C++11 emulation:

#if any_HAVE_STD_ADD_CONST

using std::add_const;

#elif any_HAVE_TR1_ADD_CONST

using std::tr1::add_const;

#else

template< class T > struct add_const { typedef const T type; };

#endif // any_HAVE_ADD_CONST

#if any_HAVE_STD_REMOVE_REFERENCE

using std::remove_reference;

#elif any_HAVE_TR1_REMOVE_REFERENCE

using std::tr1::remove_reference;

#else

template< class T > struct remove_reference     { typedef T type; };
template< class T > struct remove_reference<T&> { typedef T type; };

#endif // any_HAVE_STD_REMOVE_REFERENCE

} // namespace detail

class bad_any_cast : public std::bad_cast
{
public:
#if any_CPP11_OR_GREATER
    virtual const char* what() const any_noexcept
#else
    virtual const char* what() const throw()
#endif
   {
      return "any-lite: bad any_cast";
   }
};

class any
{
public:
    any_constexpr any() any_noexcept
    : content( any_nullptr )
    {}

    any( any const & rhs )
    : content( rhs.content ? rhs.content->clone() : any_nullptr )
    {}

#if any_CPP11_OR_GREATER

    any( any && rhs ) any_noexcept
    : content( std::move( rhs.content ) )
    {
        rhs.content = any_nullptr;
    }

    template< class ValueType, class T = typename std::decay<ValueType>::type, typename = typename std::enable_if< ! std::is_same<T, any>::value >::type >
    any( ValueType && value ) any_noexcept
    : content( new holder<T>( std::move( value ) ) )
    {}

    template< class T, class... Args, typename = typename std::enable_if< std::is_constructible<T, Args...>::value >::type >
    explicit any( nonstd_lite_in_place_type_t(T), Args&&... args )
    : content( new holder<T>( T( std::forward<Args>(args)... ) ) )
    {}

    template< class T, class U, class... Args, typename = typename std::enable_if< std::is_constructible<T, std::initializer_list<U>&, Args...>::value >::type >
    explicit any( nonstd_lite_in_place_type_t(T), std::initializer_list<U> il, Args&&... args )
    : content( new holder<T>( T( il, std::forward<Args>(args)... ) ) )
    {}

#else

    template< class ValueType >
    any( ValueType const & value )
    : content( new holder<ValueType>( value ) )
    {}

#endif // any_CPP11_OR_GREATER

    ~any()
    {
        reset();
    }

    any & operator=( any const & rhs )
    {
        any( rhs ).swap( *this );
        return *this;
    }

#if any_CPP11_OR_GREATER

    any & operator=( any && rhs ) any_noexcept
    {
        any( std::move( rhs ) ).swap( *this );
        return *this;
    }

    template< class ValueType, class T = typename std::decay<ValueType>::type, typename = typename std::enable_if< ! std::is_same<T, any>::value >::type >
    any & operator=( ValueType && rhs )
    {
        any( std::move( rhs ) ).swap( *this );
        return *this;
    }

    template< class T, class... Args >
    void emplace( Args && ... args )
    {
        any( T( std::forward<Args>(args)... ) ).swap( *this );
    }

    template< class T, class U, class... Args, typename = typename std::enable_if< std::is_constructible<T, std::initializer_list<U>&, Args...>::value >::type >
    void emplace( std::initializer_list<U> il, Args&&... args )
    {
        any( T( il, std::forward<Args>(args)... ) ).swap( *this );
    }

#else

    template< class ValueType >
    any & operator=( ValueType const & rhs )
    {
        any( rhs ).swap( *this );
        return *this;
    }

#endif // any_CPP11_OR_GREATER

    void reset() any_noexcept
    {
        delete content; content = any_nullptr;
    }

    void swap( any & rhs ) any_noexcept
    {
        std::swap( content, rhs.content );
    }

    bool has_value() const any_noexcept
    {
        return content != any_nullptr;
    }

    const std::type_info & type() const any_noexcept
    {
        return has_value() ? content->type() : typeid( void );
    }

    //
    // non-standard:
    //

    template< class ValueType >
    const ValueType * to_ptr() const
    {
        return &( static_cast<holder<ValueType> *>( content )->held );
    }

    template< class ValueType >
    ValueType * to_ptr()
    {
        return &( static_cast<holder<ValueType> *>( content )->held );
    }

private:
    class placeholder
    {
    public:
        virtual ~placeholder()
        {
        }

        virtual std::type_info const & type() const = 0;

        virtual placeholder * clone() const = 0;
    };

    template< typename ValueType >
    class holder : public placeholder
    {
    public:
        holder( ValueType const & value )
        : held( value )
        {}

#if any_CPP11_OR_GREATER
        holder( ValueType && value )
        : held( std::move( value ) )
        {}
#endif

        virtual std::type_info const & type() const
        {
            return typeid( ValueType );
        }

        virtual placeholder * clone() const
        {
            return new holder( held );
        }

        ValueType held;
    };

    placeholder * content;
};

inline void swap( any & x, any & y ) any_noexcept
{
    x.swap( y );
}

#if any_CPP11_OR_GREATER

template< class T, class ...Args >
inline any make_any( Args&& ...args )
{
    return any( in_place<T>, std::forward<Args>(args)...);
}

template< class T, class U, class ...Args >
inline any make_any( std::initializer_list<U> il, Args&& ...args )
{
    return any( in_place<T>, il, std::forward<Args>(args)...);
}

#endif // any_CPP11_OR_GREATER

#if any_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG
template< class ValueType, typename = typename std::enable_if< std::is_reference<ValueType>::value || std::is_copy_constructible<ValueType>::value >::type >
#else
template< class ValueType >
#endif
inline ValueType any_cast( any const & operand )
{
   const ValueType * result = any_cast< typename detail::add_const< typename detail::remove_reference<ValueType>::type >::type >( &operand );

   if ( ! result )
   {
      throw bad_any_cast();
   }

   return *result;
}

#if any_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG
template< class ValueType, typename = typename std::enable_if< std::is_reference<ValueType>::value || std::is_copy_constructible<ValueType>::value >::type >
#else
template< class ValueType >
#endif
inline ValueType any_cast( any & operand )
{
   const ValueType * result = any_cast< typename detail::remove_reference<ValueType>::type >( &operand );

   if ( ! result )
   {
      throw bad_any_cast();
   }

   return *result;
}

#if any_CPP11_OR_GREATER

#if any_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG
template< class ValueType, typename = typename std::enable_if< std::is_reference<ValueType>::value || std::is_copy_constructible<ValueType>::value >::type >
#else
template< class ValueType >
#endif
inline ValueType any_cast( any && operand )
{
   const ValueType * result = any_cast< typename detail::remove_reference<ValueType>::type >( &operand );

   if ( ! result )
   {
      throw bad_any_cast();
   }

   return *result;
}

#endif // any_CPP11_OR_GREATER

template< class ValueType >
inline ValueType const * any_cast( any const * operand ) any_noexcept
{
    return operand != any_nullptr && operand->type() == typeid(ValueType) ? operand->to_ptr<ValueType>() : any_nullptr;
}

template<class ValueType >
inline ValueType * any_cast( any * operand ) any_noexcept
{
    return operand != any_nullptr && operand->type() == typeid(ValueType) ? operand->to_ptr<ValueType>() : any_nullptr;
}

} // namespace any_lite

using namespace any_lite;

} // namespace nonstd

#endif // have C++17 std::any

#endif // NONSTD_ANY_LITE_HPP
