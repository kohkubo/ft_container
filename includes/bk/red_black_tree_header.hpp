#ifndef INCLUDES_RED_BLACK_TREE_HEADER_HPP_
#define INCLUDES_RED_BLACK_TREE_HEADER_HPP_

#include <algorithm>

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
  static __container_value_type const& __get_value(__node_value_type const& __v) { return __v; }
  static __container_value_type*       __get_ptr(__node_value_type& __n) { return _VSTD::addressof(__n); }
};

template <class _Key, class _Tp>
struct __tree_key_value_types<__value_type<_Key, _Tp> > {
  typedef _Key                       key_type;
  typedef _Tp                        mapped_type;
  typedef __value_type<_Key, _Tp>    __node_value_type;
  typedef std::pair<const _Key, _Tp> __container_value_type;
  typedef __container_value_type     __map_value_type;
  static const bool                  __is_map = true;
  static key_type const&             __get_key(__node_value_type const& __t) { return __t.__get_value().first; }
  template <class _Up>
  static typename std::enable_if<__is_same_uncvref<_Up, __container_value_type>::value, key_type const&>::type
  __get_key(_Up& __t) {
    return __t.first;
  }
  static __container_value_type const& __get_value(__node_value_type const& __t) { return __t.__get_value(); }
  template <class _Up>
  static typename std::enable_if<__is_same_uncvref<_Up, __container_value_type>::value,
                                 __container_value_type const&>::type
  __get_value(_Up& __t) {
    return __t;
  }
  static __container_value_type* __get_ptr(__node_value_type& __n) { return _VSTD::addressof(__n.__get_value()); }
};

template <class _Tp, class _AllocPtr, class _KVTypes = __tree_key_value_types<_Tp>, bool = _KVTypes::__is_map>
struct __tree_map_pointer_types {};

template <class _Tp, class _AllocPtr, class _KVTypes>
struct __tree_map_pointer_types<_Tp, _AllocPtr, _KVTypes, true> {
  typedef typename _KVTypes::__map_value_type                        _Mv;
  typedef typename std::__rebind_pointer<_AllocPtr, _Mv>::type       __map_value_type_pointer;
  typedef typename std::__rebind_pointer<_AllocPtr, const _Mv>::type __const_map_value_type_pointer;
};

template <class _VoidPtr>
struct __tree_node_base_types {
  typedef _VoidPtr                                                         __void_pointer;
  typedef __tree_node_base<__void_pointer>                                 __node_base_type;
  typedef typename std::__rebind_pointer<_VoidPtr, __node_base_type>::type __node_base_pointer;
  typedef __tree_end_node<__node_base_pointer>                             __end_node_type;
  typedef typename std::__rebind_pointer<_VoidPtr, __end_node_type>::type  __end_node_pointer;
  typedef __end_node_pointer                                               __parent_pointer;

 private:
};

template <class _VoidPtr>
class __tree_node_base : public __tree_node_base_types<_VoidPtr>::__end_node_type {
  typedef __tree_node_base_types<_VoidPtr> _NodeBaseTypes;

 public:
  typedef typename _NodeBaseTypes::__node_base_pointer pointer;
  typedef typename _NodeBaseTypes::__parent_pointer    __parent_pointer;
  pointer                                              __right_;
  __parent_pointer                                     __parent_;
  bool                                                 __is_black_;
  pointer __parent_unsafe() const { return static_cast<pointer>(__parent_); }
  void    __set_parent(pointer __p) { __parent_ = static_cast<__parent_pointer>(__p); }

 private:
  ~__tree_node_base()                       = delete;
  __tree_node_base(__tree_node_base const&) = delete;
  __tree_node_base& operator=(__tree_node_base const&) = delete;
};

template <class _NodePtr, class _NodeT = typename std::pointer_traits<_NodePtr>::element_type>
struct __tree_node_types;

template <class _NodePtr, class _Tp, class _VoidPtr>
struct __tree_node_types<_NodePtr, __tree_node<_Tp, _VoidPtr> >
    : public __tree_node_base_types<_VoidPtr>, __tree_key_value_types<_Tp>, __tree_map_pointer_types<_Tp, _VoidPtr> {
  typedef __tree_node_base_types<_VoidPtr>        __base;
  typedef __tree_key_value_types<_Tp>             __key_base;
  typedef __tree_map_pointer_types<_Tp, _VoidPtr> __map_pointer_base;

 public:
  typedef typename pointer_traits<_NodePtr>::element_type                         __node_type;
  typedef _NodePtr                                                                __node_pointer;
  typedef _Tp                                                                     __node_value_type;
  typedef typename std::__rebind_pointer<_VoidPtr, __node_value_type>::type       __node_value_type_pointer;
  typedef typename std::__rebind_pointer<_VoidPtr, const __node_value_type>::type __const_node_value_type_pointer;
  typedef typename __base::__end_node_pointer                                     __iter_pointer;

 private:
};

template <class _ValueTp, class _VoidPtr>
struct __make_tree_node_types {
  typedef typename std::__rebind_pointer<_VoidPtr, __tree_node<_ValueTp, _VoidPtr> >::type _NodePtr;
  typedef __tree_node_types<_NodePtr>                                                      type;
};

template <class T, class Compare, class Alloc = std::allocator<T> >
class tree {
 public:
  typedef T       value_type;
  typedef Compare value_compare;
  typedef Alloc   allocator_type;

 private:
  typedef std::allocator_traits<allocator_type>                                                    __alloc_traits;
  typedef typename __make_tree_node_types<value_type, typename __alloc_traits::void_pointer>::type _NodeTypes;
  typedef typename _NodeTypes::key_type                                                            key_type;

 public:
  typedef typename _NodeTypes::__node_value_type      __node_value_type;
  typedef typename _NodeTypes::__container_value_type __container_value_type;
  typedef typename __alloc_traits::pointer            pointer;
  typedef typename __alloc_traits::const_pointer      const_pointer;
  typedef typename __alloc_traits::size_type          size_type;
  typedef typename __alloc_traits::difference_type    difference_type;

 public:
  typedef typename _NodeTypes::__void_pointer                               __void_pointer;
  typedef typename _NodeTypes::__node_type                                  __node;
  typedef typename _NodeTypes::__node_pointer                               __node_pointer;
  typedef typename _NodeTypes::__node_base_type                             __node_base;
  typedef typename _NodeTypes::__node_base_pointer                          __node_base_pointer;
  typedef typename _NodeTypes::__end_node_type                              __end_node_t;
  typedef typename _NodeTypes::__end_node_pointer                           __end_node_ptr;
  typedef typename _NodeTypes::__parent_pointer                             __parent_pointer;
  typedef typename _NodeTypes::__iter_pointer                               __iter_pointer;
  typedef typename std::__rebind_alloc_helper<__alloc_traits, __node>::type __node_allocator;
  typedef std::allocator_traits<__node_allocator>                           __node_traits;

 private:
  __iter_pointer                                         __begin_node_;
  std::__compressed_pair<__end_node_t, __node_allocator> __pair1_;
  std::__compressed_pair<size_type, value_compare>       __pair3_;
}

#endif  // INCLUDES_RED_BLACK_TREE_HEADER_HPP_
