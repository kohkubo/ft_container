#include <map>
#include <iostream>

int main() {
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
  std::cout << "map.size() = " << map.size() << std::endl;
  for (size_t i = 0; i < map.size(); ++i) {
    std::cout << "map[" << i << "] = " << map[i] << std::endl;
  }
  std::cout << "map.count(1) = " << map.count(1) << std::endl;
  std::cout << "map.find(1) = " << map.find(1)->first << std::endl;
  // size
  std::cout << "map.size() = " << map.size() << std::endl;

  // pair
  std::pair<std::map<int, std::string>::iterator, bool> ret;
  ret = map.insert(std::make_pair(11, "eleven"));
  std::cout << "ret.second = " << ret.second << std::endl;
  std::cout << "ret.first->first = " << ret.first->first << std::endl;
  std::cout << "ret.first->second = " << ret.first->second << std::endl;
  std::cout << "map.size() = " << map.size() << std::endl;
  
  // iterator
  std::map<int, std::string>::iterator it;
  it = map.insert(map.begin(), std::make_pair(12, "twelve"));
  for (size_t i = 0; i < map.size(); ++i) {
    std::cout << "map[" << i << "] = " << map[i] << std::endl;
  }
  
  return 0;
}
