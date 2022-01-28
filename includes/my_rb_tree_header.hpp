#ifndef INCLUDES_MY_RB_TREE_HEADER_HPP_
#define INCLUDES_MY_RB_TREE_HEADER_HPP_

#include <memory>

#include "pair.hpp"
#include "pointer_traits.hpp"
#include "type_traits.hpp"

namespace ft {
template <class _Key, class _Value>
struct __value_type;

template <class _Tp>
class __tree_node {
 public:
  typedef __tree_node*     pointer;
  typedef __tree_node      __end_node_type;
  typedef __end_node_type* __end_node_pointer;

 public:
  typedef _Tp       __node_value_type;
  __node_value_type __value_;
  pointer           __right_;
  pointer           __left_;
  pointer           __parent_;
  bool              __is_black_;
};

template <class _Key, class _Tp>
class __tree_node<__value_type<_Key, _Tp> > {
  // ===========================================================================
  // tree_node_type
  // ===========================================================================
 public:
  typedef _Key                           key_type;
  typedef _Tp                            mapped_type;
  typedef pair<const _Key, _Tp>          __node_value_type;
  typedef __node_value_type*             __node_value_type_pointer;
  typedef pair<const _Key, _Tp>          __container_value_type;
  typedef __container_value_type         __map_value_type;
  typedef __tree_node<__node_value_type> __node_type;
  typedef __node_type*                   __node_pointer;
  typedef __node_pointer                 __iter_pointer;

  // ===========================================================================
  // tree_node
  // ===========================================================================
 public:
  typedef __tree_node*     pointer;
  typedef __tree_node      __end_node_type;
  typedef __end_node_type* __end_node_pointer;

 public:
  __node_value_type              __value_;
  pointer                        __right_;
  pointer                        __left_;
  pointer                        __parent_;
  bool                           __is_black_;
  // ===========================================================================
  // tree_node_type
  // ===========================================================================
  static const bool              __is_map = true;
  static __container_value_type* __get_ptr(__node_value_type& __n) {
    return addressof(__n.first());
  }
};

template <class _NodePtr, class _Tp>
struct __tree_node_types {
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

template <class _NodePtr, class _Key, class _Tp>
struct __tree_node_types<__value_type<_Key, _Tp> > {
  typedef _Key                    key_type;
  typedef _Tp                     mapped_type;
  typedef __value_type<_Key, _Tp> __node_value_type;
  typedef __node_value_type*      __node_value_type_pointer;
  typedef pair<const _Key, _Tp>   __container_value_type;
  typedef __container_value_type  __map_value_type;

 public:
  typedef typename pointer_traits<_NodePtr>::element_type __node_type;
  typedef _NodePtr                                        __node_pointer;
  typedef _NodePtr                                        __iter_pointer;
  static const bool                                       __is_map = true;
  static key_type const& __get_key(__node_value_type const& __t) {
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
    return addressof(__n.__get_value());
  }
};

template <class _Tp, class _NodePtr, class _DiffType>
class __tree_iterator {
  typedef __tree_iterator<_Tp, _NodePtr, _DiffType> iterator;
  typedef __tree_node_types<_NodePtr, _Tp>          _NodeTypes;
  typedef _NodePtr                                  __node_pointer;
  typedef typename _NodeTypes::__node_pointer       __node_base_pointer;
  typedef typename _NodeTypes::__node_pointer       __end_node_pointer;
  typedef typename _NodeTypes::__node_pointer       __iter_pointer;
  typedef pointer_traits<__node_pointer>            __pointer_traits;

  iterator                                          __i_;

 public:
  typedef std::bidirectional_iterator_tag                iterator_category;
  typedef _Tp                                            value_type;
  typedef _DiffType                                      difference_type;
  typedef value_type&                                    reference;
  typedef typename _NodeTypes::__node_value_type_pointer pointer;

  __tree_iterator() : __i_() {}

  reference        operator*() const { return __get_np()->__value_; }
  pointer          operator->() const { return pointer(__get_np()->__value_); }

