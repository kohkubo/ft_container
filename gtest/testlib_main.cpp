#include <iostream>
#include <vector>
#include <random>

#include "ft_test.hpp"

test_func_vec_type test_functions;

#include "gtest_map.cpp"
#include "gtest_set.cpp"
#include "gtest_stack.cpp"
#include "gtest_vector.cpp"

namespace ft {
namespace test {

bool MakeAndRegisterTestInfo(std::string test_name, test_func_type func) {
  test_functions.push_back(test_func_pair_type(test_name, func));
  return true;
}
}  // namespace test
}  // namespace ft

int main() {
  typedef test_func_vec_type::iterator test_func_vec_iterator;

  std::cout << "Test Start!!" << std::endl;
  std::cout << "Test count: " << test_functions.size() << std::endl;

  for (test_func_vec_iterator it = test_functions.begin();
       it != test_functions.end(); ++it) {
    std::string    test_func_name = (*it).first;
    test_func_type test_func      = (*it).second;

    std::cout << "RUN:     " << test_func_name << std::endl;
    test_func();
    std::cout << "SUCCESS: " << test_func_name << "\n" << std::endl;
  }
  std::cout << "Test Finished!!" << std::endl;
  std::cout << "All tests succeeded." << std::endl;
}