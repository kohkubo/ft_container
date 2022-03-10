#if __cplusplus >= 201103L
#include <gtest/gtest.h>
#else
#include "ft_test.hpp"
#endif

#include <memory>

#include "vector.hpp"

#ifndef LIB
# define LIB ft
#endif

TEST(Vector, Constructor) {
  // vector();
  LIB::vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_EQ(v.empty(), true);
  EXPECT_EQ(v.begin(), v.end());
  EXPECT_EQ(v.rbegin(), v.rend());
  for (int i = 0; i < 10; ++i) {
    v.push_back(i);
  }
  EXPECT_EQ(v.size(), 10);
  EXPECT_EQ(v.empty(), false);

  // explicit vector( const Allocator& alloc );
  LIB::vector<int> v2((std::allocator<int>()));
  EXPECT_EQ(v2.size(), 0);
  EXPECT_EQ(v2.capacity(), 0);
  EXPECT_EQ(v2.empty(), true);
  for (int i = 0; i < 10; ++i) {
    v2.push_back(i);
  }
  EXPECT_EQ(v2.size(), 10);
  EXPECT_EQ(v2.empty(), false);

  // explicit vector(size_type n, const T& value = T(), const Allocator& a =
  // Allocator());
  LIB::vector<int> v3(10, 0, (std::allocator<int>()));
  EXPECT_EQ(v3.size(), 10);
  EXPECT_EQ(v3.capacity(), 10);
  EXPECT_EQ(v3.empty(), false);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(v3[i], 0);
  }

  // template< class InputIt >
  // vector( InputIt first, InputIt last, const Allocator& alloc = Allocator()
  // );
  LIB::vector<int> v4(v3.begin(), v3.end(), (std::allocator<int>()));
  EXPECT_EQ(v4.size(), 10);
  EXPECT_EQ(v4.empty(), false);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(v4[i], 0);
  }

  // vector( const vector& other );
  LIB::vector<int> v5(v4);
  EXPECT_EQ(v5.size(), 10);
  EXPECT_EQ(v5.capacity(), 10);
  EXPECT_EQ(v5.empty(), false);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(v5[i], 0);
  }
}

// operator=( const vector& other );
TEST(Vector, OperatorAssign) {
  LIB::vector<int> v1(10, 0);
  LIB::vector<int> v2(v1);
  EXPECT_EQ(v2.size(), 10);
  EXPECT_EQ(v2.capacity(), 10);
  EXPECT_EQ(v2.empty(), false);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(v2[i], 0);
  }

  LIB::vector<int> v3(10, 0);
  v3 = v2;
  EXPECT_EQ(v3.size(), 10);
  EXPECT_EQ(v3.capacity(), 10);
  EXPECT_EQ(v3.empty(), false);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(v3[i], 0);
  }
}

// assign
TEST(Vector, Assign) {
  // assign( size_type n, const T& value );
  LIB::vector<int> v1(10, 0);
  v1.assign(10, 100);
  EXPECT_EQ(v1.size(), 10);
  EXPECT_EQ(v1.empty(), false);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(v1[i], 100);
  }

  // assign( InputIt first, InputIt last );
  LIB::vector<int> v3;
  v3.assign(v1.begin(), v1.end());
  EXPECT_EQ(v3.size(), 10);
  EXPECT_EQ(v3.empty(), false);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(v3[i], 100);
  }
}

// access
TEST(Vector, Access) {
  LIB::vector<int> v1;
  for (int i = 0; i < 10; ++i) {
    v1.push_back(i);
  }
  // at
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(v1.at(i), i);
  }
  // operator[]
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(v1[i], i);
    v1[i] = 100 * i;
  }
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(v1[i], 100 * i);
  }
  // front
  EXPECT_EQ(v1.front(), 0);
  // back
  EXPECT_EQ(v1.back(), 900);
}