  __tree_iterator& operator++() {
    __i_ = static_cast<iterator>(__tree_next(__i_));
    return *this;
  }
  __tree_iterator operator++(int) {
    __tree_iterator __tmp(*this);
    ++(*this);
    return __tmp;
  }
  __tree_iterator& operator--() {
    __i_ = static_cast<iterator>(__tree_prev(__i_));
    return *this;
  }
  __tree_iterator operator--(int) {
    __tree_iterator __tmp(*this);
    --(*this);
    return __tmp;
  }
  inline __node_pointer __tree_min(__node_pointer __x) {
    while (__x->__left_ != NULL)
      __x = __x->__left_;
    return __x;
  }
  inline __node_pointer __tree_max(__node_pointer __x) {
    while (__x->__right_ != NULL)
      __x = __x->__right_;
    return __x;
  }
  inline __node_pointer __tree_next(__node_pointer __x) {
    if (__x->__right_ != NULL) {
      return __tree_min(__x->__right_);
    }
    while (!__tree_is_left_child(__x)) {
      __x = __x->__parent_;
    }
    return __x->__parent_;
  }
  inline __node_pointer __tree_prev(__node_pointer __x) {
    if (__x->__left_ != NULL) {
      return __tree_max(__x->__left_);
    }
    while (__tree_is_left_child(__x)) {
      __x = __x->__parent_;
    }
    return __x->__parent_;
  }
  inline bool __tree_is_left_child(__node_pointer __x) {
    return __x == __x->__parent_->__left_;
  }

 private:
  explicit __tree_iterator(__node_pointer __x) : __i_(__x) {}
  __node_pointer __get_np() const { return static_cast<__node_pointer>(__i_); }
};

template <class _Tp, class _Compare = std::less<_Tp>,
          class _Allocator = std::allocator<_Tp> >
class __tree {
  typedef _Tp        value_type;
  typedef _Compare   value_compare;
  typedef _Allocator allocator_type;

 private:
  typedef __tree_node_types<value_type> _NodeTypes;
  typedef typename _NodeTypes::key_type key_type;

 public:
  typedef typename _NodeTypes::__node_value_type      __node_value_type;
  typedef typename _NodeTypes::__container_value_type __container_value_type;
  typedef typename allocator_type::pointer            pointer;
  typedef typename allocator_type::const_pointer      const_pointer;
  typedef typename allocator_type::size_type          size_type;
  typedef typename allocator_type::difference_type    difference_type;

 public:
  typedef _NodeTypes     __node;
  typedef __node*        __node_pointer;
  typedef __node         __node_base;
  typedef __node_pointer __node_base_pointer;
  typedef __node         __end_node_t;
  typedef __end_node_t*  __end_node_ptr;
  typedef __node_pointer __parent_pointer;
  typedef __node_pointer __iter_pointer;
  typedef
      typename allocator_type::template rebind<__node>::other __node_allocator;
  // typedef typename __rebind_alloc_helper<__alloc_traits, __node>::type
  // __node_allocator;

  typedef __tree_iterator<value_type, __node_pointer, difference_type> iterator;

 private:
  __iter_pointer   __begin_node_;
  __iter_pointer   __end_node_;
  __node_pointer   __end_node_type_;
  __node_allocator __node_alloc_;
  size_type        __size_;
  value_compare    __comp_;
  __node_pointer   __root_;

 public:
  __iter_pointer __end_node() const { return __end_node_; }
  allocator_type __alloc() const { return allocator_type(__node_alloc()); }
  value_compare& value_comp() { return __comp_; }
  size_type&     size() { return __size_; }

 private:
  __iter_pointer    __begin_node() const { return __begin_node_; }
  __node_allocator& __node_alloc() { return __node_alloc_; }

 public:
  explicit __tree(const value_compare& __comp);
  explicit __tree(const allocator_type& __a);
  __tree(const value_compare& __comp, const allocator_type& __a);
  __tree(const __tree& __t);
  __tree& operator=(const __tree& __t);
  template <class _ForwardIterator>
  void __assign_unique(_ForwardIterator __first, _ForwardIterator __last);
  ~__tree();

  void      clear();
  void      swap(__tree& __t);

  // ===========================================================================
  // iterator
  // ===========================================================================
  iterator  begin() { return iterator(__begin_node()); }
  iterator  end() { return iterator(__end_node()); }
  size_type max_size() const { return __node_alloc().max_size(); }
  // ===========================================================================
  // Modifiers
  // ===========================================================================
  // insert
  // pair<iterator, bool> __insert_unique(const value_type& __x);
  // {
  //   __node_pointer  __parent;
  //   __node_pointer& __child   = __find_equal(__parent, __x.first);
  //   bool            __insertd = false;
  //   if (__child == NULL) {
  //     __ __child = __node_alloc().allocate(1);
  //     __node_alloc().construct(__child, __x);
  //     __child->__parent_ = __parent;
  //     __insertd          = true;
  //   }
  // }
};
}  // namespace ft

#endif  // INCLUDES_MY_RB_TREE_HEADER_HPP_
