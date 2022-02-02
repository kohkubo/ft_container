#ifndef INCLUDES_MY_RB_TREE_HPP_
#define INCLUDES_MY_RB_TREE_HPP_

#include "my_rb_tree_header.hpp"

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
  
  __node_pointer& __child    = __find_equal(__parent, __v.first, __hint.__ptr_);
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
  __node_pointer __np = __p.__ptr_;
  iterator       __r  = __remove_node_pointer(__np);
  return __r;
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
                                                __node_pointer& __hint) {
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
    __begin_node_ = __it.__ptr_;
  }
  --__size_;
  __tree_remove(__end_node_->__left_, __ptr);
  return __it;
}
// =============================================================================
// tree_base
// =============================================================================
template <class _Tp, class _Compare, class _Allocator>
void __tree<_Tp, _Compare, _Allocator>::__tree_remove(__node_pointer __root,
                                                      __node_pointer __z) {
  __node_pointer __y =
      (__z->__left_ == NULL || __z->__right_ == NULL) ? __z : __tree_next(__z);
  __node_pointer __x = __y->__left_ != NULL ? __y->__left_ : __y->__right_;
  __node_pointer __w = NULL;
  if (__x != NULL) {
    __x->__parent_ = __y->__parent_;
  }
  if (__tree_is_left_child(__y)) {
    __y->__parent_->__left_ = __x;
    if (__y != __root) {
      __w = __y->__parent_->__right_;
    } else {
      __root = __x;
    }
  } else {
    __y->__parent_->__right_ = __x;
    __w                      = __y->__parent_->__left_;
  }
  bool __removed_black = __y->__is_black_;
  if (__y != __z) {
    __y->__parent_ = __z->__parent_;
    if (__tree_is_left_child(__z)) {
      __y->__parent_->__left_ = __y;
    } else {
      __y->__parent_->__right_ = __y;
    }
    __y->__left_            = __z->__left_;
    __y->__left_->__parent_ = __y;
    __y->__right_           = __z->__right_;
    if (__y->__right_ != NULL) {
      __y->__right_->__parent_ = __y;
    }
    __y->__is_black_ = __z->__is_black_;
    if (__root == __z) {
      __root = __y;
    }
  }
  if (__removed_black && __root != NULL) {
    if (__x != NULL) {
      __x->__is_black_ = true;
    } else {
      while (true) {
        if (!__tree_is_left_child(__w)) {
          if (!__w->__is_black_) {
            __w->__is_black_            = true;
            __w->__parent_->__is_black_ = false;
            __tree_left_rotate(__w->__parent_);
            if (__root == __w->__left_) {
              __root = __w;
            }
            __w = __w->__left_->__right_;
          }
          // __w->__is_black_ is new true, __w may have null children
          if ((__w->__left_ == NULL || __w->__left_->__is_black_) &&
              (__w->__right_ == NULL || __w->__right_->__is_black_)) {
            __w->__is_black_ = false;
            __w              = __w->__parent_;
            if (__x == __root || __x->__is_black_) {
              __x->__is_black_ = true;
              break;
            }
            __w = __tree_is_left_child(__x) ? __x->__parent_->__right_
                                            : __x->__parent_->__left_;
          } else {
            if (__w->__right_ == NULL || __w->__right_->__is_black_) {
              __w->__left_->__is_black_ = true;
              __w->__is_black_          = false;
              __tree_right_rotate(__w);
              __w = __w->__parent_;
            }
            __w->__is_black_           = __w->__parent_->__is_black_;
            __w->__parent_->__is_black_  = true;
            __w->__right_->__is_black_ = true;
            __tree_left_rotate(__w->__parent_);
            break;
          }
        } else {
          if (!__w->__is_black_) {
            __w->__is_black_            = true;
            __w->__parent_->__is_black_ = false;
            __tree_right_rotate(__w->__parent_);
            if (__root == __w->__right_) {
              __root = __w;
            }
            __w = __w->__right_->__left_;
          }
          if ((__w->__left_ == NULL || __w->__left_->__is_black_) &&
              (__w->__right_ == NULL || __w->__right_->__is_black_)) {
            __w->__is_black_ = false;
            __x              = __w->__parent_;
            if (!__x->__is_black_ || __x == __root) {
              __x->__is_black_ = true;
              break;
            }
            __w = __tree_is_left_child(__x) ? __x->__parent_->__right_
                                            : __x->__parent_->__left_;
          } else {
            if (__w->__left_ == NULL || __w->__left_->__is_black_) {
              __w->__right_->__is_black_ = true;
              __w->__is_black_           = false;
              __tree_left_rotate(__w);
              __w = __w->__parent_;
            }
            __w->__is_black_            = __w->__parent_->__is_black_;
            __w->__parent_->__is_black_ = true;
            __w->__left_->__is_black_   = true;
            __tree_right_rotate(__w->__parent_);
            break;
          }
        }
      }
    }
  }
};
}  // namespace ft

#endif  // INCLUDES_MY_RB_TREE_HPP_