// iterators
TEST(Vector, Iterators) {
  LIB::vector<int> v1;
  for (int i = 0; i < 10; ++i) {
    v1.push_back(i);
  }
  // begin
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(*(v1.begin() + i), i);
  }
  // end
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(*(v1.end() - i - 1), 9 - i);
  }
  // rbegin
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(*(v1.rbegin() + i), 9 - i);
  }
  // rend
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(*(v1.rend() - i - 1), i);
  }
}

// capacity
TEST(Vector, Capacity) {
  LIB::vector<int> v1;
  for (int i = 0; i < 10; ++i) {
    v1.push_back(i);
  }
  // empty
  EXPECT_EQ(v1.empty(), false);
  // size
  EXPECT_EQ(v1.size(), 10);
  // reserve
  v1.reserve(100);
  EXPECT_EQ(v1.capacity(), 100);
}

// modifiers
TEST(Vector, Modifiers) {
  LIB::vector<int> v1;
  for (int i = 0; i < 10; ++i) {
    v1.push_back(i);
  }
  // pop_back
  v1.pop_back();
  EXPECT_EQ(v1.size(), 9);
  EXPECT_EQ(v1.back(), 8);
  // push_back
  v1.push_back(100);
  EXPECT_EQ(v1.size(), 10);
  EXPECT_EQ(v1.back(), 100);
  // swap
  LIB::vector<int> v2;
  for (int i = 0; i < 20; ++i) {
    v2.push_back(i * 100);
  }
  v2.swap(v1);
  EXPECT_EQ(v1.size(), 20);
  EXPECT_EQ(v1.back(), 1900);

  // insert
  // iterator insert( iterator pos, const T& value );
  for (int i = 0; i < 10; ++i) {
    LIB::vector<int>::iterator it = v1.insert(v1.begin() + i, i);
    EXPECT_EQ(*it, i);
  }
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(v1[i], i);
  }
  // void insert( iterator pos, size_type n, const T& value );
  v1.insert(v1.begin() + 5, 10, 100);
  for (int i = 5; i < 15; ++i) {
    EXPECT_EQ(v1[i], 100);
  }
  // void insert( iterator pos, InputIt first, InputIt last );
  LIB::vector<int> v3;
  v3.insert(v3.begin(), v1.begin(), v1.end());
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(v3[i], v1[i]);
  }
  // resize
  v1.resize(10, 0);
  EXPECT_EQ(v1.size(), 10);
  EXPECT_EQ(v1.front(), 0);
  EXPECT_EQ(v1.back(), 100);

  v1.resize(20, 1000);
  EXPECT_EQ(v1.size(), 20);
  EXPECT_EQ(v1.front(), 0);
  EXPECT_EQ(v1.back(), 1000);

  // clear
  v1.clear();
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v1.empty(), true);

  LIB::vector<int> v4;
  for (int i = 0; i < 10; ++i) {
    v4.push_back(i);
  }
  // erase
  // iterator erase( iterator pos );
  // erase begin
  LIB::vector<int>::iterator it = v4.erase(v4.begin());
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(v4.size(), 9);
  EXPECT_EQ(v4.front(), 1);
  for (int i = 0; i < 9; ++i) {
    EXPECT_EQ(v4[i], i + 1);
  }
  // erase end
  v4.erase(--v4.end());
  EXPECT_EQ(v4.size(), 8);
  for (int i = 0; i < 8; ++i) {
    EXPECT_EQ(v4[i], i + 1);
  }
  // erase mid
  v4.erase(v4.begin() + 3);
  EXPECT_EQ(v4.size(), 7);
  for (int i = 0; i < 7; ++i) {
    if (i < 3) {
      EXPECT_EQ(v4[i], i + 1);
    } else {
      EXPECT_EQ(v4[i], i + 2);
    }
  }
  v4.push_back(100);
  EXPECT_EQ(v4.size(), 8);
  EXPECT_EQ(v4.back(), 100);
  // erase range
  // iterator erase( iterator first, iterator last );
  LIB::vector<int> v5;
  for (int i = 0; i < 10; ++i) {
    v5.push_back(i);
  }
  v5.erase(v5.begin() + 3, v5.begin() + 6);
  EXPECT_EQ(v5.size(), 7);
  for (int i = 0; i < 7; ++i) {
    if (i < 3) {
      EXPECT_EQ(v5[i], i);
    } else {
      EXPECT_EQ(v5[i], i + 3);
    }
  }
}

