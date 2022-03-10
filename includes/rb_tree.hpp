#ifndef INCLUDES_RB_TREE_HPP_
#define INCLUDES_RB_TREE_HPP_

#include <iostream>
#include <memory>
#include <limits>

#include "pair.hpp"
#include "pointer_traits.hpp"
#include "reverse_iterator.hpp"
#include "tree_util.hpp"
#include "type_traits.hpp"

namespace ft {

// =============================================================================
// set tree_node
// =============================================================================
template <class _Tp>
class __tree_node {
  // ===========================================================================
  // tree_node_type
  // ===========================================================================
 public:
  typedef _Tp                            key_type;
  typedef key_type                       value_type;
  typedef value_type                     __node_value_type;
  typedef __tree_node<__node_value_type> __node_type;
  typedef __node_type*                   __node_pointer;
  // ===========================================================================
  // tree_node
  // ===========================================================================
 public:
  typedef __tree_node* pointer;

 public:
  __node_value_type __value_;
  pointer           __parent_;
  pointer           __right_;
  pointer           __left_;
  bool              __is_black_;
  // ===========================================================================
  // construct/copy/destroy:
  // ===========================================================================
  explicit __tree_node(const __node_value_type& __x)
      : __value_(__x),
        __parent_(NULL),
        __right_(NULL),
        __left_(NULL),
        __is_black_(false) {}
  ~__tree_node() {}
};

// =============================================================================
// map tree_node
// =============================================================================
template <class _Key, class _Tp>
class __tree_node<pair<const _Key, _Tp> > {
  // ===========================================================================
  // tree_node_type
  // ===========================================================================
 public:
  typedef _Key                           key_type;
  typedef _Tp                            mapped_type;
  typedef pair<const _Key, _Tp>          __node_value_type;
  typedef __tree_node<__node_value_type> __node_type;
  typedef __node_type*                   __node_pointer;
  // ===========================================================================
  // tree_node
  // ===========================================================================
 public:
  typedef __tree_node* pointer;

 public:
  __node_value_type __value_;
  pointer           __parent_;
  pointer           __right_;
  pointer           __left_;
  bool              __is_black_;
  // ===========================================================================
  // construct/copy/destroy:
  // ===========================================================================
  explicit __tree_node(const __node_value_type& __x)
      : __value_(__x),
        __parent_(NULL),
        __right_(NULL),
        __left_(NULL),
        __is_black_(false) {}
  ~__tree_node() {}
};

template <class _Tp, class _NodePtr, class _DiffType>
class __tree_iterator {
  typedef typename pointer_traits<_NodePtr>::element_type __node_type;
  typedef _NodePtr                                        __node_pointer;
  __node_pointer                                          __ptr_;

 public:
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef _Tp                             value_type;
  typedef _DiffType                       difference_type;
  typedef value_type&                     reference;
  typedef _Tp*                            pointer;

  __node_pointer                          base() const { return __ptr_; }

  __tree_iterator() : __ptr_(NULL) {}
  explicit __tree_iterator(__node_pointer __p) : __ptr_(__p) {}
  __tree_iterator(const __tree_iterator& __x) : __ptr_(__x.__ptr_) {}
  __tree_iterator& operator=(const __tree_iterator& __x) {
    __ptr_ = __x.__ptr_;
    return *this;
  }
  reference        operator*() const { return __ptr_->__value_; }
  pointer          operator->() const { return &(__ptr_->__value_); }
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
  __node_pointer                                          __ptr_;
  typedef __tree_iterator<_Tp, _NodePtr, _DiffType>       __non_const_iterator;

 public:
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef _Tp                             value_type;
  typedef _DiffType                       difference_type;
  typedef const value_type&               reference;
  typedef const _Tp*                      pointer;

  __node_pointer                          base() const { return __ptr_; }

  __tree_const_iterator() : __ptr_(NULL) {}
  explicit __tree_const_iterator(__node_pointer __p) : __ptr_(__p) {}
  __tree_const_iterator(__non_const_iterator __x) : __ptr_(__x.base()) {}
  __tree_const_iterator& operator=(const __tree_const_iterator& __x) {
    __ptr_ = __x.__ptr_;
    return *this;
  }
  reference              operator*() const { return __ptr_->__value_; }
  pointer                operator->() const { return &__ptr_->__value_; }
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
  typedef _Tp                                      value_type;
  typedef _Compare                                 value_compare;
  typedef _Allocator                               allocator_type;
  typedef __tree_node<value_type>                  _NodeTypes;
  typedef typename _NodeTypes::key_type            key_type;

  typedef typename _NodeTypes::__node_value_type   __node_value_type;
  typedef typename allocator_type::pointer         pointer;
  typedef typename allocator_type::const_pointer   const_pointer;
  typedef typename allocator_type::size_type       size_type;
  typedef typename allocator_type::difference_type difference_type;

