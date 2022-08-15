#if __cplusplus >= 201103L
#include <gtest/gtest.h>
#else
#include "ft_test.hpp"
#endif
#include <random>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include "map.hpp"
#include <map>

#ifndef LIB
#define LIB ft
#endif

TEST(Map, Constructor) {
  // map();
  LIB::map<int, int> m;
  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m.empty(), true);
  EXPECT_EQ(m.begin(), m.end());
  EXPECT_EQ(m.rbegin(), m.rend());
  for (int i = 0; i < 10; ++i) {
    m.insert(LIB::make_pair(i, i));
  }
  EXPECT_EQ(m.size(), 10);
  EXPECT_EQ(m.empty(), false);

  // explicit map( const Compare& comp, const Allocator& alloc = Allocator() );
  LIB::map<int, int> m2((std::less<int>()), (std::allocator<int>()));
  EXPECT_EQ(m2.size(), 0);
  EXPECT_EQ(m2.empty(), true);
  for (int i = 0; i < 10; ++i) {
    m2.insert(LIB::make_pair(i, i));
  }
  EXPECT_EQ(m2.size(), 10);
  EXPECT_EQ(m2.empty(), false);

  // template< class InputIt >
  // map( InputIt first, InputIt last, const Compare& comp = Compare(),
  // const Allocator& alloc = Allocator() );
  LIB::map<int, int> m3(m2.begin(), m2.end(), (std::less<int>()),
                        (std::allocator<int>()));
  EXPECT_EQ(m3.size(), 10);
  EXPECT_EQ(m3.empty(), false);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(m3[i], i);
  }
  EXPECT_EQ(m3.size(), 10);

  // map( const map& other );
  LIB::map<int, int> m4(m3);
  EXPECT_EQ(m4.size(), 10);
  EXPECT_EQ(m4.empty(), false);
  for (size_t i = 0; i < m4.size(); ++i) {
    EXPECT_EQ(m4[i], m3[i]);
  }
  EXPECT_EQ(m4.get_allocator(), m3.get_allocator());

  // operator=( const map& other );
  LIB::map<int, int> m5;
  LIB::map<int, int> m6(m3);
  m5 = m3;
  EXPECT_EQ(m5.size(), m6.size());
  EXPECT_EQ(m5.empty(), m6.empty());
  for (size_t i = 0; i < m5.size(); ++i) {
    EXPECT_EQ(m5[i], m6[i]);
  }
  EXPECT_EQ(m5.get_allocator(), m6.get_allocator());

  // key_comp();
  // value_comp();
  LIB::map<int,int>::key_compare comp = m5.key_comp();
  EXPECT_EQ(comp(1, 2), true);
  EXPECT_EQ(comp(2, 1), false);
  const LIB::map<int,int>::value_compare& comp2 = m5.value_comp();
  LIB::pair <int,int> p1(1, 2);
  LIB::pair <int,int> p2(2, 1);
  EXPECT_EQ(comp2(p1, p2), true);
  EXPECT_EQ(comp2(p2, p1), false);
}

// iterator
TEST(Map, Iterator) {
  LIB::map<int, int> m;
  for (int i = 0; i < 10; ++i) {
    m.insert(LIB::make_pair(i, i));
  }

  // iterator begin();
  // const_iterator begin() const;
  LIB::map<int, int>::iterator it = m.begin();
  EXPECT_EQ(it->first, 0);
  EXPECT_EQ(it->second, 0);
  LIB::map<int, int>::const_iterator cit = m.begin();
  EXPECT_EQ(cit->first, 0);
  EXPECT_EQ(cit->second, 0);

  // iterator end();
  // const_iterator end() const;
  it = m.end();
  --it;
  EXPECT_EQ(it->first, 9);
  EXPECT_EQ(it->second, 9);
  cit = m.end();
  --cit;
  EXPECT_EQ(cit->first, 9);
  EXPECT_EQ(cit->second, 9);

  // reverse_iterator rbegin();
  // const_reverse_iterator rbegin() const;
  const LIB::map<int, int> m2(m);
  LIB::map<int, int>::reverse_iterator rit = m.rbegin();
  EXPECT_EQ(rit->first, 9);
  EXPECT_EQ(rit->second, 9);
  LIB::map<int, int>::const_reverse_iterator crit = m2.rbegin();
  EXPECT_EQ(crit->first, 9);
  EXPECT_EQ(crit->second, 9);

  // reverse_iterator rend();
  // const_reverse_iterator rend() const;
  rit = m.rend();
  --rit;
  EXPECT_EQ(rit->first, 0);
  EXPECT_EQ(rit->second, 0);
  crit = m2.rend();
  --crit;
  EXPECT_EQ(crit->first, 0);
  EXPECT_EQ(crit->second, 0);
}

