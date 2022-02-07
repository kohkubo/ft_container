#ifndef INCLUDES_RB_TREE_HPP_
#define INCLUDES_RB_TREE_HPP_

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
  static const bool __is_map = true;
};

template <class _Tp, class _NodePtr, class _DiffType>
class __tree_iterator {
  typedef typename pointer_traits<_NodePtr>::element_type __node_type;
  typedef _NodePtr                                        __node_pointer;
  typedef pointer_traits<__node_pointer>                  __pointer_traits;
  __node_pointer __ptr_;

 public:
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef _Tp                             value_type;
  typedef _DiffType                       difference_type;
  typedef value_type&                     reference;
  typedef _Tp*                            pointer;

  __node_pointer                          base() const { return __ptr_; }

  __tree_iterator() : __ptr_() {}
  __tree_iterator(__node_pointer __p) : __ptr_(__p) {}
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

template <class _Tp, class _NodePtr, class _DiffType>
class __tree_const_iterator {
  typedef typename pointer_traits<_NodePtr>::element_type __node_type;
  typedef _NodePtr                                        __node_pointer;
  typedef pointer_traits<__node_pointer>                  __pointer_traits;
  __node_pointer __ptr_;
  typedef __tree_iterator<_Tp, _NodePtr, _DiffType> __non_const_iterator;

 public:
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef _Tp                             value_type;
  typedef _DiffType                       difference_type;
  typedef const value_type&                     reference;
  typedef _Tp*                            pointer;

  __node_pointer                          base() const { return __ptr_; }