 public:
  typedef _NodeTypes __node;
  typedef __node*    __node_pointer;
  typedef
      typename allocator_type::template rebind<__node>::other __node_allocator;
  typedef __tree_iterator<value_type, __node_pointer, difference_type> iterator;
  typedef __tree_const_iterator<value_type, __node_pointer, difference_type>
                                               const_iterator;
  typedef ft::reverse_iterator<iterator>       reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 public:
  __node_pointer   __begin_node_;
  __node_pointer   __end_node_;
  __node_allocator __node_alloc_;
  size_type        __size_;
  value_compare      __comp_;

 public:
  __tree() {
    __size_ = 0;
    __comp_ = value_compare();
    __node_alloc_ = __node_allocator();
    __end_node_           = __node_alloc_.allocate(1);
    __end_node_->__right_ = NULL;
    __end_node_->__left_  = NULL;
    __begin_node_         = __end_node_;
  }
  explicit __tree(const value_compare&    __comp,
                  const allocator_type& __alloc = allocator_type()) {
    __size_ = 0;
    __comp_ = __comp;
    __node_alloc_ = __alloc;
    __end_node_           = __node_alloc_.allocate(1);
    __end_node_->__right_ = NULL;
    __end_node_->__left_  = NULL;
    __begin_node_         = __end_node_;
  }
  template <class _InputIterator>
  __tree(_InputIterator __first, _InputIterator __last,
         const value_compare&    __comp  = value_compare(),
         const allocator_type& __alloc = allocator_type()) {
    __size_ = 0;
    __comp_ = __comp;
    __node_alloc_ = __alloc;
    __end_node_           = __node_alloc_.allocate(1);
    __end_node_->__right_ = NULL;
    __end_node_->__left_  = NULL;
    __begin_node_         = __end_node_;
    insert(__first, __last);
  }
  __tree(const __tree& __x) {
    __size_ = 0;
    __comp_ = __x.__comp_;
    __node_alloc_ = __x.__node_alloc_;
    __end_node_           = __node_alloc_.allocate(1);
    __end_node_->__right_ = NULL;
    __end_node_->__left_  = NULL;
    __begin_node_         = __end_node_;
    insert(__x.begin(), __x.end());
  }
  allocator_type get_allocator() const { return allocator_type(__node_alloc_); }
  ~__tree() { __destroy(__end_node_); }
  // ===========================================================================
  // access
  // ===========================================================================
  inline __node_pointer  __root() const { return __end_node_->__left_; }
  inline __node_pointer* __root_ptr() { return &(__end_node_->__left_); }
  // ===========================================================================
  // iterator
  // ===========================================================================
  iterator               begin() { return iterator(__begin_node_); }
  const_iterator         begin() const { return const_iterator(__begin_node_); }
  iterator               end() { return iterator(__end_node_); }
  const_iterator         end() const { return const_iterator(__end_node_); }
  reverse_iterator       rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator       rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }
  // ===========================================================================
  // Capacity:
  // ===========================================================================
  bool             empty() const { return __size_ == 0; }
  inline size_type size() const { return __size_; }
  inline size_type max_size() const {
    return std::min<size_type>(__node_alloc_.max_size(),
                               std::numeric_limits<difference_type>::max());
  }
  // ===========================================================================
  // Modifiers
  // ===========================================================================
  void clear() {
    __destroy(__root());
    __size_              = 0;
    __begin_node_        = __end_node_;
    __end_node_->__left_ = NULL;
  }
  pair<iterator, bool> insert(const value_type& __v) {
    __node_pointer  __parent   = NULL;
    __node_pointer& __child    = __find_equal(__parent, __v);
    bool            __inserted = false;
    if (__child == NULL) {
      __child = __create_node(__v, __parent);
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
    __node_pointer  __parent = NULL;
    __node_pointer& __child  = __find_equal(__parent, __v, __hint);
    if (__child == NULL) {
      __child = __create_node(__v, __parent);
      if (__begin_node_->__left_ != NULL) {
        __begin_node_ = __begin_node_->__left_;
      }
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
    while (__first != __last) {
      __first = erase(__first);
    }
    return __last;
  }
  size_type erase(const key_type& __key) {
    iterator __it = find(__key);
    if (__it != end()) {
      erase(__it);
      return 1;
    }
    return 0;
  }
  void swap(__tree& __other) {
    std::swap(__size_, __other.__size_);
    std::swap(__comp_, __other.__comp_);
    std::swap(__node_alloc_, __other.__node_alloc_);
    std::swap(__begin_node_, __other.__begin_node_);
    std::swap(__end_node_, __other.__end_node_);
  }
  // ===========================================================================
  // search
  // ===========================================================================
  size_type count(const key_type& __k) const {
    const_iterator __cit = find(__k);
    return __cit == end() ? 0 : 1;
  }
  iterator find(const key_type& __k) {
    iterator __it = lower_bound(__k);
    if (__it != end() && !__comp_(__k, *__it)) {
      return __it;
    }
    return end();
  }
  const_iterator find(const key_type& __k) const {
    const_iterator __it = lower_bound(__k);
    if (__it != end() && !__comp_(__k, *__it)) {
      return __it;
    }
    return end();
  }
  pair<iterator, iterator> equal_range(const key_type& __k) {
    return pair<iterator, iterator>(lower_bound(__k), upper_bound(__k));
  }
  pair<const_iterator, const_iterator> equal_range(const key_type& __k) const {
    return pair<const_iterator, const_iterator>(lower_bound(__k),
                                                upper_bound(__k));
  }
  // lower_bound(const key_type&)
  // keyより大きい、または等しい最初の要素を指すイテレータを返します。
  iterator lower_bound(const key_type& __k) {
    __node_pointer __result = NULL;
    __node_pointer __node   = __root();
    if (__node == NULL) {
      return end();
    }
    while (__node != NULL) {
      if (!__comp_(__node->__value_, __k)) {
        __result = __node;
        __node   = __node->__left_;
      } else {
        __node = __node->__right_;
      }
    }
    if (__result == NULL) {
      return end();
    }
    return iterator(__result);
  }
  const_iterator lower_bound(const key_type& __k) const {
    __node_pointer __result = NULL;
    __node_pointer __node   = __root();
    if (__node == NULL) {
      return end();
    }
    while (__node != NULL) {
      if (!__comp_(__node->__value_, __k)) {
        __result = __node;
        __node   = __node->__left_;
      } else {
        __node = __node->__right_;
      }
    }
    if (__result == NULL) {
      return end();
    }
    return const_iterator(__result);
  }
  iterator upper_bound(const key_type& __k) {
    __node_pointer __result = NULL;
    __node_pointer __node   = __root();
    if (__node == NULL) {
      return end();
    }
    while (__node != NULL) {
      if (__comp_(__k, __node->__value_)) {
        __result = __node;
        __node   = __node->__left_;
      } else {
        __node = __node->__right_;
      }
    }
    if (__result == NULL) {
      return end();
    }
    return iterator(__result);
  }
  const_iterator upper_bound(const key_type& __k) const {
    __node_pointer __result = NULL;
    __node_pointer __node   = __root();
    if (__node == NULL) {
      return end();
    }
    while (__node != NULL) {
      if (__comp_(__k, __node->__value_)) {
        __result = __node;
        __node   = __node->__left_;
      } else {
        __node = __node->__right_;
      }
    }
    if (__result == NULL) {
      return end();
    }
    return const_iterator(__result);
  }
  // ===========================================================================
  // observers
  // ===========================================================================
  value_compare            key_comp() const { return __comp_; }
  // ===========================================================================
  // private
  // ===========================================================================
  // Find place to insert if __k doesn't exist
  // Set __parent to parent of null leaf
  // Return reference to null leaf
  // If __k exists, set parent to node of __k and return reference to node of
  // __k
  inline __node_pointer& __find_equal(__node_pointer& __parent,
                                      const value_type& __v) {
    __node_pointer  __nd = __root();
    __node_pointer* __p  = __root_ptr();
    if (__nd != NULL) {
      while (true) {
        if (__comp_(__v, __nd->__value_)) {
          if (__nd->__left_ != NULL) {
            __p  = &(__nd->__left_);
            __nd = __nd->__left_;
          } else {
            __parent = __nd;
            return __parent->__left_;
          }
        } else if (__comp_(__nd->__value_, __v)) {
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
  inline __node_pointer& __find_equal(__node_pointer& __parent,
                                      const value_type& __v, iterator __hint) {
    if (__hint.base() == __end_node_ || __comp_(__v, *__hint)) {
      iterator __prior = __hint;
      if (__prior.base() == __begin_node_ || __comp_((*--__prior), __v)) {
        if (__hint.base()->__left_ == NULL) {
          __parent = __hint.base();
          return __hint.base()->__left_;
        } else {
          __parent = __prior.base();
          return __prior.base()->__right_;
        }
      }
      return __find_equal(__parent, __v);
    } else if (__comp_(*__hint, __v)) {
      iterator __next_it = __next(__hint);
      if (__next_it.base() == __end_node_ || __comp_(__v, *__next_it)) {
        if (__hint.base()->__right_ == NULL) {
          __parent = __hint.base();
          return __hint.base()->__right_;
        } else {
          __parent = __next_it.base();
          return __parent->__left_;
        }
      }
      return __find_equal(__parent, __v);
    }
    __parent = __hint.base();
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
  inline __node_pointer __create_node(const value_type&     __v,
                                      const __node_pointer& __parent) {
    __node_pointer __new_node = __node_alloc_.allocate(1);
    __node_alloc_.construct(__new_node, __v);
    __new_node->__parent_ = __parent;
    __new_node->__left_  = NULL;
    __new_node->__right_ = NULL;
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
  iterator __next(iterator it) { return ++it; }
};

// =============================================================================
// non-member functions
// =============================================================================
template <class _Tp, class _Compare, class _Allocator>
inline bool operator==(const __tree<_Tp, _Compare, _Allocator>& __x,
                       const __tree<_Tp, _Compare, _Allocator>& __y) {
  return __x.size() == __y.size() && equal(__x.begin(), __y.begin());
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
