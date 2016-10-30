# any-lite: A single-file header-only version of a C++17-like any, a type-safe container for single values of any type for C++98, C++11 and later

Features:

- Can be used together with [variant-lite](https://github.com/martinmoene/variant-lite) (and later with [optional-lite](https://github.com/martinmoene/optional-lite)).

Current limitations:

- Objects are always allocated dynamically, i.e. there's no small-object optimization for types T for which std::is_nothrow_move_constructible_v<T> is true.

