#ifndef INCLUDES_TEST_HPP_
#define INCLUDES_TEST_HPP_

#include "pair.hpp"

namespace ft
{

template<class _Tp>
struct Node;

template<class _Key, class _Tp>
struct Node<pair<_Key, _Tp> > {
  typedef _Key key_type;
  typedef _Tp mapped_type;
  typedef pair<_Key, _Tp> value_type;
};




} // namespace ft



#endif  // INCLUDES_TEST_HPP_
