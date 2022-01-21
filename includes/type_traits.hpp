// Copyright (c) 2022 kohkubo

#ifndef INCLUDES_TYPE_TRAITS_HPP_
#define INCLUDES_TYPE_TRAITS_HPP_

#include <exception>
namespace ft {
template <class _Tp, _Tp __v>
struct integral_constant {
  static const _Tp          value = __v;
  typedef _Tp               value_type;
  typedef integral_constant type;
                            operator value_type() const { return value; }
};

template <class _Tp, _Tp __v>
const _Tp                              integral_constant<_Tp, __v>::value;

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

template <class T>
struct is_integral : public ft::false_type {};
template <class T>
struct is_integral<const T> : public is_integral<T> {};
template <class T>
struct is_integral<volatile T> : public is_integral<T> {};
template <class T>
struct is_integral<const volatile T> : public is_integral<T> {};

template <>
struct is_integral<unsigned char> : public true_type {};
template <>
struct is_integral<unsigned short> : public true_type {};
template <>
struct is_integral<unsigned int> : public true_type {};
template <>
struct is_integral<unsigned long> : public true_type {};
template <>
struct is_integral<unsigned long long> : public true_type {};
template <>
struct is_integral<signed char> : public true_type {};
template <>
struct is_integral<char> : public true_type {};
template <>
struct is_integral<short> : public true_type {};
template <>
struct is_integral<int> : public true_type {};
template <>
struct is_integral<long> : public true_type {};
template <>
struct is_integral<long long> : public true_type {};
template <>
struct is_integral<wchar_t> : public true_type {};

// =============================================================================
// enable_if
// =============================================================================
template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
  typedef T type;
};
// =============================================================================
// is_same
// =============================================================================
template <class T, class U>
struct is_same : public ft::false_type {};

template <class T>
struct is_same<T, T> : public ft::true_type {};
// =============================================================================
// is_convertible
// =============================================================================
typedef char yes_type;
struct no_type {
  char dummy[8];
};

template <class From, class To>
struct is_convertible {
  static From       val;
  static no_type    test(...);
  static yes_type   test(To);
  static bool const value = sizeof(test(val)) == sizeof(true_type);
};
}  // namespace ft
#endif  // INCLUDES_TYPE_TRAITS_HPP_
