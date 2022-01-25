#include <iostream>

#include "treap.hpp"

int main() {
  ft::Treap<int> t;
  int            NUMS = 10;
  const int      GAP  = 37;
  int            i;

  std::cout << "Checking... (no more output means success)" << std::endl;

  for (i = GAP; i != 0; i = (i + GAP) % NUMS) t.insert(i);
  for (i = 1; i < NUMS; i += 2) t.remove(i);

  if (NUMS < 40)
    t.printTree();
  //   if (t.findMin() != 2 || t.findMax() != NUMS - 2)
  //     std::cout << "FindMin or FindMax error!" << std::endl;

  //   for (i = 2; i < NUMS; i += 2)
  //     if (!t.contains(i)) std::cout << "Find error1!" << std::endl;

  //   for (i = 1; i < NUMS; i += 2) {
  //     if (t.contains(i)) std::cout << "Find error2!" << std::endl;
  //   }

  //   ft::Treap<int> t2;
  //   t2 = t;

  //   for (i = 2; i < NUMS; i += 2)
  //     if (!t2.contains(i)) std::cout << "Find error1!" << std::endl;

  //   for (i = 1; i < NUMS; i += 2) {
  //     if (t2.contains(i)) std::cout << "Find error2!" << std::endl;
  //   }

  std::cout << "Test finished" << std::endl;
  return 0;
}
