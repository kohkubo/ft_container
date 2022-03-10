#include <gtest/gtest.h>

#include <map>
#include <random>

#include "map.hpp"

TEST(MapTest, MapConstructor) {
  // map();
  ft::map<int, int>  ft;
  std::map<int, int> std;
  EXPECT_EQ(ft.size(), std.size());
  EXPECT_EQ(ft.empty(), std.empty());
  EXPECT_EQ(ft.begin(), ft.end());
  EXPECT_EQ(ft.rbegin(), ft.rend());
  EXPECT_EQ(ft.max_size(), std.max_size());

  for (int i = 0; i < 10; ++i) {
    ft.insert(ft::make_pair(i, i * 2));
    std.insert(std::make_pair(i, i * 2));
  }
  // explicit map( const Compare& comp, const Allocator& alloc = Allocator() );
  ft::map<int, int>  ft_comp((std::less<int>()), (std::allocator<int>()));
  std::map<int, int> std_comp((std::less<int>()), (std::allocator<int>()));
  EXPECT_EQ(ft_comp.size(), std_comp.size());
  EXPECT_EQ(ft_comp.empty(), std_comp.empty());
  EXPECT_EQ(ft_comp.begin(), ft_comp.end());
  EXPECT_EQ(ft_comp.rbegin(), ft_comp.rend());
  EXPECT_EQ(ft_comp.max_size(), std_comp.max_size());

  // template< class InputIt >
  // map( InputIt first, InputIt last,
  //   const Compare& comp = Compare(),
  //   const Allocator& alloc = Allocator() );
  ft::map<int, int>  ft2(ft.begin(), ft.end(), (std::less<int>()),
                         (std::allocator<int>()));
  std::map<int, int> std2(std.begin(), std.end(), (std::less<int>()),
                          (std::allocator<int>()));
  EXPECT_EQ(ft2.size(), std2.size());
  EXPECT_EQ(ft2.empty(), std2.empty());
  EXPECT_EQ(ft2.begin()->first, std2.begin()->first);
  EXPECT_EQ(ft2.begin()->second, std2.begin()->second);
  EXPECT_EQ(ft2.rbegin()->first, std2.rbegin()->first);
  EXPECT_EQ(ft2.rbegin()->second, std2.rbegin()->second);

  // map( const map& other );
  ft::map<int, int>  ft3(ft);
  std::map<int, int> std3(std);
  EXPECT_EQ(ft3.size(), std3.size());
  EXPECT_EQ(ft3.empty(), std3.empty());
  EXPECT_EQ(ft3.begin()->first, std3.begin()->first);
  EXPECT_EQ(ft3.begin()->second, std3.begin()->second);
  EXPECT_EQ(ft3.rbegin()->first, std3.rbegin()->first);
  EXPECT_EQ(ft3.rbegin()->second, std3.rbegin()->second);

  // get_allocator()
  EXPECT_EQ(ft.get_allocator(), std.get_allocator());
}

TEST(MapTest, MapIterator) {
  ft::map<int, int>  ft;
  std::map<int, int> std;
  for (int i = 0; i < 10; ++i) {
    ft.insert(ft::make_pair(i, i * 2));
    std.insert(std::make_pair(i, i * 2));
  }
  // iterator begin();
  // iterator end();
  ft::map<int, int>::iterator  ft_it  = ft.begin();
  std::map<int, int>::iterator std_it = std.begin();
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(ft_it->first, std_it->first);
    EXPECT_EQ(ft_it->second, std_it->second);
    ++ft_it;
    ++std_it;
  }
  EXPECT_EQ(ft_it, ft.end());
  EXPECT_EQ(std_it, std.end());

  // const_iterator begin() const;
  // const_iterator end() const;
  const ft::map<int, int>  ft_const(ft);
  const std::map<int, int> std_const(std);
  ft::map<int, int>::const_iterator  ft_cit  = ft_const.begin();
  std::map<int, int>::const_iterator std_cit = std_const.begin();
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(ft_cit->first, std_cit->first);
    EXPECT_EQ(ft_cit->second, std_cit->second);
    ++ft_cit;
    ++std_cit;
  }
  // EXPECT_EQ(ft_cit, ft.end());
  // EXPECT_EQ(std_cit, std.end());
}

