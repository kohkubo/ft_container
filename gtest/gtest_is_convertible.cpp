#include <gtest/gtest.h>

#include <type_traits>
#include <typeinfo>

#include "type_traits.hpp"

class IsConvertibleTest : public ::testing::Test {};

template <class From, class To>
void test_is_convertible() {
  bool ft  = ft::is_convertible<From, To>::value;
  bool std = std::is_convertible<From, To>::value;
  EXPECT_EQ(ft, std);
}

TEST_F(IsConvertibleTest, IsConvertibleTest_int) {
  test_is_convertible<int, int>();
  test_is_convertible<int, unsigned int>();
  test_is_convertible<int, unsigned long>();
  test_is_convertible<int, unsigned long long>();
  test_is_convertible<int, long>();
  test_is_convertible<int, long long>();
  test_is_convertible<int, char>();
  test_is_convertible<int, signed char>();
  test_is_convertible<int, unsigned char>();
  test_is_convertible<int, short>();
  test_is_convertible<int, unsigned short>();
  test_is_convertible<int, float>();
  test_is_convertible<int, double>();
  test_is_convertible<int, long double>();
  test_is_convertible<int, void*>();
  test_is_convertible<int, int*>();
//   test_is_convertible<int, int&>();
}

TEST_F(IsConvertibleTest, IsConvertibleTest_qualifiers) {
    test_is_convertible<const int, int>();
    test_is_convertible<const int, unsigned int>();
    test_is_convertible<const int, unsigned long>();
    test_is_convertible<const int, unsigned long long>();
    test_is_convertible<const int, long>();
    test_is_convertible<const int, long long>();
    test_is_convertible<const int, char>();
    test_is_convertible<const int, signed char>();
    test_is_convertible<const int, unsigned char>();
    test_is_convertible<const int, short>();
    test_is_convertible<const int, unsigned short>();
    test_is_convertible<const int, float>();
    test_is_convertible<const int, double>();
    test_is_convertible<const int, long double>();
    test_is_convertible<const int, void*>();
    test_is_convertible<const int, int*>();
    test_is_convertible<const int, int&>();

    test_is_convertible<volatile int, int>();
    test_is_convertible<volatile int, unsigned int>();
    test_is_convertible<volatile int, unsigned long>();
    test_is_convertible<volatile int, unsigned long long>();
    test_is_convertible<volatile int, long>();
    test_is_convertible<volatile int, long long>();
    test_is_convertible<volatile int, char>();
    test_is_convertible<volatile int, signed char>();
    test_is_convertible<volatile int, unsigned char>();
    test_is_convertible<volatile int, short>();
    test_is_convertible<volatile int, unsigned short>();
    test_is_convertible<volatile int, float>();
    test_is_convertible<volatile int, double>();
    test_is_convertible<volatile int, long double>();
    test_is_convertible<volatile int, void*>();
    test_is_convertible<volatile int, int*>();
    test_is_convertible<volatile int, int&>();
}
