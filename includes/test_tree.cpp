#include <iostream>
#include <map>

#include "rb_tree.hpp"
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
  for (int i = 1; i <= 10; ++i) {
    ftPairBool tmp = tree.insert(ft::make_pair(i, i));
    ft::print_tree(tree.__root(), 0);
    std::cout << "tmp.second: " << tmp.second << std::endl;
    std::cout << "---" << std::endl;
  }
  
  return 0;
}
