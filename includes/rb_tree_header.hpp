#ifndef INCLUDES_RB_TREE_HEADER_HPP_
#define INCLUDES_RB_TREE_HEADER_HPP_

#include <iostream>
#include <memory>

#include "pair.hpp"
#include "pointer_traits.hpp"
#include "tree_util.hpp"
#include "type_traits.hpp"

namespace ft {

template <class _Tp>
class __tree_node;

template <class _Key, class _Tp>
class __tree_node<pair<const _Key, _Tp> > {
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
  __node_value_type __value_;
  pointer           __right_;
  pointer           __left_;
  pointer           __parent_;
  bool              __is_black_;
  // ===========================================================================
  // construct/copy/destroy:
  // ===========================================================================
  __tree_node()
      : __right_(NULL), __left_(NULL), __parent_(NULL), __is_black_(false) {}
  __tree_node(const __node_value_type& __x)
      : __value_(__x),
        __right_(NULL),
        __left_(NULL),
        __parent_(NULL),
        __is_black_(false) {}
  ~__tree_node() {}

  // ===========================================================================
  // tree_node_type
  // ===========================================================================
 private:
  static const bool              __is_map = true;
  static __container_value_type* __get_ptr(__node_value_type& __n) {
    return addressof(__n.first());
  }
};

template <class _Tp, class _NodePtr, class _DiffType>
class __tree_iterator {
 public:
  typedef typename pointer_traits<_NodePtr>::element_type __node_type;
  typedef _NodePtr                                        __node_pointer;
  typedef typename __node_type::__node_pointer            __node_base_pointer;
  typedef typename __node_type::__node_pointer            __end_node_pointer;
  typedef typename __node_type::__node_pointer            __iter_pointer;
  typedef pointer_traits<__node_pointer>                  __pointer_traits;

 private:
  __node_pointer __ptr_;

 public:
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef _Tp                             value_type;
  typedef _DiffType                       difference_type;
  typedef value_type&                     reference;
  typedef _Tp*                            pointer;

  __node_pointer                          base() const { return __ptr_; }

  __tree_iterator() : __ptr_() {}
  __tree_iterator(__node_pointer __i) : __ptr_(__i) {}
  __tree_iterator& operator=(const __tree_iterator& __x) {
    __ptr_ = __x.__ptr_;
    return *this;
  }
  reference        operator*() const { return __ptr_->__value_; }
  pointer          operator->() const { return &__ptr_->__value_; }
  __tree_iterator& operator++() {
    __ptr_ = __tree_next(__ptr_);
    return *this;
  }
  __tree_iterator operator++(int) {
    __tree_iterator __tmp(*this);
    ++(*this);
    return __tmp;
  }
  __tree_iterator& operator--() {
    __ptr_ = __tree_prev(__ptr_);
    return *this;
  }
  __tree_iterator operator--(int) {
    __tree_iterator __tmp(*this);
    --(*this);
    return __tmp;
  }
  friend bool operator==(const __tree_iterator& __x,
                         const __tree_iterator& __y) {
    return __x.__ptr_ == __y.__ptr_;
  }
  friend bool operator!=(const __tree_iterator& __x,
                         const __tree_iterator& __y) {
    return __x.__ptr_ != __y.__ptr_;
  }
};

template <class _Tp, class _Compare, class _Allocator>
class __tree {
 public:
  typedef _Tp                                         value_type;
  typedef _Compare                                    key_compare;
  typedef _Allocator                                  allocator_type;
  typedef __tree_node<value_type>                     _NodeTypes;
  typedef typename _NodeTypes::key_type               key_type;

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

 public:
  __node_pointer   __begin_node_;
  __node_pointer   __end_node_;
  __node_allocator __node_alloc_;
  size_type        __size_;
  key_compare      __comp_;

 public:
  allocator_type    __alloc() const { return allocator_type(__node_alloc()); }
  key_compare       key_comp() const { return __comp_; }
  size_type&        size() { return __size_; }
  __node_allocator& __node_alloc() { return __node_alloc_; }

 public:
  __tree() {
    __size_       = 0;
    __comp_       = key_compare();
    __node_alloc_ = __node_allocator();
    __end_node_   = __node_alloc_.allocate(1);
    __node_alloc_.construct(__end_node_, __node_value_type());
    __end_node_->__parent_ = __end_node_->__right_ = NULL;
    __end_node_->__left_                           = NULL;
    __begin_node_                                  = __end_node_;
  }
  explicit __tree(const key_compare& __comp);
  explicit __tree(const allocator_type& __a);
  __tree(const key_compare& __comp, const allocator_type& __a);
  __tree(const __tree& __t);
  __tree&        operator=(const __tree& __t);
  allocator_type get_allocator() const { return allocator_type(__node_alloc_); }
  template <class _ForwardIterator>
  void __assign_unique(_ForwardIterator __first, _ForwardIterator __last);
  ~__tree();
  void                 swap(__tree& __t);
  // ===========================================================================
  // accese
  // ===========================================================================
  __node_pointer       __root() const { return __end_node_->__left_; }
  __node_pointer*      __root_ptr() { return &(__end_node_->__left_); }
  // ===========================================================================
  // iterator
  // ===========================================================================
  iterator             begin() { return iterator(__begin_node_); }
  iterator             end() { return iterator(__end_node_); }
  size_type            max_size() const { return __node_alloc().max_size(); }
  // ===========================================================================
  // Modifiers
  // ===========================================================================
  void                 clear();
  pair<iterator, bool> insert(const value_type& __v);
  iterator             insert(iterator __hint, const value_type& __v);
  template <class _InputIterator>
  void            insert(_InputIterator __first, _InputIterator __last);
  iterator        erase(iterator __pos);
  iterator        erase(iterator __f, iterator __l);
  size_type       erase(const key_type& __key);
  // ===========================================================================
  // search
  // ===========================================================================
  iterator        find(const key_type& __key);
  iterator        lower_bound(const key_type& __key);
  // ===========================================================================
  // observers
  // ===========================================================================
  key_compare     value_comp() const { return __comp_; }
  // ===========================================================================
  // private
  // ===========================================================================
  iterator        __lower_bound(const key_type& __k, __node_pointer __root);
  __node_pointer& __find_equal(__node_pointer& __parent, const key_type& __k);
  __node_pointer& __find_equal(__node_pointer& __parent, const key_type& __k,
                               __node_pointer __hint);
  void            __destroy(__node_pointer __nd);
  __node_pointer  __create_node(const value_type& __x);
  iterator        __remove_node_pointer(__node_pointer __ptr);
};

}  // namespace ft

#endif  // INCLUDES_RB_TREE_HEADER_HPP_
