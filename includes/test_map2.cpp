#include <iostream>
#include <map>

#include "my_rb_tree.hpp"
#include "pair.hpp"

int main() {
  typedef ft::pair<const int, int>  myPair;
  ft::__tree_node<myPair>           node;
  ft::__tree_node<myPair>::key_type key = 1;
  std::cout << "key = " << key << std::endl;

  ft::__tree<myPair, std::less<int>, std::allocator<ft::pair<const int, int> > >
                                                                   tree;
  ft::__tree<myPair, std::less<int>,
             std::allocator<ft::pair<const int, int> > >::key_type key2 = 1;
  std::cout << "key2 = " << key2 << std::endl;

  std::cout << "tree.size() = " << tree.size() << std::endl;
  // key_comp
  std::cout << tree.key_comp()(1, 22) << std::endl;
  std::map<int, int> map;
  std::cout << map.key_comp()(1, 22) << std::endl;

  // allocator_type
  typedef std::pair<const int, int> stdPair;
  stdPair                          *p = map.get_allocator().allocate(10);
  p->second                           = 200;
  std::cout << p->second << std::endl;

  myPair *p2 = tree.get_allocator().allocate(10);
  p2->second = 300;
  std::cout << p2->second << std::endl;

  // insert
  tree.insert(ft::make_pair(1, 2));
  tree.insert(ft::make_pair(2, 3));
  tree.insert(ft::make_pair(3, 4));
  tree.insert(ft::make_pair(4, 5));
  tree.insert(ft::make_pair(5, 6));
  std::cout << "tree.size() = " << tree.size() << std::endl;
  std::cout << tree.begin()->first << std::endl;
  std::cout << tree.begin()->second << std::endl;

  tree.print_node(tree.__end_node_);
  tree.print_node(tree.__root());
  tree.print_node(tree.__root()->__left_);
  tree.print_node(tree.__root()->__right_);
  tree.print_node(tree.__root()->__parent_);
  // iterator
  std::cout << "=== iterator ========" << std::endl;
  ft::__tree<myPair, std::less<int>,
             std::allocator<ft::pair<const int, int> > >::iterator it =
      tree.begin();
  std::cout << it->first << std::endl;
  ++it;
  std::cout << it->first << std::endl;
  ++it;
  std::cout << it->first << std::endl;
  ++it;
  std::cout << it->first << std::endl;
  std::cout << "=== print_tree ========" << std::endl;
  ft::print_tree(tree.__root(), 0);
  std::cout << "=== find ========" << std::endl;
  std::cout << tree.find(2)->first << std::endl;
  std::cout << tree.find(2)->second << std::endl;

  // loewr_bound
  std::cout << "=== lower_bound ========" << std::endl;
  ft::__tree<myPair, std::less<int>,
             std::allocator<ft::pair<const int, int> > >::iterator it2 =
      tree.lower_bound(1);
  std::cout << it2->first << std::endl;
  std::cout << it2->second << std::endl;

  return 0;
}

/*
node: NULL
0 0
 parent: NULL left: NULL right: NULL
node: END_NODE()
0 0
 parent: 0x0 left: ROOT() right: 0x0
node: ROOT()
2 3
 parent: END_NODE() left: 0x6000029d42d0 right: 0x6000029d4330
node: 0x6000029d42d0
1 2
 parent: ROOT() left: NULL right: NULL
node: 0x6000029d4330
3 4
 parent: ROOT() left: NULL right: NULL
node: END_NODE()
0 0
 parent: 0x0 left: ROOT() right: 0x0
*/
