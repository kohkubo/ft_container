#include <iostream>
#include <vector>

#include "type_traits.hpp"

#define EXPECT_EQ(a, b)                                                     \
  do {                                                                      \
    if ((a) != (b)) {                                                       \
      std::cout << "Expected: " << (a) << " but got: " << (b) << std::endl; \
    }                                                                       \
  } while (0)

typedef void (*test_func_type)();
typedef std::vector<test_func_type> test_func_vec_type;
test_func_vec_type                  test_functions;

namespace ft {
namespace test {

bool MakeAndRegisterTestInfo(test_func_type func);

}  // namespace test
}  // namespace ft

#define GEN_TEST_CLASS_NAME(test_suite_name, test_name) \
  test_suite_name##_##test_name##_##TEST

#define GEN_TEST_FUNCTION_NAME(test_suite_name, test_name) \
  test_suite_name##_##test_name##_##test_func

#define TEST(test_suite_name, test_name)                                                                    \
  /* このクラスは使わない。値をセット時に関数が呼べる仕様を使いたいだけ */ \
  class GEN_TEST_CLASS_NAME(test_suite_name, test_name) {                                                   \
   private:                                                                                                 \
    static const bool tmp_;                                                                                 \
  };                                                                                                        \
  void       GEN_TEST_FUNCTION_NAME(test_suite_name, test_name)();                                          \
  const bool GEN_TEST_CLASS_NAME(test_suite_name, test_name)::tmp_ =                                        \
      ft::test::MakeAndRegisterTestInfo(                                                                    \
          GEN_TEST_FUNCTION_NAME(test_suite_name, test_name));                                              \
  void GEN_TEST_FUNCTION_NAME(test_suite_name, test_name)()

namespace ft {
namespace test {

bool MakeAndRegisterTestInfo(test_func_type func) {
  test_functions.push_back(func);
  return true;
}

}  // namespace test
}  // namespace ft

TEST(EnableIfTest, true_type) {
  ft::enable_if<true, int>::type test = 1;
  EXPECT_EQ(1, test);
}

// TEST_F(EnableIfTest, false_type) {
//     ft::enable_if<false, int>::type test = 1;
//     EXPECT_EQ(0, test);
// }

int main() {
  typedef test_func_vec_type::iterator test_func_vec_iterator;

  std::cout << "Test Start!!" << std::endl;
  std::cout << "Test count: " << test_functions.size() << std::endl;

  for (test_func_vec_iterator it = test_functions.begin();
       it != test_functions.end(); ++it) {
    (*it)();
  }
  std::cout << "Test finished!!" << std::endl;
}
