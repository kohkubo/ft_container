#include <iostream>
#include <map>

#include "rb_tree.hpp"
#include "map.hpp"
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

  ft::print_node(tree.__end_node_);
  ft::print_node(tree.__root());
  ft::print_node(tree.__root()->__left_);
  ft::print_node(tree.__root()->__right_);
  ft::print_node(tree.__root()->__parent_);
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

  // erase
  std::cout << "=== erase ========" << std::endl;
  ft::print_tree_node(tree.__root());
  std::cout << tree.erase(2) << std::endl;
  ft::print_tree_node(tree.__root());

  std::cout << "=== map ========" << std::endl;
  std::map<int, int> map2;
  map2.insert(std::make_pair(1, 2));
  std::cout << map2[1] << std::endl;
  map2[2] = 3;
  std::cout << map2[2] << std::endl;
  map2[2] = 4;
  std::cout << map2[2] << std::endl;
  std::cout << map2[3] << std::endl;
  std::cout << map2.find(2)->second << std::endl;
  std::cout << map2.find(3)->second << std::endl;
  // 既にある要素をインサート
  std::pair<std::map<int, int>::iterator, bool> ret =
      map2.insert(std::make_pair(1, 5));
  if (ret.first == map2.end())
    std::cout << "it == map2.end()" << std::endl;
  else
  {
    // 既にあるkeyをインサートしても、valueは変わらない、falseと要素のIteratorが返る
    std::cout << "it != map2.end()" << std::endl;
    std::cout << "ret->second = " << ret.second << std::endl;
    std::cout << "it->first = " << ret.first->first << std::endl;
    std::cout << "it->second = " << ret.first->second << std::endl;
  }
  // end()にinsertするとどうなるか
  std::cout << "===========" << std::endl;
  std::map<int, int>::iterator it3 =
      map2.insert(map2.end(), std::make_pair(4, 5));
  std::cout << "it3->first = " << it3->first << std::endl;
  std::cout << "it3->second = " << it3->second << std::endl;
  // end()にinsertするとどうなるか ver. ft
  std::cout << "===========" << std::endl;
  ft::map<int, int> ft_map;
  ft_map.insert(ft::make_pair(1, 2));
  ft::map<int, int>::iterator it4 =
      ft_map.insert(ft_map.end(), ft::make_pair(4, 5));
  std::cout << "it4->first = " << it4->first << std::endl;
  std::cout << "it4->second = " << it4->second << std::endl;

  // end_nodeをeraseするとセグフォ
  // std::map<int, int>::iterator it3 = map2.erase(map2.end());
  // if (it3 == map2.end())
  //   std::cout << "it3 == map2.end()" << std::endl;
  // else
  //   std::cout << "it3 != map2.end()" << std::endl;

  // mapのiteratorにNULLを入れるとどうなる？
  {
    // ftでは、NULLを入れると入ってしまう
    // ft::map<int, int>::iterator it(NULL);
    // stdでは、NULLを入れるとエラーになる
    // std::map<int, int>::iterator it2(NULL);
  }

  // size 0のとき、loewr_bound ft
  {
    std::cout << "=== size 0 lower_bound ===" << std::endl;
    ft::map<int, int> map3;
    ft::map<int, int>::iterator ftit = map3.lower_bound(1);
    if (ftit == map3.end())
      std::cout << "ftit == map3.end()" << std::endl;
    else
      std::cout << "ftit != map3.end()" << std::endl;
  }
  // size 0のとき、loewr_bound std
  {
    std::cout << "=== size 0 lower_bound ===" << std::endl;
    std::map<int, int> map4;
    std::map<int, int>::iterator stdit = map4.lower_bound(1);
    if (stdit == map4.end())
      std::cout << "stdit == map4.end()" << std::endl;
    else
      std::cout << "stdit != map4.end()" << std::endl;
  }

  // size() = 0のとき、find()するとどうなる？
  {
    std::cout << "====find() with size 0=======" << std::endl;
    std::map<int, int> map3;
    map3.insert(std::make_pair(1, 2));
    map3.clear();
    std::map<int, int>::iterator it5 = map3.find(1);
    if (it5 == map3.end())
      std::cout << "it5 == map3.end()" << std::endl;
    else
      std::cout << "it5 != map3.end()" << std::endl;
  }
  // size() = 0のとき、find()するとどうなる？ ft
  {
    std::cout << "====find() with size 0=======" << std::endl;
    ft::map<int, int> ft_map2;
    ft_map2.insert(ft::make_pair(1, 2));
    std::cout << "__LINE__" << __LINE__ << std::endl;
    ft_map2.clear();
    ft::map<int, int>::iterator it6 = ft_map2.find(1);
    if (it6 == ft_map2.end())
      std::cout << "it6 == ft_map2.end()" << std::endl;
    else
      std::cout << "it6 != ft_map2.end()" << std::endl;
  }

  // eraseで返ってきたiteratorの中身は？
  std::cout << "===========" << std::endl;
  std::map<int, int>::iterator it5 = map2.erase(map2.find(1));
  std::cout << "it5->first = " << it5->first << std::endl;
  std::cout << "it5->second = " << it5->second << std::endl;
  while (it5 != map2.end())
  {
    std::cout << "it5->first = " << it5->first << std::endl;
    ++it5;
  }
  map2.erase(2);
  map2.erase(3);
  map2.erase(4);
  std::cout << map2.size() << std::endl;
  map2.erase(100);
  // eraseで返ってきたiteratorの中身は？ ft
  std::cout << "==ft_map erase =========" << std::endl;
  ft::map<int, int>::iterator it6 = ft_map.erase(ft_map.find(1));
  std::cout << "it6->first = " << it6->first << std::endl;
  std::cout << "it6->second = " << it6->second << std::endl;
  while (it6 != ft_map.end())
  {
    std::cout << "it6->first = " << it6->first << std::endl;
    ++it6;
  }
  ft_map.erase(2);
  ft_map.erase(3);
  ft_map.erase(4);
  std::cout << ft_map.size() << std::endl;
  ft_map.erase(100);
  ft_map.erase(100);
  ft_map.erase(100);
  ft_map.erase(100);

  


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
