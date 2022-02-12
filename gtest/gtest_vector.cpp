#include <gtest/gtest.h>

#include <memory>

#include "vector.hpp"

#ifndef LIB
#define LIB ft
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
  EXPECT_EQ(v4.capacity(), 10);
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
// 一旦ここまで