TEST(MapTest, MapReverseIterator) {
  ft::map<int, int>  ft;
  std::map<int, int> std;
  for (int i = 0; i < 10; ++i) {
    ft.insert(ft::make_pair(i, i * 2));
    std.insert(std::make_pair(i, i * 2));
  }
  // reverse_iterator rbegin();
  // reverse_iterator rend();
  ft::map<int, int>::reverse_iterator  ft_it  = ft.rbegin();
  std::map<int, int>::reverse_iterator std_it = std.rbegin();
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(ft_it->first, std_it->first);
    EXPECT_EQ(ft_it->second, std_it->second);
    ++ft_it;
    ++std_it;
  }
  EXPECT_EQ(ft_it, ft.rend());
  EXPECT_EQ(std_it, std.rend());

  // const_reverse_iterator rbegin() const;
  // const_reverse_iterator rend() const;
  const ft::map<int, int>  ft_const(ft);
  const std::map<int, int> std_const(std);
  ft::map<int, int>::const_reverse_iterator  ft_cit  = ft_const.rbegin();
  std::map<int, int>::const_reverse_iterator std_cit = std_const.rbegin();
  ft::map<int, int>::const_reverse_iterator  ft_end  = ft_const.rend();
  std::map<int, int>::const_reverse_iterator std_end = std_const.rend();
  while (ft_cit != ft_end) {
    EXPECT_EQ(ft_cit->first, std_cit->first);
    EXPECT_EQ(ft_cit->second, std_cit->second);
    ++ft_cit;
    ++std_cit;
  }
}

TEST(MapTest, MapRandomInsertAndEraseAndClear) {
  int size = 100000;
  srand(time(0));
  ft::map<int, int>  ft;
  std::map<int, int> std;
  // insert(const value_type& __x)
  for (int i = 0; i < size; ++i) {
    int                                         key = std::rand() % size;
    int                                         val = std::rand() % size;
    ft::pair<ft::map<int, int>::iterator, bool> ft_ret =
        ft.insert(ft::make_pair(key, val));
    std::pair<std::map<int, int>::iterator, bool> std_ret =
        std.insert(std::make_pair(key, val));
    EXPECT_EQ(ft_ret.second, std_ret.second);
  }
  // insert(iterator position, const value_type& __x) begin
  for (int i = 0; i < size; ++i) {
    int                         key = std::rand() % size;
    int                         val = std::rand() % size;
    ft::map<int, int>::iterator ft_ret =
        ft.insert(ft.begin(), ft::make_pair(key, val));
    std::map<int, int>::iterator std_ret =
        std.insert(std.begin(), std::make_pair(key, val));
  }
  if (std::rand() % 4 == 0) {
    ft.clear();
    std.clear();
    ft.clear();
    std.clear();
  }
  // insert(iterator position, const value_type& __x) end
  ft::map<int, int>  ft2;
  std::map<int, int> std2;
  for (int i = 0; i < size; ++i) {
    int                         key = std::rand() % size;
    int                         val = std::rand() % size;
    ft::map<int, int>::const_iterator ft_ret =
        ft2.insert(ft2.end(), ft::make_pair(key, val));
    std::map<int, int>::const_iterator std_ret =
        std2.insert(std2.end(), std::make_pair(key, val));
  }

  // insert(iterator first, iterator last)
  ft.insert(ft2.begin(), ft2.end());
  std.insert(std2.begin(), std2.end());
  ft::map<int, int>::iterator  ft_it;
  std::map<int, int>::iterator std_it;
  for (std::map<int, int>::iterator it = std.begin(); it != std.end(); ++it) {
    ft_it  = ft.find(it->first);
    std_it = std.find(it->first);
    EXPECT_EQ(ft_it->first, std_it->first);
    EXPECT_EQ(ft_it->second, std_it->second);
  }
  if (std::rand() % 4 == 0) {
    ft.clear();
    std.clear();
    ft.clear();
    std.clear();
  }
  // erase(iterator position)
  for (int i = 0; i < size; ++i) {
    int                          key     = std::rand() % size;
    ft::map<int, int>::iterator  ft_ret  = ft.find(key);
    std::map<int, int>::iterator std_ret = std.find(key);
    if (ft_ret != ft.end()) {
      ft_ret  = ft.erase(ft_ret);
      std_ret = std.erase(std_ret);
      if (ft_ret != ft.end()) {
        EXPECT_EQ(ft_ret->first, std_ret->first);
        EXPECT_EQ(ft_ret->second, std_ret->second);
      }
    }
  }
  // erase(iterator first, iterator last)
  for (int i = 0; i < size; ++i) {
    int key  = std::rand() % size;
    int key2 = std::rand() % size;
    if (key > key2) {
      std::swap(key, key2);
    }
    if (ft.count(key) + ft.count(key2) == 2) {
      ft::map<int, int>::iterator  ft_ret  = ft.find(key);
      std::map<int, int>::iterator std_ret = std.find(key);
      ft_ret                               = ft.erase(ft_ret, ft.find(key2));
      std_ret                              = std.erase(std_ret, std.find(key2));
      if (ft_ret != ft.end()) {
        EXPECT_EQ(ft_ret->first, std_ret->first);
        EXPECT_EQ(ft_ret->second, std_ret->second);
      }
    }
  }
  // erase(const key_type& __x)
  for (int i = 0; i < size * 30; ++i) {
    int key = std::rand() % size;
    if (ft.count(key) == 1) {
      int ft_ret  = ft.erase(key);
      int std_ret = std.erase(key);
      EXPECT_EQ(ft_ret, std_ret);
    }
  }
}

