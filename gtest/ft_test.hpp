/*
This program is a modified version of "testlib" by JUNNETWORKS, which can be found at the link below.
https://github.com/JUNNETWORKS/42-ft_containers/tree/main/test/testlib
*/

#ifndef GTEST_FT_TEST_HPP_
#define GTEST_FT_TEST_HPP_

#include <cassert>
#include <string>
#include <vector>

typedef void (*test_func_type)();
typedef std::pair<std::string, test_func_type> test_func_pair_type;
typedef std::vector<test_func_pair_type> test_func_vec_type;

extern test_func_vec_type test_functions;

namespace ft {
namespace test {

// TEST()
bool MakeAndRegisterTestInfo(std::string test_name, test_func_type func);

}  // namespace test
}  // namespace ft

/********** TEST登録マクロ **********/

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define GEN_TEST_CLASS_NAME(test_suite_name, test_name) \
  test_suite_name##_##test_name##_##TEST

#define GEN_TEST_FUNCTION_NAME(test_suite_name, test_name) \
  test_suite_name##_##test_name##_##test_func

#define TEST(test_suite_name, test_name)                                                                    \
  class GEN_TEST_CLASS_NAME(test_suite_name, test_name) {                                                   \
   private:                                                                                                 \
    static const bool tmp_;                                                                                 \
  };                                                                                                        \
  void GEN_TEST_FUNCTION_NAME(test_suite_name, test_name)();                                                \
  const bool GEN_TEST_CLASS_NAME(test_suite_name, test_name)::tmp_ =                                        \
      ft::test::MakeAndRegisterTestInfo(                                                                    \
          STR(GEN_TEST_FUNCTION_NAME(test_suite_name, test_name)),                                          \
          GEN_TEST_FUNCTION_NAME(test_suite_name, test_name));                                              \
  void GEN_TEST_FUNCTION_NAME(test_suite_name, test_name)()

/********** EXPECT **********/

#define EXPECT_EQ(arg1, arg2) \
  { assert((arg1) == (arg2)); }

#endif  // GTEST_FT_TEST_HPP_
