#include <gtest/gtest.h>

#include <set>

#include "set.hpp"

TEST(SetTest, Constructor) {
  ft::set<int>  ft;
  std::set<int> std;
  EXPECT_EQ(ft.size(), std.size());
  EXPECT_EQ(ft.empty(), std.empty());
  EXPECT_EQ(ft.begin(), ft.end());
  EXPECT_EQ(std.begin(), std.end());
  EXPECT_EQ(ft.max_size(), std.max_size());

  for (int i = 0; i < 10; ++i) {
    ft.insert(i);
    std.insert(i);
  }
  ft::set<int>  ft_comp(std::less<int>(), ft.get_allocator());
  std::set<int> std_comp(std::less<int>(), std.get_allocator());
  ft_comp.insert(ft.begin(), ft.end());
  std_comp.insert(std.begin(), std.end());
  EXPECT_EQ(ft_comp.size(), std_comp.size());
  EXPECT_EQ(ft_comp.empty(), std_comp.empty());
  EXPECT_EQ(ft_comp.begin(), ft_comp.end());
  EXPECT_EQ(std_comp.begin(), std_comp.end());
  EXPECT_EQ(ft_comp.max_size(), std_comp.max_size());

  ft::set<int>  ft2(ft.begin(), ft.end(), (std::less<int>()),
                    ft.get_allocator());
  std::set<int> std2(std.begin(), std.end(), (std::less<int>()),
                     std.get_allocator());
  EXPECT_EQ(ft2.size(), std2.size());
  EXPECT_EQ(ft2.empty(), std2.empty());
  EXPECT_EQ(ft2.begin(), ft2.end());
  EXPECT_EQ(std2.begin(), std2.end());
  EXPECT_EQ(ft2.max_size(), std2.max_size());
  EXPECT_EQ(ft2.get_allocator(), ft.get_allocator());
  EXPECT_EQ(std2.get_allocator(), std.get_allocator());

  ft::set<int>  ft3(ft);
  std::set<int> std3(std);
  EXPECT_EQ(ft3.size(), std3.size());
  EXPECT_EQ(ft3.empty(), std3.empty());
  EXPECT_EQ(ft3.begin(), ft3.end());
  EXPECT_EQ(std3.begin(), std3.end());
  EXPECT_EQ(ft3.max_size(), std3.max_size());
  EXPECT_EQ(ft3.get_allocator(), ft.get_allocator());
  
}
