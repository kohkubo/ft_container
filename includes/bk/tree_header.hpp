#ifndef INCLUDES_TREE_HEADER_HPP_
#define INCLUDES_TREE_HEADER_HPP_

#include <memory>

#include "pair.hpp"
#include "type_traits.hpp"
#include "pointer_traits.hpp"

namespace ft {

template <class _Tp, class _Compare, class _Allocator>
class __tree;
template <class _Tp, class _NodePtr, class _DiffType>
class __tree_iterator;
template <class _Tp, class _ConstNodePtr, class _DiffType>
class __tree_const_iterator;

template <class _Pointer>
class __tree_end_node;
template <class _VoidPtr>
class __tree_node_base;
template <class _Tp, class _VoidPtr>
class __tree_node;

template <class _Key, class _Value>
struct __value_type;

template <class _Allocator>
class __map_node_destructor;
template <class _TreeIterator>
class __map_iterator;
template <class _TreeIterator>
class __map_const_iterator;

template <class _Tp>
struct __tree_key_value_types {
  typedef _Tp                          key_type;
  typedef _Tp                          __node_value_type;
  typedef _Tp                          __container_value_type;
  static const bool                    __is_map = false;

  static key_type const&               __get_key(_Tp const& __v) { return __v; }
  static __container_value_type const& __get_value(
      __node_value_type const& __v) {
    return __v;
  }
  static __container_value_type* __get_ptr(__node_value_type& __n) {
    return _VSTD::addressof(__n);
  }
};

template <class _Key, class _Tp>
struct __tree_key_value_types<__value_type<_Key, _Tp> > {
  typedef _Key                    key_type;
  typedef _Tp                     mapped_type;
  typedef __value_type<_Key, _Tp> __node_value_type;
  typedef pair<const _Key, _Tp>   __container_value_type;
  typedef __container_value_type  __map_value_type;
  static const bool               __is_map = true;

  static key_type const&          __get_key(__node_value_type const& __t) {
    return __t.__get_value().first;
  }
  template <class _Up>
  static
      typename enable_if<__is_same_uncvref<_Up, __container_value_type>::value,
                         key_type const&>::type
      __get_key(_Up& __t) {
    return __t.first;
  }

  static __container_value_type const& __get_value(
      __node_value_type const& __t) {
    return __t.__get_value();
  }

  template <class _Up>

  static
      typename enable_if<__is_same_uncvref<_Up, __container_value_type>::value,
                         __container_value_type const&>::type
      __get_value(_Up& __t) {
    return __t;
  }

  static __container_value_type* __get_ptr(__node_value_type& __n) {
    return _VSTD::addressof(__n.__get_value());
  }
};

template <class _Tp, class _VoidPtr>
class __tree_node {
 public:
  typedef __tree_node*     pointer;
  typedef __tree_node      __end_node_type;
  typedef __end_node_type* __end_node_pointer;

 public:
  typedef _Tp       __node_value_type;
  __node_value_type __value_;
  // typedef __end_node_pointer __parent_pointer;
  pointer           __right_;
  pointer           __left_;
  pointer           __parent_;
  bool              __is_black_;
  pointer           __parent_unsafe() const { return __parent_; }
  void              __set_parent(pointer __p) { __parent_ = __p; }
};


template <class _NodePtr, class _NodeT>
struct __tree_node_types;

template <class _NodePtr, class _Tp, class _VoidPtr>
struct __tree_node_types<_NodePtr, __tree_node<_Tp, _VoidPtr> >
    : public __tree_node<_Tp, _VoidPtr>::__end_node_pointer,
      __tree_key_value_types<_Tp> {
  typedef __tree_node<_Tp, _VoidPtr>  __base;
  typedef __tree_key_value_types<_Tp> __key_base;

 public:
  typedef typename pointer_traits<_NodePtr>::element_type __node_type;
  typedef _NodePtr                                        __node_pointer;
  typedef _Tp                                             __node_value_type;
  typedef typename __rebind_pointer<_VoidPtr, __node_value_type>::type
      __node_value_type_pointer;
  typedef typename __rebind_pointer<_VoidPtr, const __node_value_type>::type
                                              __const_node_value_type_pointer;
  typedef typename __base::__end_node_pointer __iter_pointer;

 private:
};

template <class _Tp, class _NodePtr, class _DiffType>
class __tree_iterator {
  typedef __tree_node_types<_NodePtr>              _NodeTypes;
  typedef _NodePtr                                 __node_pointer;
  typedef typename _NodeTypes::__node_base_pointer __node_base_pointer;
  typedef typename _NodeTypes::__end_node_pointer  __end_node_pointer;
  typedef typename _NodeTypes::__iter_pointer      __iter_pointer;
  typedef std::pointer_traits<__node_pointer>      __pointer_traits;
}

template <class _Tp, class _Compare = std::less<_Tp>,
          class _Allocator = std::allocator<_Tp> >
class __tree {
  typedef _Tp                                   value_type;
  typedef _Compare                              value_compare;
  typedef _Allocator                            allocator_type;
  typedef typename allocator_type::void_pointer __void_pointer;

 private:
  // なぜこれを行う必要があるのか
  // 一度voidポインタにして、値のチェックを行っている
  typedef __tree_node<value_type, __void_pointer> _NodeTypes;
  typedef typename _NodeTypes::key_type           key_type;

 public:
  typedef typename _NodeTypes::__node_value_type      __node_value_type;
  typedef typename _NodeTypes::__container_value_type __container_value_type;
  typedef typename allocator_type::pointer            pointer;
  typedef typename allocator_type::const_pointer      const_pointer;
  typedef typename allocator_type::size_type          size_type;
  typedef typename allocator_type::difference_type    difference_type;

 public:
  typedef _NodeTypes                              __node;
  typedef __node*                                 __node_pointer;
  typedef _NodeTypes                              __node_base;
  typedef __node_base*                            __node_base_pointer;
  typedef typename _NodeTypes::__end_node_type    __end_node_t;
  typedef typename _NodeTypes::__end_node_pointer __end_node_ptr;
  typedef typename _NodeTypes::__parent_pointer   __parent_pointer;
  typedef typename _NodeTypes::__iter_pointer     __iter_pointer;
  typedef typename __rebind_alloc_helper<allocator_type, __node>::type
                                                  __node_allocator;
  typedef std::allocator_traits<__node_allocator> __node_traits;
};

}  // namespace ft

#endif  // INCLUDES_TREE_HEADER_HPP_
