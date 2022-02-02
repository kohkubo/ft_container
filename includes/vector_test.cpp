// Copyright (c) 2022 kohkubo

#include <iostream>
#include <vector>

#include "vector.hpp"

int main() {
  // std::vector<int> v(10);
  // v.insert(v.begin(), 1);
  // v.insert(v.begin(), 2);
  // v.insert(v.begin(), 3);
  // v.insert(v.begin(), 4);

  // std::cout << "v.size() = " << v.size() << std::endl;
  // std::cout << "v.max_size() = " << v.max_size() << std::endl;
  // std::cout << "v.capacity() = " << v.capacity() << std::endl;
  // std::cout << "v.empty() = " << v.empty() << std::endl;
  // std::cout << "v.begin() = " << *v.begin() << std::endl;

  // v.reserve(300);
  // std::cout << "v.size() = " << v.size() << std::endl;
  // std::cout << "v.max_size() = " << v.max_size() << std::endl;
  // std::cout << "v.capacity() = " << v.capacity() << std::endl;
  // std::cout << "v.empty() = " << v.empty() << std::endl;
  // std::cout << "v.begin() = " << *v.begin() << std::endl;
  // // // std::cout << "v.end() = " << *v.end() << std::endl;

  // std::cout << "========== allocate ===========" << std::endl;
  // int *p = std::allocator<int>().allocate(10);
  // for (int i = 0; i < 10; ++i)
  //     p[i] = i;
  // for (int i = 0; i < 10; ++i)
  //     std::cout << p[i] << " ";
  // std::cout << std::endl;
  // std::allocator<int>().deallocate(p, 10);

  // std::cout << "========== ft::vector ===========" << std::endl;
  // ft::vector<int> ft_v(10);
  // std::cout << "ft_v(10)" << std::endl;
  // std::cout << "ft_v.size() = " << ft_v.size() << std::endl;
  // std::cout << "ft_v.capacity() = " << ft_v.capacity() << std::endl;
  // std::cout << "ft_v.empty() = " << ft_v.empty() << std::endl;
  // std::cout << "ft_v.begin() = " << *ft_v.begin() << std::endl;
  // std::cout << "ft_v.end() = " << *ft_v.end() << std::endl;
  // std::cout << "ft_v.rbegin() = " << *ft_v.rbegin() << std::endl;

  // std::cout << "========== ft_v.push_back(1) ===========" << std::endl;
  // ft_v.push_back(100);
  // std::cout << "ft_v.push_back(100)" << std::endl;
  // ft_v.push_back(200);
  // std::cout << "ft_v.push_back(200)" << std::endl;
  // ft_v.push_back(300);
  // std::cout << "ft_v.push_back(300)" << std::endl;
  // for (size_t i = 0; i < ft_v.size(); ++i) std::cout << ft_v[i] << " ";
  // std::cout << std::endl;

  // std::cout << "ft_v.size() = " << ft_v.size() << std::endl;
  // std::cout << "ft_v.capacity() = " << ft_v.capacity() << std::endl;
  // std::cout << "ft_v.empty() = " << ft_v.empty() << std::endl;
  // std::cout << "ft_v.begin() = " << *ft_v.begin() << std::endl;
  // std::cout << "ft_v.end() = " << *--ft_v.end() << std::endl;

  // std::cout << "========== copy constructor ===========" << std::endl;
  // ft::vector<int> ft_v2(ft_v);
  // for (size_t i = 0; i < ft_v.size(); ++i) std::cout << ft_v[i] << " ";
  // std::cout << std::endl;
  // std::cout << "ft_v2.size() = " << ft_v2.size() << std::endl;
  // std::cout << "ft_v2.capacity() = " << ft_v2.capacity() << std::endl;
  // std::cout << "ft_v2.empty() = " << ft_v2.empty() << std::endl;
  // std::cout << "ft_v2.begin() = " << *ft_v2.begin() << std::endl;
  // std::cout << "ft_v2.end() = " << *--ft_v2.end() << std::endl;

  std::vector<int> std_v(10);
  std::cout << *std_v.begin().base() << std::endl;
  return 0;
}
