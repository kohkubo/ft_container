#include <gtest/gtest.h>

#include <map>
#include <random>

#include "map.hpp"

TEST(MapTest, MapConstructor) {
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
  ft::map<int, int>  ft2(ft.begin(), ft.end());
  std::map<int, int> std2(std.begin(), std.end());
  EXPECT_EQ(ft2.size(), std2.size());
  EXPECT_EQ(ft2.empty(), std2.empty());
  EXPECT_EQ(ft2.begin()->first, std2.begin()->first);
  EXPECT_EQ(ft2.begin()->second, std2.begin()->second);
}

TEST(MapTest, MapIterator) {
  ft::map<int, int>  ft;
  std::map<int, int> std;
  for (int i = 0; i < 10; ++i) {
    ft.insert(ft::make_pair(i, i * 2));
    std.insert(std::make_pair(i, i * 2));
  }
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
}

TEST(MapTest, MapReverseIterator) {
  ft::map<int, int>  ft;
  std::map<int, int> std;
  for (int i = 0; i < 10; ++i) {
    ft.insert(ft::make_pair(i, i * 2));
    std.insert(std::make_pair(i, i * 2));
  }
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
}

TEST(MapTest, MapRandomInsertAndErase) {
  int size = 10000;
  std::srand(std::time(0));
  ft::map<int, int>  ft;
  std::map<int, int> std;
  // insert(const value_type& __x)
  for (int i = 0; i < size; ++i) {
    int                                         key = std::rand();
    int                                         val = std::rand();
    ft::pair<ft::map<int, int>::iterator, bool> ft_ret =
        ft.insert(ft::make_pair(key, val));
    std::pair<std::map<int, int>::iterator, bool> std_ret =
        std.insert(std::make_pair(key, val));
    EXPECT_EQ(ft_ret.second, std_ret.second);
  }
  // insert(iterator position, const value_type& __x) begin
  for (int i = 0; i < size; ++i) {
    int                         key = std::rand();
    int                         val = std::rand();
    // TODO 重複するものが入ってきたときに、本家のインサートでどのように処理をしているのか確認する
    ft::map<int, int>::iterator ft_ret =
        ft.insert(ft.begin(), ft::make_pair(key, val));
    std::map<int, int>::iterator std_ret =
        std.insert(std.begin(), std::make_pair(key, val));
  }
  exit(0);
  // insert(iterator position, const value_type& __x) end
  ft::map<int, int>  ft2;
  std::map<int, int> std2;
  for (int i = 0; i < size; ++i) {
    int                         key = std::rand();
    int                         val = std::rand();
    ft::map<int, int>::iterator ft_ret =
        ft2.insert(ft2.end(), ft::make_pair(key, val));
    std::map<int, int>::iterator std_ret =
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
}
