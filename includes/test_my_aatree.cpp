#include <iostream>
#include <map>

#include "my_rb_tree_header.hpp"

int main() {
  // iterator
  std::map<int, std::string> map;
  map.insert(std::make_pair(1, "one"));
  map.insert(std::make_pair(2, "two"));
  map.insert(std::make_pair(3, "three"));
  map.insert(std::make_pair(4, "four"));
  map.insert(std::make_pair(5, "five"));
  map.insert(std::make_pair(6, "six"));
  map.insert(std::make_pair(7, "seven"));
  map.insert(std::make_pair(8, "eight"));
  map.insert(std::make_pair(9, "nine"));
  map.insert(std::make_pair(10, "ten"));
  ft::__tree<int, std::string>::iterator it;
  it = map.insert(map.begin(), std::make_pair(12, "twelve"));
  for (size_t i = 0; i < map.size(); ++i) {
    std::cout << "map[" << i << "] = " << map[i] << std::endl;
  }


  return 0;
}