// non-member functions
TEST(Vector, NonMemberFunctions) {
  LIB::vector<int> v1;
  LIB::vector<int> v2;
  for (int i = 0; i < 10; ++i) {
    v1.push_back(i);
    v2.push_back(i);
  }
  // operator==
  EXPECT_EQ(v1 == v2, true);
  v2.pop_back();
  // v1 0 1 2 3 4 5 6 7 8 9
  // v2 0 1 2 3 4 5 6 7 8
  EXPECT_EQ(v1 == v2, false);

  // operator!=
  EXPECT_EQ(v1 != v2, true);
  v1.pop_back();
  // v1 0 1 2 3 4 5 6 7 8
  // v2 0 1 2 3 4 5 6 7 8
  EXPECT_EQ(v1 != v2, false);
  // operator<
  LIB::vector<int> v3;
  for (int i = 0; i < 9; ++i) {
    v3.push_back(i * 2);
  }
  // v1 0 1 2 3 4  5  6  7  8
  // v3 0 2 4 6 8 10 12 14 16
  EXPECT_EQ(v1 < v3, true);
  EXPECT_EQ(v1 < v2, false);
  // operator>
  EXPECT_EQ(v1 > v3, false);
  EXPECT_EQ(v1 > v2, false);
  // operator<=
  EXPECT_EQ(v1 <= v3, true);
  EXPECT_EQ(v1 <= v2, true);
  // operator>=
  EXPECT_EQ(v1 >= v3, false);
  EXPECT_EQ(v1 >= v2, true);
  v2.pop_back();
  // v1 0 1 2 3 4  5  6  7  8
  // v2 0 1 2 3 4  5  6  7
  EXPECT_EQ(v1 <= v2, false);

  // swap
  swap(v1, v2);
  EXPECT_EQ(v1 <= v2, true);
}

// type
TEST(Vector, Type) {
  LIB::vector<char> v_char;
  LIB::vector<int> v_int;
  LIB::vector<float> v_float;
  LIB::vector<double> v_double;
  LIB::vector<std::string> v_string;

  // char
  v_char.push_back('a');
  v_char.push_back('b');
  v_char.push_back('c');
  v_char.push_back('d');
  EXPECT_EQ(v_char.size(), 4);
  EXPECT_EQ(v_char.front(), 'a');
  EXPECT_EQ(v_char.back(), 'd');
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(v_char[i], 'a' + i);
  }
  // int
  v_int.push_back(1);
  v_int.push_back(2);
  v_int.push_back(3);
  v_int.push_back(4);
  EXPECT_EQ(v_int.size(), 4);
  EXPECT_EQ(v_int.front(), 1);
  EXPECT_EQ(v_int.back(), 4);
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(v_int[i], 1 + i);
  }
  // float
  v_float.push_back(1.0f);
  v_float.push_back(2.0f);
  v_float.push_back(3.0f);
  v_float.push_back(4.0f);
  EXPECT_EQ(v_float.size(), 4);
  EXPECT_EQ(v_float.front(), 1.0f);
  EXPECT_EQ(v_float.back(), 4.0f);
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(v_float[i], 1.0f + i);
  }
  // double
  v_double.push_back(1.0);
  v_double.push_back(2.0);
  v_double.push_back(3.0);
  v_double.push_back(4.0);
  EXPECT_EQ(v_double.size(), 4);
  EXPECT_EQ(v_double.front(), 1.0);
  EXPECT_EQ(v_double.back(), 4.0);
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(v_double[i], 1.0 + i);
  }
  // string
  v_string.push_back("a");
  v_string.push_back("b");
  v_string.push_back("c");
  v_string.push_back("d");
  EXPECT_EQ(v_string.size(), 4);
  EXPECT_EQ(v_string.front(), "a");
  EXPECT_EQ(v_string.back(), "d");
  EXPECT_EQ(v_string[0], "a");
  EXPECT_EQ(v_string[1], "b");
  EXPECT_EQ(v_string[2], "c");
  EXPECT_EQ(v_string[3], "d");
}