// operator[]
TEST(MapTest, MapOperate) {
  ft::map<int, int>  ft;
  std::map<int, int> std;
  int                 size = 100000;
  srand(time(0));
  for (int i = 0; i < size; ++i) {
    int                                         key = std::rand() % size;
    int                                         val = std::rand() % size;
    ft::pair<ft::map<int, int>::iterator, bool> ft_ret =
        ft.insert(ft::make_pair(key, val));
    std::pair<std::map<int, int>::iterator, bool> std_ret =
        std.insert(std::make_pair(key, val));
    EXPECT_EQ(ft_ret.second, std_ret.second);
  }
  for (int i = 0; i < size; ++i) {
    int key = std::rand() % size;
    ft[key] = 100;
    std[key] = 100;
  }
  for (int i = 0; i < size; ++i) {
    int key = std::rand() % size;
    EXPECT_EQ(ft[key], std[key]);
  }
  for (ft::map<int, int>::iterator it = ft.begin(); it != ft.end(); ++it) {
    EXPECT_EQ(it->second, std.find(it->first)->second);
  }
}

// swap
TEST(MapTest, MapSwap) {
  srand(time(0));
  size_t             size = 100;
  ft::map<int, int>  ft1;
  std::map<int, int> std1;
  ft::map<int, int>  ft2;
  std::map<int, int> std2;
  for (int i = 0; i < size; ++i) {
    int                                         key = std::rand() % size;
    int                                         val = std::rand() % size;
    ft::pair<ft::map<int, int>::iterator, bool> ft_ret =
        ft1.insert(ft::make_pair(key, val));
    std::pair<std::map<int, int>::iterator, bool> std_ret =
        std1.insert(std::make_pair(key, val));
    EXPECT_EQ(ft_ret.second, std_ret.second);
  }
  for (int i = 0; i < size; ++i) {
    int                                         key = std::rand() % size;
    int                                         val = std::rand() % size;
    ft::pair<ft::map<int, int>::iterator, bool> ft_ret =
        ft2.insert(ft::make_pair(key, val));
    std::pair<std::map<int, int>::iterator, bool> std_ret =
        std2.insert(std::make_pair(key, val));
    EXPECT_EQ(ft_ret.second, std_ret.second);
  }
  ft1.swap(ft2);
  std1.swap(std2);
  ft::map<int, int>::iterator  ft_it;
  std::map<int, int>::iterator std_it;
  for (std::map<int, int>::iterator it = std1.begin(); it != std1.end(); ++it) {
    ft_it  = ft1.find(it->first);
    std_it = std1.find(it->first);
    EXPECT_EQ(ft_it->first, std_it->first);
    EXPECT_EQ(ft_it->second, std_it->second);
  }
}

