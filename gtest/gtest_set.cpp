#if __cplusplus >= 201103L
#include <gtest/gtest.h>
#else
#include "ft_test.hpp"
#endif

#include <set>
#include <random>

#include "set.hpp"

#ifndef LIB
# define LIB ft
#endif

TEST(SetTest, Constructor) {
  // set();
  LIB::set<int> s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_EQ(s.empty(), true);
  EXPECT_EQ(s.begin(), s.end());
  EXPECT_EQ(s.rbegin(), s.rend());
  // explicit set( const Compare& comp, const Allocator& alloc = Allocator() );
  LIB::set<int> s2((std::less<int>()), (std::allocator<int>()));
  EXPECT_EQ(s2.size(), 0);
  EXPECT_EQ(s2.empty(), true);
  // template< class InputIt >
  // set( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() );
  LIB::set<int> s3(s2.begin(), s2.end(), (std::less<int>()),
                   (std::allocator<int>()));
  EXPECT_EQ(s3.size(), 0);
  EXPECT_EQ(s3.empty(), true);
  // set( const set& other );
  LIB::set<int> s4(s3);
  EXPECT_EQ(s4.size(), 0);
  EXPECT_EQ(s4.empty(), true);
  // operator=( const set& other );
  LIB::set<int> s5;
  LIB::set<int> s6(s3);
  s5 = s3;
  EXPECT_EQ(s5.size(), s6.size());
  EXPECT_EQ(s5.empty(), s6.empty());
  // get_allocator()
  EXPECT_EQ(s5.get_allocator(), s6.get_allocator());

  // key_comp()
  // value_comp()
  const LIB::set<int>::key_compare &kc = s5.key_comp();
  EXPECT_EQ(kc(1, 2), true);
  EXPECT_EQ(kc(2, 1), false);
  const LIB::set<int>::value_compare &vc = s5.value_comp();
  EXPECT_EQ(vc(1, 2), true);
  EXPECT_EQ(vc(2, 1), false);
}

TEST(Set, Iterator)
{
  LIB::set<int> s;
  for (int i = 0; i < 10; ++i) {
    s.insert(i);
  }
  LIB::set<int>::iterator it = s.begin();
  EXPECT_EQ(*it, 0);
  ++it;
  EXPECT_EQ(*it, 1);
  const LIB::set<int>& cs = s;
  LIB::set<int>::const_iterator cit = cs.begin();
  EXPECT_EQ(*cit, 0);
  ++cit;
  EXPECT_EQ(*cit, 1);

  // iterator end()
  it = s.end();
  --it;
  EXPECT_EQ(*it, 9);
  cit = cs.end();
  --cit;
  EXPECT_EQ(*cit, 9);

  // reverse_iterator rbegin()
  LIB::set<int>::reverse_iterator rit = s.rbegin();
  EXPECT_EQ(*rit, 9);
  ++rit;
  EXPECT_EQ(*rit, 8);
  LIB::set<int>::const_reverse_iterator crit = cs.rbegin();
  crit = cs.rbegin();
  EXPECT_EQ(*crit, 9);
  ++crit;
  EXPECT_EQ(*crit, 8);

  // reverse_iterator rend()
  rit = s.rend();
  --rit;
  EXPECT_EQ(*rit, 0);
  crit = cs.rend();
  --crit;
  EXPECT_EQ(*crit, 0);
}

