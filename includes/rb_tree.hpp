#ifndef INCLUDES_RB_TREE_HPP_
#define INCLUDES_RB_TREE_HPP_

#include "rb_tree_header.hpp"

namespace ft {

// destractor
template <class _Tp, class _Compare, class _Allocator>
__tree<_Tp, _Compare, _Allocator>::~__tree() {
  // std::cout << "~__tree() ===========" << std::endl;
  // print_tree(__root(), 0);
  // std::cout << "===========" << std::endl;
  __destroy(__end_node_);
}
// =============================================================================
// Modifiers
// =============================================================================
// clear
template <class _Tp, class _Compare, class _Allocator>
void __tree<_Tp, _Compare, _Allocator>::clear() {
  __destroy(__root());
  __size_              = 0;
  __begin_node_        = __end_node_;
  __end_node_->__left_ = NULL;
}

template <class _Tp, class _Compare, class _Allocator>
pair<typename __tree<_Tp, _Compare, _Allocator>::iterator, bool>
__tree<_Tp, _Compare, _Allocator>::insert(const value_type& __v) {
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

template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::insert(iterator          __hint,
                                          const value_type& __v) {
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

// insert(first, last)
template <class _Tp, class _Compare, class _Allocator>
template <class _InputIterator>
void __tree<_Tp, _Compare, _Allocator>::insert(_InputIterator __first,
                                               _InputIterator __last) {
  for (; __first != __last; ++__first) {
    insert(*__first);
  }
}

// erase(iterator)
template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::erase(iterator __p) {
  __node_pointer __np = __p.base();
  iterator       __r  = __remove_node_pointer(__np);
  __node_alloc_.destroy(__np);
  __node_alloc_.deallocate(__np, 1);
  return __r;
}

// erase(first, last)
template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::erase(iterator __first, iterator __last) {
  for (; __first != __last; ++__first) {
    erase(__first);
  }
  return __last;
}

// erase(const key_type&)
template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::size_type
__tree<_Tp, _Compare, _Allocator>::erase(const key_type& __k) {
  iterator __it = find(__k);
  if (__it != __end_node_) {
    erase(__it);
    return 1;
  }
  return 0;
}
// =============================================================================
// Search
// =============================================================================
// find(const key_type&)
// キー key と同等なキーを持つ要素を探します。
template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::find(const key_type& __k) {
  iterator __p = __lower_bound(__k, __root());
  if (__p != end() && !__comp_(__k, __p->first)) {
    return __p;
  }
  return end();
}
// lower_bound(const key_type&)
// key より小さくない (すなわち大きいまたは等しい)
// 最初の要素を指すイテレータを返します。
template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::lower_bound(const key_type& __k) {
  return __lower_bound(__k, __root());
}
// =============================================================================
// Private
// =============================================================================
// __lower_bound(const key_type&, __node_pointer&, __node_pointer&)
// keyより大きい、または等しい最初の要素を指すイテレータを返します。
template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::__lower_bound(const key_type& __k,
                                                 __node_pointer  __root) {
  __node_pointer __result;
  // 根にたどり着くまで回る
  while (__root != NULL) {
    // __rootのキーが__vより大きい場合
    if (!__comp_(__root->__value_.first, __k)) {
      __result = __root;
      // 小さい方に移動
      __root   = __root->__left_;
    } else {
      // 大きい方に移動
      __root = __root->__right_;
    }
  }
  return iterator(__result);
}
// __destroy
template <class _Tp, class _Compare, class _Allocator>
void __tree<_Tp, _Compare, _Allocator>::__destroy(__node_pointer __nd) {
  if (__nd != NULL) {
    __destroy(__nd->__left_);
    __destroy(__nd->__right_);
    __node_alloc_.destroy(__nd);
    __node_alloc_.deallocate(__nd, 1);
  }
}

// Find place to insert if __k doesn't exist
// Set __parent to parent of null leaf
// Return reference to null leaf
// If __k exists, set parent to node of __k and return reference to node of __k
template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::__node_pointer&
__tree<_Tp, _Compare, _Allocator>::__find_equal(__node_pointer& __parent,
                                                const key_type& __k) {
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

template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::__node_pointer&
__tree<_Tp, _Compare, _Allocator>::__find_equal(__node_pointer& __parent,
                                                const key_type& __k,
                                                __node_pointer  __hint) {
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

// __create_node
template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::__node_pointer
__tree<_Tp, _Compare, _Allocator>::__create_node(const value_type& __v) {
  __node_pointer __new_node = __node_alloc_.allocate(1);
  __node_alloc_.construct(__new_node, __v);
  return __new_node;
}

template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::__remove_node_pointer(__node_pointer __ptr) {
  iterator __it(__ptr);
  ++__it;
  if (__begin_node_ == __ptr) {
    __begin_node_ = __it.base();
  }
  --__size_;
  __tree_remove(__root(), __ptr);
  return __it;
}
// =============================================================================
// tree_base
// =============================================================================

}  // namespace ft

#endif  // INCLUDES_RB_TREE_HPP_