// find
TEST(MapTest, MapFind) {
  // iterator find( const Key& key );
  ft::map<int, int>  ft;
  std::map<int, int> std;
  // size 0
  EXPECT_EQ(ft.find(0), ft.end());
  EXPECT_EQ(std.find(0), std.end());
  EXPECT_EQ(ft.find(-1), ft.end());
  EXPECT_EQ(std.find(-1), std.end());
  EXPECT_EQ(ft.find(100), ft.end());
  EXPECT_EQ(std.find(100), std.end());
  // size 10
  for (int i = 0; i < 10; ++i) {
    ft.insert(ft::make_pair(i, i * 2));
    std.insert(std::make_pair(i, i * 2));
  }
  ft::map<int, int>::iterator  ft_it  = ft.find(5);
  std::map<int, int>::iterator std_it = std.find(5);
  EXPECT_EQ(ft_it->first, std_it->first);
  EXPECT_EQ(ft_it->second, std_it->second);
  ft_it  = ft.find(15);
  std_it = std.find(15);
  EXPECT_EQ(ft_it, ft.end());
  EXPECT_EQ(std_it, std.end());

  // const_iterator find(const key_type& __x) const
  ft::map<int, int>  ft_const;
  std::map<int, int> std_const;
  for (int i = 0; i < 10; ++i) {
    ft_const.insert(ft::make_pair(i, i * 2));
    std_const.insert(std::make_pair(i, i * 2));
  }
  ft::map<int, int>::const_iterator  ft_it_const  = ft_const.find(5);
  std::map<int, int>::const_iterator std_it_const = std_const.find(5);
  EXPECT_EQ(ft_it_const->first, std_it_const->first);
  EXPECT_EQ(ft_it_const->second, std_it_const->second);
  ft_it_const  = ft_const.find(15);
  std_it_const = std_const.find(15);
  EXPECT_EQ(ft_it_const, ft_const.end());
  EXPECT_EQ(std_it_const, std_const.end());
}

// count
TEST(MapTest, MapCount) {
  ft::map<int, int>  ft;
  std::map<int, int> std;
  // size 0
  EXPECT_EQ(ft.count(0), 0);
  EXPECT_EQ(std.count(0), 0);
  EXPECT_EQ(ft.count(-1), 0);
  EXPECT_EQ(std.count(-1), 0);
  EXPECT_EQ(ft.count(100), 0);
  EXPECT_EQ(std.count(100), 0);
  // size 10
  for (int i = 0; i < 10; ++i) {
    ft.insert(ft::make_pair(i, i * 2));
    std.insert(std::make_pair(i, i * 2));
  }
  EXPECT_EQ(ft.count(5), 1);
  EXPECT_EQ(std.count(5), 1);
  EXPECT_EQ(ft.count(15), 0);
  EXPECT_EQ(std.count(15), 0);
}

