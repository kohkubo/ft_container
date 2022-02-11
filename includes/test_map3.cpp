#include <iostream>
#include <map>

#include "map.hpp"
#include "pair.hpp"
#include "vector.hpp"
#include <vector>

#define EXPECT_EQ(a, b) \
  if (a != b) { \
    std::cout << "__LINE__" << __LINE__ << std::endl; \
    std::cout << "Error" << std::endl; \
    return 1; \
  }

int main() {
  ft::map<int, int>  ft;
  std::map<int, int> std;

  for (int i = 0; i < 10; ++i) {
    ft.insert(ft::make_pair(i, i * 2));
    std.insert(std::make_pair(i, i * 2));
  }
  ft.erase(ft.begin(), ft.end());
  std.erase(std.begin(), std.end());
  std::cout << "ft.size() = " << ft.size() << std::endl;
  std::cout << "std.size() = " << std.size() << std::endl;
  // EXPECT_EQ(ft.size(), std.size());
  // EXPECT_EQ(ft.empty(), std.empty());
  ft::map<int, int>::iterator ft_map_test1;
  ft::map<int, int>::iterator ft_map_test2;
  ft_map_test1 = ft.find(1);
  ft_map_test2 = ft.find(2);
  if (ft_map_test1 == ft_map_test2)
    std::cout << "find(1) == find(2)" << std::endl;
  else
    std::cout << "find(1) != find(2)" << std::endl;


  // []
  ft[1] = 2;
  std[1] = 2;
  EXPECT_EQ(ft[1], std[1]);
  ft[1] = 3;
  std[1] = 3;
  EXPECT_EQ(ft[1], std[1]);
  ft[1] = 4;
  std[1] = 4;
  EXPECT_EQ(ft[1], std[1]);
  ft[100] = 5;
  std[100] = 5;
  EXPECT_EQ(ft[100], std[100]);

  ft::vector<int> ft_vector;
  std::vector<int> std_vector;
  ft_vector.assign(10, 1);
  std_vector.assign(10, 1);
  return 0;
}