void print_vector(const LIB::vector<int>& v) {
  for (size_t i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}

#include <sstream>

TEST(Vector, insert) {
  size_t size = 4194304;
  // random access_iterator
  LIB::vector<int> v1;
  LIB::vector<int> v2;
  for (size_t i = 0; i < size; ++i) {
    v2.push_back((int)i);
  }
  v1.insert(v1.begin(), v2.begin(), v2.end());
  EXPECT_EQ(v1.size(), size);
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(v1[i], (int)i);
  }
  // input iterator
  std::stringstream ss;
  for (size_t i = 0; i < size; ++i) {
    ss << i << " ";
  }
  std::istream_iterator<int> istream_iter(ss);
  std::istream_iterator<int> istream_iter_end;

  LIB::vector<int>            v;
  // begin
  v.insert(v.begin(), istream_iter, istream_iter_end);
  EXPECT_EQ(v.size(), size);
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(v[i], (int)i);
  }
   // end
  std::stringstream ss2;
  for (size_t i = 0; i < size; ++i) {
    ss2 << i + size << " ";
  }
  std::istream_iterator<int> istream_iter2(ss2);
  std::istream_iterator<int> istream_iter_end2;

  v.insert(v.end(), istream_iter2, istream_iter_end2);
  EXPECT_EQ(v.size(), size * 2);
  for (size_t i = 0; i < size * 2; ++i) {
    EXPECT_EQ(v[i], (int)i);
  }
}

TEST(Vector, other) {
  size_t size = 10;
  size_t base_size = 10;
  LIB::vector<int> v3(base_size);
  std::stringstream ss3;
  for (size_t i = 0; i < size; ++i) {
    ss3 << i << " ";
  }
  std::istream_iterator<int> ii(ss3);
  std::istream_iterator<int> eos;
  v3.insert(v3.begin(), ii, eos);
  EXPECT_EQ(v3.size(), size + base_size);
  for (size_t i = 0; i < base_size; ++i) {
    EXPECT_EQ(v3[i], (int)i);
  }
  print_vector(v3);
  std::stringstream ss4;
  for (size_t i = 0; i < size; ++i) {
    ss4 << i << " ";
  }
  std::istream_iterator<int> ii2(ss4);
  std::istream_iterator<int> eos2;
  LIB::vector<int> v4(ii2, eos2);
  EXPECT_EQ(v4.size(), size);
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(v4[i], (int)i);
  }
}

TEST(Vector, insert2) {
  size_t size = 10;
  LIB::vector<int> v1(size);
  v1.insert(v1.begin(), size, 1);
  v1.insert(v1.end(), size, 2);
  EXPECT_EQ(v1.size(), size * 3);
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(v1[i], 1);
  }
}

TEST(Vector, insert3) {
  size_t size = 10;
  LIB::vector<int> v1((int)size);
  v1.insert(v1.begin(), 1);
  v1.insert(v1.end(), 1);
  EXPECT_EQ(v1.size(), size + 2);
  print_vector(v1);
}

TEST(Vector, insert4) {
  int size = 10;
  LIB::vector<int> v1(size);
  LIB::vector<int> v2;
  v2.insert(v2.begin(), size, 1);
  v1.insert(v1.begin(), v2.begin(), v2.end());
  print_vector(v1);
}