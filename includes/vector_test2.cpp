#include <iostream>
#include <vector>
#include "vector.hpp"

using namespace std;

void print_vector(ft::vector<int> v1, std::vector<int> v2) {
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
  for (int i = 0; i < 10; i++) {
    v1.push_back(i);
    v2.push_back(i);
  }
  for (int i = 0; i < 100000; i++) {
    v1.insert(v1.begin(), i, i);
    v2.insert(v2.begin(), i, i);
  }

  print_vector(v1, v2);
}
