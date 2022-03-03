#if __cplusplus >= 201103L
#include <gtest/gtest.h>
#else
#include "ft_test.hpp"
#endif

#include <stack>
#include "stack.hpp"

#ifndef LIB
# define LIB ft
#endif

TEST(Stack, Constructor) {
  // stack();
  LIB::stack<int> s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_EQ(s.empty(), true);
  for (int i = 0; i < 10; ++i) {
    s.push(i);
  }
  EXPECT_EQ(s.size(), 10);
  EXPECT_EQ(s.empty(), false);
  EXPECT_EQ(s.top(), 9);

  LIB::stack<int, std::vector<int> > s2;
  EXPECT_EQ(s2.size(), 0);
  EXPECT_EQ(s2.empty(), true);
  for (int i = 0; i < 10; ++i) {
    s2.push(i);
  }
  EXPECT_EQ(s2.size(), 10);
  EXPECT_EQ(s2.empty(), false);
  EXPECT_EQ(s2.top(), 9);

  // stack( const stack& other );
  LIB::stack<int, std::vector<int> > s3(s2);
  EXPECT_EQ(s3.size(), 10);
  EXPECT_EQ(s3.empty(), false);
  EXPECT_EQ(s3.top(), 9);

  // operator=( const stack& other );
  LIB::stack<int> s4;
  s4 = s;
  EXPECT_EQ(s4.size(), 10);
  EXPECT_EQ(s4.empty(), false);
  EXPECT_EQ(s4.top(), 9);
  for (int i = 9; i >= 0; i--) {
    EXPECT_EQ(s4.top(), i);
    s4.pop();
  }
  EXPECT_EQ(s4.size(), 0);
  EXPECT_EQ(s4.empty(), true);

  // swap
  for (int i = 0; i < 10; ++i) {
    s4.push(i);
  }
  LIB::stack<int> s5;
  s5.swap(s4);
  EXPECT_EQ(s5.size(), 10);
  EXPECT_EQ(s5.empty(), false);
  EXPECT_EQ(s5.top(), 9);
  for (int i = 9; i >= 0; i--) {
    EXPECT_EQ(s5.top(), i);
    s5.pop();
  }
  EXPECT_EQ(s5.size(), 0);
  EXPECT_EQ(s5.empty(), true);
  EXPECT_EQ(s4.size(), 0);
  EXPECT_EQ(s4.empty(), true);
}

// non-member functions
TEST(Stack, NonMemberFunction)
{
  LIB::stack<int> s;
  LIB::stack<int> s2;
  LIB::stack<int> s3;
  for (int i = 0; i < 10; ++i) {
    s.push(i);
    s2.push(i);
    s3.push(i * 2);
  }
  // operator==
  EXPECT_EQ(s == s2, true);
  EXPECT_EQ(s == s3, false);
  // operator!=
  EXPECT_EQ(s != s2, false);
  EXPECT_EQ(s != s3, true);
  // operator<
  EXPECT_EQ(s < s2, false);
  EXPECT_EQ(s < s3, true);
  // operator>
  EXPECT_EQ(s > s2, false);
  EXPECT_EQ(s > s3, false);
  // operator<=
  EXPECT_EQ(s <= s2, true);
  EXPECT_EQ(s <= s3, true);
  // operator>=
  EXPECT_EQ(s >= s2, true);
  EXPECT_EQ(s >= s3, false);

  // swap
  LIB::swap(s, s3);
  EXPECT_EQ(s == s3, false);
  EXPECT_EQ(s3 == s, false);
  EXPECT_EQ(s == s2, false);
  EXPECT_EQ(s2 == s, false);
}
