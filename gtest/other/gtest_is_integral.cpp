#include <gtest/gtest.h>
#include "type_traits.hpp"

template<class T>
void test_is_integral_true()
{
    EXPECT_TRUE((ft::is_integral<T>::value));
    EXPECT_TRUE((ft::is_integral<const T>::value));
    EXPECT_TRUE((ft::is_integral<volatile T>::value));
    EXPECT_TRUE((ft::is_integral<const volatile T>::value));
}

template<class T>
void test_is_integral_false()
{
    EXPECT_FALSE((ft::is_integral<T>::value));
    EXPECT_FALSE((ft::is_integral<const T>::value));
    EXPECT_FALSE((ft::is_integral<volatile T>::value));
    EXPECT_FALSE((ft::is_integral<const volatile T>::value));
}

TEST(IsIntegralTest, IntegralTypes)
{
    test_is_integral_true<unsigned char>();
    test_is_integral_true<unsigned short>();
    test_is_integral_true<unsigned int>();
    test_is_integral_true<unsigned long>();
    test_is_integral_true<unsigned long long>();
    test_is_integral_true<signed char>();
    test_is_integral_true<char>();
    test_is_integral_true<short>();
    test_is_integral_true<int>();
    test_is_integral_true<long>();
    test_is_integral_true<long long>();
    test_is_integral_true<wchar_t>();
}

TEST(IsIntegralTest, NonIntegralTypes)
{
    test_is_integral_false<double>();
    test_is_integral_false<float>();
    test_is_integral_false<long double>();
    test_is_integral_false<void>();
    test_is_integral_false<int*>();
    test_is_integral_false<int&>();
    test_is_integral_false<int&&>();
    test_is_integral_false<int[]>();
    test_is_integral_false<int[2]>();
    test_is_integral_false<int(*)()>();
    test_is_integral_false<int(&&)()>();
    test_is_integral_false<int(*)[2]>();
    test_is_integral_false<int(&&)[2]>();
    test_is_integral_false<int(*)[][2]>();
    test_is_integral_false<int(&&)[][2]>();
    test_is_integral_false<int(&)()>();
    test_is_integral_false<int(&)[2]>();
    test_is_integral_false<int(&)[][2]>();
}
