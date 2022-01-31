#include "test.hpp"
#include <iostream>

using namespace std;

int main() {
  typedef ft::Node<ft::pair<int, int> > myNode;
  myNode::key_type key = 1;
  cout << "key = " << key << endl;

  typedef ft::pair<int , int> myPair;
  typedef ft::Node<myPair> myNode2;
  myNode2::key_type key2 = 1;
  cout << "key2 = " << key2 << endl;
}