// modifiers
#define SIZE 1000
TEST(Set, Modifiers)
{
  int random[SIZE] = {0};
  std::srand(std::time(0));
  LIB::set<int> s;
  for (int i = 0; i < SIZE; ++i) {
    int key = std::rand() % SIZE;
    LIB::pair<LIB::set<int>::iterator, bool> ret = s.insert(key);
    if (ret.second) {
      random[key] = key;
    }
  }
  // iterator insert( iterator hint, const value_type& value );
  int random2[SIZE] = {0};
  LIB::set<int, std::greater<int> > s2;
  LIB::set<int, std::greater<int> >::iterator it2 = s2.begin();
  for (int i = 0; i < SIZE; ++i) {
    int key = std::rand() % SIZE;
    it2 = s2.insert(it2, int(key));
    EXPECT_EQ(*it2, key);
    ++it2;
    random2[i] = key;
  }

  // iterator insert(InputIterator first, InputIterator last );
  LIB::set<int> s3;
  s3.insert(s.begin(), s.end());
  for (int i = 0; i < SIZE; ++i) {
    LIB::set<int>::iterator it3 = s3.find(i);
    LIB::set<int>::iterator it4 = s.find(i);
    if (it3 != s3.end()) {
      EXPECT_EQ(*it3, *it4);
    }
  }
  // void erase( iterator pos );
  LIB::set<int> s4;
  for (int i = 0; i < SIZE; ++i) {
    s4.insert(i);
  }
  for (int i = 0; i < SIZE; ++i) {
    LIB::set<int>::iterator it5 = s4.find(i);
    if (it5 != s4.end()) {
      s4.erase(it5);
    }
  }
  EXPECT_EQ(s4.size(), 0);
  EXPECT_EQ(s4.empty(), true);
  // void erase( iterator first, iterator last );
  LIB::set<int> s5;
  for (int i = 0; i < SIZE; ++i) {
    s5.insert(i);
  }
  s5.erase(s5.begin(), s5.end());
  EXPECT_EQ(s5.size(), 0);
  EXPECT_EQ(s5.empty(), true);

  // size_type erase( const key_type& key );
  LIB::set<int> s6;
  for (int i = 0; i < SIZE; ++i) {
    s6.insert(i);
  }
  size_t erase_size = s6.erase(0);
  EXPECT_EQ(s6.size(), SIZE - 1);
  EXPECT_EQ(erase_size, 1);

  // clear();
  s6.clear();
  EXPECT_EQ(s6.size(), 0);
  EXPECT_EQ(s6.empty(), true);

  // void swap( set& other );
  LIB::set<int> s7;
  for (int i = 0; i < SIZE; ++i) {
    s7.insert(i);
  }
  LIB::set<int> s8;
  for (int i = 0; i < SIZE; ++i) {
    s8.insert(i * 2);
  }
  s7.swap(s8);
  for (int i = 0; i < SIZE; ++i) {
    LIB::set<int>::iterator it7 = s7.find(i * 2);
    LIB::set<int>::iterator it8 = s8.find(i);
    if (it7 != s7.end()) {
      EXPECT_EQ(*it7, i * 2);
    }
    if (it8 != s8.end()) {
      EXPECT_EQ(*it8, i);
    }
  }
}

// lookup
TEST(Set, Lookup)
{
  LIB::set<int> s;
  for (int i = 0; i < 10; ++i) {
    s.insert(i);
  }
  LIB::set<int>::iterator it = s.find(5);
  EXPECT_EQ(*it, 5);
  LIB::set<int>::const_iterator cit = s.find(5);
  EXPECT_EQ(*cit, 5);
  LIB::set<int>::iterator it2 = s.find(15);
  EXPECT_EQ(it2, s.end());
  LIB::set<int>::const_iterator cit2 = s.find(15);
  EXPECT_EQ(cit2, s.end());

  // iterator equal_range( const key_type& key );
  for (int i = 0; i < 10; ++i) {
    LIB::pair<LIB::set<int>::iterator, LIB::set<int>::iterator> ret = s.equal_range(i);
    EXPECT_EQ(ret.first, s.lower_bound(i));
    EXPECT_EQ(ret.second, s.upper_bound(i));
  }
  EXPECT_EQ(s.count(5), 1);
}

// non-member functions
TEST(Set, NonMemberFunctions)
{
  LIB::set<int> s1;
  LIB::set<int> s2;
  LIB::set<int> s3;
  for (int i = 0; i < 10; ++i) {
    s1.insert(i);
    s2.insert(i);
    s3.insert(i * 2);
  }
  // bool operator==( const set& lhs, const set& rhs );
  EXPECT_EQ(s1 == s2, true);
  EXPECT_EQ(s1 == s3, false);
  // bool operator!=( const set& lhs, const set& rhs );
  EXPECT_EQ(s1 != s2, false);
  EXPECT_EQ(s1 != s3, true);
  // bool operator<( const set& lhs, const set& rhs );
  EXPECT_EQ(s1 < s2, false);
  EXPECT_EQ(s1 < s3, true);
  // bool operator<=( const set& lhs, const set& rhs );
  EXPECT_EQ(s1 <= s2, true);
  EXPECT_EQ(s1 <= s3, true);
  // bool operator>( const set& lhs, const set& rhs );
  EXPECT_EQ(s1 > s2, false);
  EXPECT_EQ(s1 > s3, false);
  // bool operator>=( const set& lhs, const set& rhs );
  EXPECT_EQ(s1 >= s2, true);
  EXPECT_EQ(s1 >= s3, false);
}