// modifiers
#define SIZE 1000
TEST(Map, Modifiers) {
  // LIB::pair<iterator, bool> insert( const value_type& value );
  int random[SIZE] = {0};
  srand(time(0));
  LIB::map<int, int> m;
  for (int i = 0; i < SIZE; ++i) {
    int key = std::rand() % SIZE;
    LIB::pair<LIB::map<int, int>::iterator, bool> ret =
        m.insert(LIB::make_pair(key, key));
    EXPECT_EQ(ret.first->first, key);
    if (ret.second == true) {
      random[i] = key;
    }
  }
  for (int i = 0; i < SIZE; ++i) {
    EXPECT_EQ(m[random[i]], random[i]);
  }
  std::sort(random, random + SIZE, std::greater<int>());
  LIB::map<int, int>::reverse_iterator it = m.rbegin();
  for (size_t i = 0; i < m.size(); ++i) {
    EXPECT_EQ(it->first, random[i]);
    ++it;
  }
  // iterator insert( iterator position, const value_type& value );
  int random2[SIZE] = {0};
  srand(time(0));
  LIB::map<int, int, std::greater<int> > m2;
  LIB::map<int, int>::iterator it2 = m2.begin();
  for (int i = 0; i < SIZE; ++i) {
    int key = std::rand() % SIZE;
    if (m2.find(key) != m2.end()) {
      it2 = m2.insert(it2, LIB::make_pair(key, key));
      EXPECT_EQ(it2->first, key);
      ++it2;
      random2[i] = key;
    }
  }
  sort(random2, random2 + SIZE, std::greater<int>());
  it2 = m2.begin();
  for (size_t i = 0; i < m2.size(); ++i) {
    EXPECT_EQ(it2->first, random2[i]);
    ++it2;
  }
  // LIB::pair<iterator, bool> insert( InputIterator first, InputIterator last );
  LIB::map<int, int> m3;
  m3.insert(m2.begin(), m2.end());
  for (int i = 0; i < SIZE; ++i) {
    EXPECT_EQ(m3[i], m2[i]);
  }

  // void erase( iterator pos );
  LIB::map<int, int> m4;
  for (int i = 0; i < SIZE; ++i) {
    m4.insert(LIB::make_pair(i, i));
  }
  for (int i = 0; i < SIZE; ++i) {
    m4.erase(m4.find(i));
  }
  EXPECT_EQ(m4.size(), 0);
  EXPECT_EQ(m4.empty(), true);
  for (int i = 0; i < SIZE; ++i) {
    m4.insert(LIB::make_pair(i, i));
  }
  LIB::map<int, int>::iterator it3 = m4.begin();
  for (int i = 0; i < SIZE; ++i) {
    EXPECT_EQ(it3->first, i);
    ++it3;
  }

  // void erase( iterator first, iterator last );
  LIB::map<int, int> m5;
  for (int i = 0; i < SIZE; ++i) {
    m5.insert(LIB::make_pair(i, i));
  }
  m5.erase(m5.begin(), m5.end());
  EXPECT_EQ(m5.size(), 0);
  EXPECT_EQ(m5.empty(), true);
  for (int i = 0; i < SIZE; ++i) {
    m5.insert(LIB::make_pair(i, i));
  }
  for (int i = 0; i < SIZE; ++i) {
    EXPECT_EQ(m5[i], i);
  }

  // size_type erase( const key_type& key );
  LIB::map<int, int> m6;
  for (int i = 0; i < SIZE; ++i) {
    m6.insert(LIB::make_pair(i, i));
  }
  size_t ret = m6.erase(0);
  EXPECT_EQ(ret, 1);
  EXPECT_EQ(m6.size(), SIZE - 1);
  EXPECT_EQ(m6.empty(), false);
  for (int i = 1; i < SIZE; ++i) {
    EXPECT_EQ(m6[i], i);
  }

  // swap
  LIB::map<int, int> m7;
  for (int i = 0; i < SIZE; ++i) {
    m7.insert(LIB::make_pair(i, i));
  }
  LIB::map<int, int> m8;
  for (int i = 0; i < SIZE; ++i) {
    m8.insert(LIB::make_pair(i * 2, i));
  }
  m7.swap(m8);
  EXPECT_EQ(m7.size(), SIZE);
  EXPECT_EQ(m7.empty(), false);
  for (int i = 0; i < SIZE; ++i) {
    EXPECT_EQ(m7[i * 2], i);
  }

  // void clear();
  LIB::map<int, int> m9;
  for (int i = 0; i < SIZE; ++i) {
    m9.insert(LIB::make_pair(i, i));
  }
  m9.clear();
  EXPECT_EQ(m9.size(), 0);
  EXPECT_EQ(m9.empty(), true);
}