// lower_bound
TEST(MapTest, MapLower_bound) {
  size_t size = 10000;
  srand(time(0));

  // iterator lower_bound(const key_type& k)
  ft::map<int, int>  ft;
  std::map<int, int> std;
  // size 0
  EXPECT_EQ(ft.lower_bound(0), ft.end());
  EXPECT_EQ(std.lower_bound(0), std.end());
  EXPECT_EQ(ft.lower_bound(-100), ft.end());
  EXPECT_EQ(std.lower_bound(-100), std.end());
  EXPECT_EQ(ft.lower_bound(110), ft.end());
  EXPECT_EQ(std.lower_bound(110), std.end());
  // size 10
  for (int i = 0; i < size; ++i) {
    int key = std::rand() % size;
    int val = std::rand() % size;
    ft.insert(ft::make_pair(key, val));
    std.insert(std::make_pair(key, val));
  }
  for (int i = 0; i < size * 3; ++i) {
    int                          key    = std::rand() % size;
    ft::map<int, int>::iterator  ft_it  = ft.lower_bound(key);
    std::map<int, int>::iterator std_it = std.lower_bound(key);
    if (ft_it != ft.end()) {
      EXPECT_EQ(ft_it->first, std_it->first);
      EXPECT_EQ(ft_it->second, std_it->second);
    } else {
      EXPECT_EQ(ft_it, ft.end());
      EXPECT_EQ(std_it, std.end());
    }
  }
  // const_iterator lower_bound(const key_type& k) const
  const ft::map<int, int>  ft_const;
  const std::map<int, int> std_const;
  for (int i = 0; i < size * 3; ++i) {
    int                          key    = std::rand() % size;
    ft::map<int, int>::const_iterator  ft_it_const  = ft_const.lower_bound(key);
    std::map<int, int>::const_iterator std_it_const = std_const.lower_bound(key);
    if (ft_it_const != ft_const.end()) {
      EXPECT_EQ(ft_it_const->first, std_it_const->first);
      EXPECT_EQ(ft_it_const->second, std_it_const->second);
    } else {
      EXPECT_EQ(ft_it_const, ft_const.end());
      EXPECT_EQ(std_it_const, std_const.end());
    }
  }
}

// upper_bound
TEST(MapTest, MapUpper_bound) {
  //  iterator upper_bound(const key_type& k)
  ft::map<int, int>  ft;
  std::map<int, int> std;

  // size 0
  EXPECT_EQ(ft.upper_bound(0), ft.end());
  EXPECT_EQ(std.upper_bound(0), std.end());
  EXPECT_EQ(ft.upper_bound(-100), ft.end());
  EXPECT_EQ(std.upper_bound(-100), std.end());
  EXPECT_EQ(ft.upper_bound(110), ft.end());
  EXPECT_EQ(std.upper_bound(110), std.end());
  // size 10
  for (int i = 0; i < 1000; ++i) {
    ft.insert(ft::make_pair(i, i * 2));
    std.insert(std::make_pair(i, i * 2));
  }
  for (int i = 0; i < 1000 * 3; ++i) {
    ft::map<int, int>::iterator  ft_it  = ft.upper_bound(i);
    std::map<int, int>::iterator std_it = std.upper_bound(i);
    if (ft_it != ft.end()) {
      EXPECT_EQ(ft_it->first, std_it->first);
      EXPECT_EQ(ft_it->second, std_it->second);
    } else {
      EXPECT_EQ(ft_it, ft.end());
      EXPECT_EQ(std_it, std.end());
    }
  }
  // const_iterator upper_bound(const key_type& k) const
  const ft::map<int, int>  ft_const;
  const std::map<int, int> std_const;
  for (int i = 0; i < 1000 * 3; ++i) {
    ft::map<int, int>::const_iterator  ft_it_const  = ft_const.upper_bound(i);
    std::map<int, int>::const_iterator std_it_const = std_const.upper_bound(i);
    if (ft_it_const != ft_const.end()) {
      EXPECT_EQ(ft_it_const->first, std_it_const->first);
      EXPECT_EQ(ft_it_const->second, std_it_const->second);
    } else {
      EXPECT_EQ(ft_it_const, ft_const.end());
      EXPECT_EQ(std_it_const, std_const.end());
    }
  }
}

