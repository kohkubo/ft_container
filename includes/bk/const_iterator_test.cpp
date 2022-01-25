// Copyright 2022 kohkubo

#include <iostream>
#include <vector>

#include "vector.hpp"

#define FT ft

int main() {
  int             array[] = {1, 2, 3, 4, 5};
  FT::vector<int> v(array, array + 5);
  std::cout << "v.size() = " << v.size() << std::endl;
  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;

  // // test erase
  // std::cout << "========== erase ===========" << std::endl;
  // FT::vector<int>::iterator it = v.begin();
  // std::cout << "v.erase(it)" << std::endl;
  // FT::vector<int>::iterator it2 = v.erase(it);
  // std::cout << "v.size() = " << v.size() << std::endl;
  // std::cout << "it2 = " << *it2 << std::endl;
  // std::cout << "v.erase(it2)" << std::endl;
  // FT::vector<int>::iterator it3 = v.erase(it2);
  // std::cout << "v.size() = " << v.size() << std::endl;
  // std::cout << "it3 = " << *it3 << std::endl;

  // for (size_t i = 0; i < v.size(); ++i) {
  //   std::cout << v[i] << " ";
  // }
  // std::cout << std::endl;
  // // test insert
  // std::cout << "========== insert ===========" << std::endl;
  // FT::vector<int> v2(array, array + 5);
  // std::cout << "v2.insert(v2.begin(), 10)" << std::endl;
  // FT::vector<int>::iterator it4 = v2.insert(v2.begin(), 10);
  // for (size_t i = 0; i < v2.size(); ++i) {
  //   std::cout << v2[i] << " ";
  // }
  // std::cout << std::endl;
  // std::cout << "it4 = " << *it4 << std::endl;
  // std::cout << "v2.insert(v2.begin() + 1, 20)" << std::endl;
  // FT::vector<int>::iterator it5 = v2.insert(v2.begin() + 1, 20);
  // for (size_t i = 0; i < v2.size(); ++i) {
  //   std::cout << v2[i] << " ";
  // }
  // std::cout << std::endl;
  // std::cout << "it5 = " << *it5 << std::endl;
  // std::cout << "v2.insert(v2.end(), 5, 30)" << std::endl;
  // FT::vector<int>::iterator it6 = v2.insert(v2.end(), 5, 30);
  // for (size_t i = 0; i < v2.size(); ++i) {
  //   std::cout << v2[i] << " ";
  // }
  // std::cout << std::endl;
  // std::cout << "it6 = " << *it6 << std::endl;
  // FT::vector<int> v3(array, array + 5);
  // std::cout << "v2.insert(v2.end(), v3.begin(), v3.end())" << std::endl;
  // FT::vector<int>::iterator it7 =
  //     v2.insert(v2.end(), v3.begin(), v3.end());
  // for (size_t i = 0; i < v3.size(); ++i) {
  //   std::cout << v3[i] << " ";
  // }
  // std::cout << std::endl;
  // std::cout << "it7 = " << *it7 << std::endl;
  return 0;
}
