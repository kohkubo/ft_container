#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP
#include "integral_constant.hpp"

namespace ft
{
template <class T>
struct is_integral : public ft::false_type {};
template <class T>
struct is_integral<const T> : public is_integral<T> {};
template <class T>
struct is_integral<volatile T> : public is_integral<T> {};
template <class T>
struct is_integral<const volatile T> : public is_integral<T> {};
template<> struct is_integral<unsigned char> : public true_type {};
template<> struct is_integral<unsigned short> : public true_type{};
template<> struct is_integral<unsigned int> : public true_type{};
template<> struct is_integral<unsigned long> : public true_type{};
template<> struct is_integral<unsigned long long> : public true_type{};
template<> struct is_integral<signed char> : public true_type{};
template<> struct is_integral<char> : public true_type{};
template<> struct is_integral<short> : public true_type{};
template<> struct is_integral<int> : public true_type{};
template<> struct is_integral<long> : public true_type{};
template<> struct is_integral<long long> : public true_type{};
template<> struct is_integral<wchar_t> : public true_type{};

}  // namespace ft


#endif