// equal_range
TEST(MapTest, MapEqual_range) {
  ft::map<int, int>  ft;
  std::map<int, int> std;

  // size 0
  EXPECT_EQ(ft.equal_range(0), ft::make_pair(ft.end(), ft.end()));
  EXPECT_EQ(std.equal_range(0), std::make_pair(std.end(), std.end()));
  EXPECT_EQ(ft.equal_range(-100), ft::make_pair(ft.end(), ft.end()));
  EXPECT_EQ(std.equal_range(-100), std::make_pair(std.end(), std.end()));
  EXPECT_EQ(ft.equal_range(110), ft::make_pair(ft.end(), ft.end()));
  EXPECT_EQ(std.equal_range(110), std::make_pair(std.end(), std.end()));
  // // size 10
  for (int i = 0; i < 10; ++i) {
    ft.insert(ft::make_pair(i, i * 2));
    std.insert(std::make_pair(i, i * 2));
  }
  ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> ft_it =
      ft.equal_range(5);
  std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator> std_it =
      std.equal_range(5);
  EXPECT_EQ(ft_it.first->first, std_it.first->first);
  EXPECT_EQ(ft_it.first->second, std_it.first->second);
  EXPECT_EQ(ft_it.second->first, std_it.second->first);
  EXPECT_EQ(ft_it.second->second, std_it.second->second);
  ft_it  = ft.equal_range(10);
  std_it = std.equal_range(10);
  EXPECT_EQ(ft_it.first, ft.end());
  EXPECT_EQ(ft_it.second, ft.end());
  EXPECT_EQ(std_it.first, std.end());
  EXPECT_EQ(std_it.second, std.end());
  ft_it  = ft.equal_range(-1);
  std_it = std.equal_range(-1);
  EXPECT_EQ(ft_it.first->first, std_it.first->first);
  EXPECT_EQ(ft_it.first->second, std_it.first->second);
  EXPECT_EQ(ft_it.second->first, std_it.second->first);
  EXPECT_EQ(ft_it.second->second, std_it.second->second);
}

// non-member functions
TEST(MapTest, MapNonMemberFunc) {
  int size = 5;
  srand(time(0));
  ft::map<int, int>  ft;
  std::map<int, int> std;
  ft::map<int, int>  ft_large;
  std::map<int, int> std_large;
  ft::map<int, int>  ft_small;
  std::map<int, int> std_small;
  ft::map<int, int>  ft_random;
  std::map<int, int> std_random;
  for (int i = 0; i < size; ++i) {
    int key = std::rand() % size;
    int val = std::rand() % size;
    ft.insert(ft::make_pair(key, val));
    std.insert(std::make_pair(key, val));
    ft_large.insert(ft::make_pair(key + 2, val + 2));
    std_large.insert(std::make_pair(key + 2, val + 2));
    ft_small.insert(ft::make_pair(key - 2, val - 2));
    std_small.insert(std::make_pair(key - 2, val - 2));
    key = std::rand() % size;
    val = std::rand() % size;
    ft_random.insert(ft::make_pair(key, val));
    std_random.insert(std::make_pair(key, val));
  }
  ft::map<int, int>  ft_copy(ft);
  std::map<int, int> std_copy(std);
  EXPECT_EQ(ft == ft_copy, std == std_copy);
  EXPECT_EQ(ft == ft_large, std == std_large);
  EXPECT_EQ(ft == ft_small, std == std_small);
  EXPECT_EQ(ft == ft_random, std == std_random);
  EXPECT_EQ(ft != ft_copy, std != std_copy);
  EXPECT_EQ(ft != ft_large, std != std_large);
  EXPECT_EQ(ft != ft_small, std != std_small);
  EXPECT_EQ(ft != ft_random, std != std_random);
  EXPECT_EQ(ft < ft_copy, std < std_copy);
  EXPECT_EQ(ft < ft_large, std < std_large);
  EXPECT_EQ(ft < ft_small, std < std_small);
  EXPECT_EQ(ft < ft_random, std < std_random);
  EXPECT_EQ(ft > ft_copy, std > std_copy);
  EXPECT_EQ(ft > ft_large, std > std_large);
  EXPECT_EQ(ft > ft_small, std > std_small);
  EXPECT_EQ(ft > ft_random, std > std_random);
  EXPECT_EQ(ft <= ft_copy, std <= std_copy);
  EXPECT_EQ(ft <= ft_large, std <= std_large);
  EXPECT_EQ(ft <= ft_small, std <= std_small);
  EXPECT_EQ(ft <= ft_random, std <= std_random);
  EXPECT_EQ(ft >= ft_copy, std >= std_copy);
  EXPECT_EQ(ft >= ft_large, std >= std_large);
  EXPECT_EQ(ft >= ft_small, std >= std_small);
  EXPECT_EQ(ft >= ft_random, std >= std_random);
  ft::swap(ft_large, ft_small);
  std::swap(std_large, std_small);
  EXPECT_EQ(ft == ft_large, std == std_large);
  EXPECT_EQ(ft == ft_small, std == std_small);
  EXPECT_EQ(ft == ft_random, std == std_random);
  EXPECT_EQ(ft != ft_large, std != std_large);
  EXPECT_EQ(ft != ft_small, std != std_small);
  EXPECT_EQ(ft != ft_random, std != std_random);
  EXPECT_EQ(ft < ft_large, std < std_large);
  EXPECT_EQ(ft < ft_small, std < std_small);
  EXPECT_EQ(ft < ft_random, std < std_random);
  EXPECT_EQ(ft > ft_large, std > std_large);
  EXPECT_EQ(ft > ft_small, std > std_small);
  EXPECT_EQ(ft > ft_random, std > std_random);
  EXPECT_EQ(ft <= ft_large, std <= std_large);
  EXPECT_EQ(ft <= ft_small, std <= std_small);
  EXPECT_EQ(ft <= ft_random, std <= std_random);
  EXPECT_EQ(ft >= ft_large, std >= std_large);
  EXPECT_EQ(ft >= ft_small, std >= std_small);
  EXPECT_EQ(ft >= ft_random, std >= std_random);
}

