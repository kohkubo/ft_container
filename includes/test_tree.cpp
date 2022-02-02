#include <iostream>
#include <map>

#include "my_rb_tree.hpp"
#include "pair.hpp"

int main() {
  typedef ft::pair<const int, int>                                    ftPair;
  typedef std::pair<const int, int>                                   stdPair;
  typedef ft::__tree<ftPair, std::less<int>, std::allocator<ftPair> > ftTree;
  typedef std::map<int, int>                                          stdMap;
  typedef ft::__tree<ftPair, std::less<int>, std::allocator<ftPair> >::iterator
                                       ftIt;
  typedef std::map<int, int>::iterator stdIt;
  typedef ft::pair<ftIt, bool>         ftPairBool;
  typedef std::pair<stdIt, bool>       stdPairBool;

  ftTree                               tree;
  int                                  array[5] = {3, 6, 2, 4, 5};

  tree.insert(ft::make_pair(array[0], array[0]));
  tree.insert(ft::make_pair(array[1], array[1]));
  tree.insert(ft::make_pair(array[2], array[2]));
  tree.insert(ft::make_pair(array[3], array[3]));
  tree.insert(ft::make_pair(array[4], array[4]));
  ft::print_tree(tree.__root(), 0);
  exit(0);

  for (int i = 0; i < 5; ++i) {
    std::cout << "Inserting " << array[i] << std::endl;
    ftPairBool tmp = tree.insert(ft::make_pair(array[i], array[i]));
    ft::print_tree(tree.__root(), 0);
    std::cout << "tmp.second: " << tmp.second << std::endl;
    std::cout << "---" << std::endl;
  }
  // for (int i = 1; i <= 10; ++i) {
  //   ftPairBool tmp = tree.insert(ft::make_pair(i, i));
  //   ft::print_tree(tree.__root(), 0);
  //   std::cout << "tmp.second: " << tmp.second << std::endl;
  //   std::cout << "---" << std::endl;
  // }

  return 0;
}