  __tree_const_iterator() : __ptr_() {}
  __tree_const_iterator(__non_const_iterator __p) : __ptr_(__p) {}
  __tree_const_iterator& operator=(const __tree_const_iterator& __x) {
    __ptr_ = __x.__ptr_;
    return *this;
  }
  reference        operator*() const { return __ptr_->__value_; }
  pointer          operator->() const { return &__ptr_->__value_; }
  __tree_const_iterator& operator++() {
    __ptr_ = __tree_next(__ptr_);
    return *this;
  }
  __tree_const_iterator operator++(int) {
    __tree_const_iterator __tmp(*this);
    ++(*this);
    return __tmp;
  }
  __tree_const_iterator& operator--() {
    __ptr_ = __tree_prev(__ptr_);
    return *this;
  }
  __tree_const_iterator operator--(int) {
    __tree_const_iterator __tmp(*this);
    --(*this);
    return __tmp;
  }
  friend bool operator==(const __tree_const_iterator& __x,
                         const __tree_const_iterator& __y) {
    return __x.__ptr_ == __y.__ptr_;
  }
  friend bool operator!=(const __tree_const_iterator& __x,
                         const __tree_const_iterator& __y) {
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
  typedef __tree_const_iterator<value_type, __node_pointer, difference_type>
      const_iterator;

 public:
  __node_pointer   __begin_node_;
  __node_pointer   __end_node_;
  __node_allocator __node_alloc_;
  size_type        __size_;
  key_compare      __comp_;

 public:
  allocator_type    __alloc() const { return allocator_type(__node_alloc()); }
  size_type&        size() { return __size_; }
  __node_allocator& __node_alloc() { return __node_alloc_; }

 public:
  __tree()
      : __size_(0), __comp_(key_compare()), __node_alloc_(__node_allocator()) {
    __end_node_ = __node_alloc_.allocate(1);
    __node_alloc_.construct(__end_node_, __node_value_type());
    __end_node_->__parent_ = __end_node_->__right_ = NULL;
    __end_node_->__left_                           = NULL;
    __begin_node_                                  = __end_node_;
  }
  explicit __tree(const key_compare&    __comp,
                  const allocator_type& alloc = allocator_type())
      : __size_(0), __comp_(__comp), __node_alloc_(alloc) {
    __end_node_ = __node_alloc_.allocate(1);
    __node_alloc_.construct(__end_node_, __node_value_type());
    __end_node_->__parent_ = __end_node_->__right_ = NULL;
    __end_node_->__left_                           = NULL;
    __begin_node_                                  = __end_node_;
  }
  template <class _InputIterator>
  __tree(_InputIterator __first, _InputIterator __last,
         const key_compare&    __comp  = key_compare(),
         const allocator_type& __alloc = allocator_type())
      : __size_(0), __comp_(__comp), __node_alloc_(__alloc) {
    __end_node_ = __node_alloc_.allocate(1);
    __node_alloc_.construct(__end_node_, __node_value_type());
    __end_node_->__parent_ = __end_node_->__right_ = NULL;
    __end_node_->__left_                           = NULL;
    __begin_node_                                  = __end_node_;
    insert(__first, __last);
  }
  allocator_type get_allocator() const { return allocator_type(__node_alloc_); }
  template <class _ForwardIterator>
  void __assign_unique(_ForwardIterator __first, _ForwardIterator __last);
  ~__tree() { __destroy(__end_node_); }
  // ===========================================================================
  // accese
  // ===========================================================================
  __node_pointer  __root() const { return __end_node_->__left_; }
  __node_pointer* __root_ptr() { return &(__end_node_->__left_); }
  // ===========================================================================
  // iterator
  // ===========================================================================
  iterator        begin() { return iterator(__begin_node_); }
  iterator        end() { return iterator(__end_node_); }
  size_type       max_size() const { return __node_alloc().max_size(); }
  // ===========================================================================
  // Modifiers
  // ===========================================================================
  void            clear() {
    __destroy(__root());
    __size_              = 0;
    __begin_node_        = __end_node_;
    __end_node_->__left_ = NULL;
  }
  pair<iterator, bool> insert(const value_type& __v) {
    __node_pointer  __parent;
    __node_pointer& __child    = __find_equal(__parent, __v.first);
    bool            __inserted = false;
    if (__child == NULL) {
      __child            = __create_node(__v);
      __child->__parent_ = __parent;
      if (__begin_node_->__left_ != NULL) {
        __begin_node_ = __begin_node_->__left_;
      }
      __tree_balance_after_insert(__root(), __child);
      ++__size_;
      __inserted = true;
    }
    return pair<iterator, bool>(iterator(__child), __inserted);
  }
  iterator insert(iterator __hint, const value_type& __v) {
    __node_pointer  __parent;
    __node_pointer& __child = __find_equal(__parent, __v.first, __hint.base());
    if (__child == NULL) {
      __child            = __create_node(__v);
      __child->__parent_ = __parent;
      __tree_balance_after_insert(__root(), __child);
      ++__size_;
    }
    return iterator(__child);
  }
  template <class _InputIterator>
  void insert(_InputIterator __first, _InputIterator __last) {
    for (; __first != __last; ++__first) {
      insert(*__first);
    }
  }
  iterator erase(iterator __i) {
    __node_pointer __np = __i.base();
    iterator       __r  = __remove_node_pointer(__np);
    __node_alloc_.destroy(__np);
    __node_alloc_.deallocate(__np, 1);
    return __r;
  }
  iterator erase(iterator __first, iterator __last) {
    for (; __first != __last; ++__first) {
      erase(__first);
    }
    return __last;
  }
  size_type erase(const key_type& __key) {
    iterator __it = find(__key);
    if (__it != __end_node_) {
      erase(__it);
      return 1;
    }
    return 0;
  }
  void swap(__tree& __other) {
    __node_pointer    __tmp_begin_node = __begin_node_;
    __node_pointer    __tmp_end_node   = __end_node_;
    size_type         __tmp_size       = __size_;
    key_compare       __tmp_comp       = __comp_;
    __node_allocator& __tmp_node_alloc = __node_alloc_;
    __begin_node_                      = __other.__begin_node_;
    __end_node_                        = __other.__end_node_;
    __size_                            = __other.__size_;
    __comp_                            = __other.__comp_;
    __node_alloc_                      = __other.__node_alloc_;
    __other.__begin_node_              = __tmp_begin_node;
    __other.__end_node_                = __tmp_end_node;
    __other.__size_                    = __tmp_size;
    __other.__comp_                    = __tmp_comp;
    __other.__node_alloc_              = __tmp_node_alloc;
  }
  // ===========================================================================
  // search
  // ===========================================================================
  size_type count(const key_type& __k) const {
    __node_pointer __node = find(__k);
    return __node == NULL ? 0 : 1;
  }
  iterator find(const key_type& __k) {
    iterator __p = lower_bound(__k);
    if (__p != end() && !__comp_(__k, __p->first)) {
      return __p;
    }
    return end();
  }
  value_type equal_range(const key_type& __k) {
    return pair<iterator, iterator>(lower_bound(__k), upper_bound(__k));
  }
  // lower_bound(const key_type&)
  // keyより大きい、または等しい最初の要素を指すイテレータを返します。
  iterator lower_bound(const key_type& __k) {
    __node_pointer __result;
    __node_pointer __node = __root();
    while (__node != NULL) {
      if (!__comp_(__node->__value_.first, __k)) {
        __result = __node;
        __node   = __node->__left_;
      } else {
        __node = __node->__right_;
      }
    }
    return iterator(__result);
  }
  iterator upper_bound(const key_type& __k) {
    __node_pointer __result;
    __node_pointer __node = __root();
    while (__node != NULL) {
      if (!__comp_(__k, __node->__value_.first)) {
        __result = __node;
        __node   = __node->__left_;
      } else {
        __node = __node->__right_;
      }
    }
    return iterator(__result);
  }
  // ===========================================================================
  // observers
  // ===========================================================================
  key_compare     value_comp() const { return __comp_; }
  key_compare     key_comp() const { return __comp_; }
  // ===========================================================================
  // private
  // ===========================================================================
  // Find place to insert if __k doesn't exist
  // Set __parent to parent of null leaf
  // Return reference to null leaf
  // If __k exists, set parent to node of __k and return reference to node of
  // __k
  __node_pointer& __find_equal(__node_pointer& __parent, const key_type& __k) {
    __node_pointer  __nd = __root();
    __node_pointer* __p  = __root_ptr();
    if (__nd != NULL) {
      while (true) {
        if (__comp_(__k, __nd->__value_.first)) {
          if (__nd->__left_ != NULL) {
            __p  = &(__nd->__left_);
            __nd = __nd->__left_;
          } else {
            __parent = __nd;
            return __parent->__left_;
          }
        } else if (__comp_(__nd->__value_.first, __k)) {
          if (__nd->__right_ != NULL) {
            __p  = &(__nd->__right_);
            __nd = __nd->__right_;
          } else {
            __parent = __nd;
            return __nd->__right_;
          }
        } else {
          __parent = __nd;
          return *__p;
        }
      }
    }
    __parent = __end_node_;
    return __parent->__left_;
  }
  __node_pointer& __find_equal(__node_pointer& __parent, const key_type& __k,
                               __node_pointer __hint) {
    if (__hint == __end_node_ || __comp_(__k, __hint->__value_.first)) {
      if (__hint == __begin_node_ || __comp_(__hint->__value_.first, __k)) {
        if (__hint->__left_ == NULL) {
          __parent = __hint;
          return __hint->__left_;
        } else {
          __parent = __hint;
          return __hint->__right_;
        }
      }
      return __find_equal(__parent, __k);
    } else if (__comp_(__hint->__value_.first, __k)) {
      __node_pointer __next = __tree_next(__hint);
      if (__next == __end_node_ || __comp_(__k, __next->__value_.first)) {
        if (__hint->__right_ == NULL) {
          __parent = __hint;
          return __hint->__right_;
        } else {
          __parent = __hint;
          return __hint->__left_;
        }
      }
      return __find_equal(__parent, __k);
    }
    __parent = __hint;
    return __parent;
  }
  void __destroy(__node_pointer __nd) {
    if (__nd != NULL) {
      __destroy(__nd->__left_);
      __destroy(__nd->__right_);
      __node_alloc_.destroy(__nd);
      __node_alloc_.deallocate(__nd, 1);
    }
  }
  __node_pointer __create_node(const value_type& __v) {
    __node_pointer __new_node = __node_alloc_.allocate(1);
    __node_alloc_.construct(__new_node, __v);
    return __new_node;
  }
  iterator __remove_node_pointer(__node_pointer __ptr) {
    iterator __it(__ptr);
    ++__it;
    if (__begin_node_ == __ptr) {
      __begin_node_ = __it.base();
    }
    --__size_;
    __tree_remove(__root(), __ptr);
    return __it;
  }
};

// =============================================================================
// non-member functions
// =============================================================================
template <class _Tp, class _Compare, class _Allocator>
inline bool operator==(const __tree<_Tp, _Compare, _Allocator>& __x,
                       const __tree<_Tp, _Compare, _Allocator>& __y) {
  return __x.size() == __y.size() && equal(__x.begin(), __x.end(), __y.begin());
}
template <class _Tp, class _Compare, class _Allocator>
inline bool operator<(const __tree<_Tp, _Compare, _Allocator>& __x,
                      const __tree<_Tp, _Compare, _Allocator>& __y) {
  return lexicographical_compare(__x.begin(), __x.end(), __y.begin(),
                                 __y.end());
}
template <class _Tp, class _Compare, class _Allocator>
inline bool operator!=(const __tree<_Tp, _Compare, _Allocator>& __x,
                       const __tree<_Tp, _Compare, _Allocator>& __y) {
  return !(__x == __y);
}
template <class _Tp, class _Compare, class _Allocator>
inline bool operator>(const __tree<_Tp, _Compare, _Allocator>& __x,
                      const __tree<_Tp, _Compare, _Allocator>& __y) {
  return __y < __x;
}
template <class _Tp, class _Compare, class _Allocator>
inline bool operator<=(const __tree<_Tp, _Compare, _Allocator>& __x,
                       const __tree<_Tp, _Compare, _Allocator>& __y) {
  return !(__y < __x);
}
template <class _Tp, class _Compare, class _Allocator>
inline bool operator>=(const __tree<_Tp, _Compare, _Allocator>& __x,
                       const __tree<_Tp, _Compare, _Allocator>& __y) {
  return !(__x < __y);
}
template <class _Tp, class _Compare, class _Allocator>
inline void swap(__tree<_Tp, _Compare, _Allocator>& __x,
                 __tree<_Tp, _Compare, _Allocator>& __y) {
  __x.swap(__y);
}
}  // namespace ft

#endif  // INCLUDES_RB_TREE_HPP_