// observers
TEST(MapTest, MapObservers) {
  ft::map<int, int> ft;
  std::map<int, int> std;
  ft::map<int, int>::key_compare ft_comp = ft.key_comp();
  std::map<int, int>::key_compare std_comp = std.key_comp();
  EXPECT_EQ(ft_comp(1, 2), std_comp(1, 2));
  EXPECT_EQ(ft_comp(2, 1), std_comp(2, 1));
  EXPECT_EQ(ft_comp(1, 1), std_comp(1, 1));

  ft::map<int, int>::value_compare ft_val_comp = ft.value_comp();
  std::map<int, int>::value_compare std_val_comp = std.value_comp();
  ft::pair<int, int> ft_pair(1, 2);
  std::pair<int, int> std_pair(1, 2);
  ft::pair<int, int> ft_pair2(2, 1);
  std::pair<int, int> std_pair2(2, 1);
  ft::pair<int, int> ft_pair3(1, 1);
  std::pair<int, int> std_pair3(1, 1);
  EXPECT_EQ(ft_val_comp(ft_pair, ft_pair2), std_val_comp(std_pair, std_pair2));
  EXPECT_EQ(ft_val_comp(ft_pair, ft_pair3), std_val_comp(std_pair, std_pair3));
  EXPECT_EQ(ft_val_comp(ft_pair2, ft_pair), std_val_comp(std_pair2, std_pair));
  EXPECT_EQ(ft_val_comp(ft_pair2, ft_pair3), std_val_comp(std_pair2, std_pair3));
  EXPECT_EQ(ft_val_comp(ft_pair3, ft_pair), std_val_comp(std_pair3, std_pair));
  EXPECT_EQ(ft_val_comp(ft_pair3, ft_pair2), std_val_comp(std_pair3, std_pair2));
}

// operator=
TEST(MapTest, MapOperatorEqual) {
  ft::map<int, int> ft;
  std::map<int, int> std;
  ft::map<int, int> ft_copy(ft);
  std::map<int, int> std_copy(std);
  for (int i = 0; i < 100; ++i) {
    ft.insert(ft::make_pair(i, i));
    std.insert(std::make_pair(i, i));
  }
  ft_copy = ft;
  std_copy = std;
  EXPECT_EQ(ft, ft_copy);
  EXPECT_EQ(std, std_copy);
  for (ft::map<int, int>::iterator it = ft.begin(); it != ft.end(); ++it) {
    EXPECT_EQ(it->second, ft_copy[it->first]);
  }
}
