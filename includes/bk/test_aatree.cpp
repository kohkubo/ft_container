#include <iostream>
#include <limits>
#include <stdexcept>
#include <random>
#include "aatree.hpp"

int main() {
  std::srand(std::time(0));
  ft::AATree<int> t;

  for (size_t i = 0; i < 10; ++i) {
    t.insert(std::rand() % 100);
  }
  t.printTree();
  std::cout << "Min: " << t.findMin() << std::endl;
  std::cout << "Max: " << t.findMax() << std::endl;
  return 0;
}