// lookup
TEST(Map, Lookup) {
  int random[SIZE] = {0};
  srand(time(0));
  LIB::map<int, int> m;
  EXPECT_EQ(m.find(0) == m.end(), true);
  for (int i = 0; i < SIZE; ++i) {
    int key = std::rand() % SIZE;
    random[i] = key;
    m.insert(LIB::make_pair(key, key));
  }
  std::sort(random, random + SIZE, std::less<int>());
  // iterator find( const Key& key );
  for (int i = 0; i < SIZE; ++i) {
    EXPECT_EQ(m.find(random[i])->second, random[i]);
    // count
    EXPECT_EQ(m.count(random[i]), 1);
  }
  LIB::map<int, int> m2;
  for (int i = 0; i < 10; i++) {
    m2.insert(LIB::make_pair(i, i));
  }
  for (int i = 0; i < 10; i++) {
    LIB::pair<LIB::map<int, int>::iterator, LIB::map<int, int>::iterator> ret =
        m2.equal_range(i);
    EXPECT_EQ(ret.first, m2.lower_bound(i));
    EXPECT_EQ(ret.second, m2.upper_bound(i));
  }
}

// non-member functions
TEST(Map, NonMemberFunctions) {
  int random[SIZE] = {0};
  srand(time(0));
  LIB::map<int, int> m;
  for (int i = 0; i < SIZE; ++i) {
    int key = std::rand() % SIZE;
    random[i] = key;
    m.insert(LIB::make_pair(key, key));
  }
  std::sort(random, random + SIZE, std::less<int>());


  // void swap( Map& lhs, Map& rhs );
  LIB::map<int, int> m2;
  for (int i = 0; i < SIZE; i++) {
    m2.insert(LIB::make_pair(i, i));
  }

  LIB::map<int, int> m3;
  for (int i = 0; i < SIZE; i++) {
    m3.insert(LIB::make_pair(i, i * 2));
  }
  LIB::swap(m3, m2);
  for (int i = 0; i < SIZE; i++) {
    EXPECT_EQ(m2[i], i * 2);
  }
  for (int i = 0; i < SIZE; i++) {
    EXPECT_EQ(m3[i], i);
  }

  // bool operator==( const Map& lhs, const Map& rhs );
  LIB::map<int, int> m4;
  for (int i = 0; i < SIZE; i++) {
    m4.insert(LIB::make_pair(i, i));
  }
  LIB::map<int, int> m5;
  for (int i = 0; i < SIZE; i++) {
    m5.insert(LIB::make_pair(i, i));
  }
  EXPECT_EQ(m4 == m5, true);
  LIB::map<int, int> m6;
  for (int i = 0; i < SIZE; i++) {
    m6.insert(LIB::make_pair(i * 2, i * 2));
  }
  EXPECT_EQ(m4 == m6, false);
  EXPECT_EQ(m6 == m4, false);
  EXPECT_EQ(m4 != m6, true);
  EXPECT_EQ(m6 != m4, true);
  EXPECT_EQ(m4 < m6, true);
  EXPECT_EQ(m6 < m4, false);
  EXPECT_EQ(m4 > m6, false);
  EXPECT_EQ(m6 > m4, true);
  EXPECT_EQ(m4 <= m6, true);
  EXPECT_EQ(m6 <= m4, false);
  EXPECT_EQ(m4 >= m6, false);
  EXPECT_EQ(m6 >= m4, true);
}

TEST(Map, other) {
  LIB::map<int, int> m;
  m.insert(LIB::make_pair(1, 1));
  std::cout << "m  " << &*m.begin() << std::endl;

  LIB::map<int, int>::iterator it = m.begin();
  std::cout << it->first << " " << it->second << std::endl;
  std::cout << m.size() << std::endl;

  LIB::map<int, int> m2;
  m2.insert(LIB::make_pair(1, 1));
  std::cout << "m2 " << &*m2.begin() << std::endl;
  std::cout << "swap" << std::endl;
  swap(m, m2);
  std::cout << "m  " << &*m.begin() << std::endl;
  std::cout << "m2 " << &*m2.begin() << std::endl;
}

TEST(Map, other2) {
  LIB::map<int, int> m;
  m.insert(LIB::make_pair(1, 1));
  std::cout << "first " << &*m.begin() << std::endl;

  m.insert(LIB::make_pair(2, 2));
  std::cout << "second " << &*m.begin() << std::endl;

  m[3];
  std::cout << "m[3]" << m.count(3) << std::endl;
}