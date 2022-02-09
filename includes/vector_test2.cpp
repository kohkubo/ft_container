#include <iostream>
#include <vector>
#include "vector.hpp"
#include "pair.hpp"

using namespace std;

void print_vector(ft::vector<int> v1, std::vector<int> v2) {
  cout << "====================================" << endl;
  cout << "v1.size() = " << v1.size() << " v2.size() = " << v2.size() << endl;
  cout << "v1.empty() = " << v1.empty() << " v2.empty() = " << v2.empty() << endl;
  cout << "v1.max_size() = " << v1.max_size() << " v2.max_size() = " << v2.max_size() << endl;
  cout << "v1.capacity() = " << v1.capacity() << " v2.capacity() = " << v2.capacity() << endl;
  cout << "v1.front() = " << v1.front() << " v2.front() = " << v2.front() << endl;
  cout << "v1.back() = " << v1.back() << " v2.back() = " << v2.back() << endl;
  size_t size = std::max(v1.size(), v2.size());
  for (size_t i = 0; i < size; i++) {
    cout << "v1[" << i << "] = " << v1[i] << " v2[" << i << "] = " << v2[i] << endl;
  }
}

int main() {
  ft::vector<int> v1;
  std::vector<int> v2;
  std::cout << "sizeof(ft::vector<int>) = " << sizeof(v1) << endl;
  std::cout << "sizeof(std::vector<int>) = " << sizeof(v2) << endl;
  for (int i = 0; i < 10; i++) {
    v1.push_back(i);
    v2.push_back(i);
  }
  print_vector(v1, v2);

  std::pair<int, int> p1;
  p1.first = 1;
  p1.second = 2;
  cout << "p1.first = " << p1.first << " p1.second = " << p1.second << endl;
  std::pair<int, int> p2;
  p2 = p1;
  cout << "p2.first = " << p2.first << " p2.second = " << p2.second << endl;

  ft::pair<int, int> p3;
  p3.first = 1;
  p3.second = 2;
  cout << "p3.first = " << p3.first << " p3.second = " << p3.second << endl;
  ft::pair<int, int> p4;
  p4 = p3;
  cout << "p4.first = " << p4.first << " p4.second = " << p4.second << endl;
}
