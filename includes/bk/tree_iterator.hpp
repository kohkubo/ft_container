#ifndef INCLUDES_TREE_ITERATOR_HPP_
#define INCLUDES_TREE_ITERATOR_HPP_

#include <memory>

namespace ft {

template <class _VoidPtr>
struct __tree_node_base_types {
  typedef _VoidPtr                         __void_pointer;
  typedef __tree_node_base<__void_pointer> __node_base_type;
  typedef typename __rebind_pointer<_VoidPtr, __node_base_type>::type
                                               __node_base_pointer;
  typedef __tree_end_node<__node_base_pointer> __end_node_type;
  typedef typename std::__rebind_pointer<_VoidPtr, __end_node_type>::type
                             __end_node_pointer;
  typedef __end_node_pointer __parent_pointer;
};

template <class _NodePtr, class _Tp, class _VoidPtr>
struct __tree_node_types {
  typedef _NodePtr*                                            node_pointer;
  typedef _Tp*                                                 value_pointer;
  typedef _VoidPtr                                             void_pointer;
  typedef __tree_node_base_types<_VoidPtr>                     base;
  typedef __tree_key_value_types<_Tp>                          key_base;
  typedef __tree_map_pointer_types<_Tp, _VoidPtr>              map_pointer_base;
  typedef typename std::pointer_traits<_NodePtr>::element_type node_type;
  typedef _NodePtr                                             node_pointer;
  typedef _Tp                                                  node_value_type;
  typedef typename base::__end_node_pointer                    iter_pointer;
};

template <class _Tp, class _NodePtr, class _DiffType>
class __tree_iterator {
  typedef __tree_node_types<_NodePtr>           node_types;
  typedef _NodePtr                              node_pointer;
  typedef typename node_types::node_base_ptr    node_base_pointer;
  typedef typename node_types::end_node_pointer end_node_pointer;
  typedef typename node_types::iter_pointer     iter_pointer;
  typedef std::pointer_traits<node_pointer>     pointer_traits;
  iter_pointer                                  __ptr_;

 public:
  typedef _Tp                             value_type;
  typedef _DiffType                       difference_type;
  typedef _Tp*                            pointer;
  typedef _Tp&                            reference;
  typedef std::bidirectional_iterator_tag iterator_category;

  __tree_iterator() {}

 private:
  explicit __tree_iterator(node_pointer __x) : __ptr_(__x) {}
  explicit __tree_iterator(end_node_pointer __x) : __ptr_(__x) {}
  __node_pointer __get_np() const { return static_cast<node_pointer>(__ptr_); }
}

}  // namespace ft

#endif  // INCLUDES_TREE_ITERATOR_HPP_
