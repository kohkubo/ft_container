// Copyright (c) 2022 kohkubo

#include <iostream>
#include <type_traits>
#include <vector>

#include "vector_func.hpp"
#include "iterator.hpp"
#include "random_access_iterator.hpp"
#include "type_traits.hpp"

int main() {
  // std::cout << std::is_convertible<int, int>::value << std::endl;
  // std::cout << std::is_convertible<int, int>::value << std::endl;
  // std::cout << std::is_convertible<long, double>::value << std::endl;
  // std::cout << std::is_convertible<long, double>::value << std::endl;
  // std::cout << std::is_convertible<int, double>::value << std::endl;
  // std::cout << std::is_convertible<int *, double *>::value << std::endl;
  // std::cout << ft::is_convertible<int *, double *>::value << std::endl;
  // std::cout << std::is_convertible<int, const int>::value << std::endl;
  // std::cout << ft::is_convertible<int, const int>::value << std::endl;

  // std::cout << ft::is_input_iterator<std::vector<int>::iterator>::value
  //           << std::endl;
  // std::cout << ft::has_iterator_category<std::vector<int>::iterator>::value
  //           << std::endl;
  // std::cout << ft::has_iterator_category_is_convertible<
  //     std::vector<int>::iterator, std::input_iterator_tag>::value
  //           << std::endl;
  // std::cout << ft::is_input_iterator<ft::vector<int>::iterator>::value
  //           << std::endl;
  int array[] = {1, 2, 3, 4, 5};
  std::vector<int> v(array, array + 5);
  std::cout << std::distance(v.begin(), v.end()) << std::endl;

  ft::vector<int> ft_v;
  std::cout << ft_v.size() << std::endl;
  for (int i = 0; i < 5; ++i) {
    ft_v.push_back(i);
  }
  ft::vector<int> v3(ft_v.begin(), ft_v.end());

  ft::vector<int> v4(ft_v);
  std::cout << v4.size() << std::endl;

  ft::vector<int> v5(v.begin(), v.end());
  std::cout << v5.size() << std::endl;
  return 0;
}
