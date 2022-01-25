#ifndef INCLUDES_GCC_TREE_HEADER_HPP_
#define INCLUDES_GCC_TREE_HEADER_HPP_

#include <memory>

namespace ft {

template <typename Key, typename Val, typename KeyOfValue, typename Compare, typename Alloc = std::allocator<Val> >
class AATree {
  typename Alloc::template rebind<Val>::other                        __Node_allocator;
  typedef typename Alloc::template rebind<Val>::other::pointer       __AANodePtr;
  typedef typename Alloc::template rebind<Val>::other::const_pointer __AANodeConstPtr;

 public:
  typedef Key        key_type;
  typedef Val        value_type;
  typedef Val*       pointer;
  typedef const Val* const_pointer;
  typedef Val&       reference;
  typedef const Val& const_reference;
  typedef size_t     size_type;
  typedef ptrdiff_t  difference_type;
  typedef Alloc      allocator_type;
};

}  // namespace ft

#endif  // INCLUDES_GCC_TREE_HEADER_HPP_
