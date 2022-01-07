#ifndef INTEGRAL_CONSTANT_HPP
#define INTEGRAL_CONSTANT_HPP

namespace ft
{
template <class T, T v>
struct integral_constant {
    typedef T                       value_type;
    static const T                  value = v;
    typedef integral_constant<T, v> type;
};

template <class T, T v>
T const integral_constant<T, v>::value;

template <bool v>
struct integral_constant<bool, v> {
    typedef bool                       value_type;
    static const bool                  value = v;
    typedef integral_constant<bool, v> type;
};

template <bool v>
bool const integral_constant<bool, v>::value;

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
    typedef T type;
};
}  // namespace ft

#endif
