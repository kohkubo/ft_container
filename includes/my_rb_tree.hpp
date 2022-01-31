#ifndef INCLUDES_MY_RB_TREE_HPP_
#define INCLUDES_MY_RB_TREE_HPP_

#include "my_rb_tree_header.hpp"

namespace ft {

// destractor
template <class _Tp, class _Compare, class _Allocator>
__tree<_Tp, _Compare, _Allocator>::~__tree() {
  __destroy(__end_node_);
}
// =============================================================================
// Modifiers
// =============================================================================
// __insert_unique
// __emplace_unique_key_args
template <class _Tp, class _Compare, class _Allocator>
pair<typename __tree<_Tp, _Compare, _Allocator>::iterator, bool>
__tree<_Tp, _Compare, _Allocator>::__insert_unique(const value_type& __x) {
  __node_pointer  __parent;
  __node_pointer& __child    = __find_equal(__parent, __x.first);
  bool            __inserted = false;
  if (__child == NULL) {
    __node_pointer __new_node = __create_node(__x);
    __insert_node_at(__parent, __child, __new_node);
    __child->__parent_ = __parent;
    __inserted         = true;
  }
  return pair<iterator, bool>(iterator(__child), __inserted);
}
// erase(iterator)
template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::erase(iterator __p) {
  __node_pointer __np = __p.__ptr_;
  iterator       __r  = __remove_node_pointer(__np);
}

// __destroy
template <class _Tp, class _Compare, class _Allocator>
void __tree<_Tp, _Compare, _Allocator>::__destroy(__node_pointer __nd) {
  if (__nd != __end_node_) {
    __destroy(__nd->__left_);
    __destroy(__nd->__right_);
    __node_alloc_.destroy(__nd);
    __node_alloc_.deallocate(__nd, 1);
  }
}

template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::__node_pointer&
__tree<_Tp, _Compare, _Allocator>::__find_equal(__node_pointer& __parent,
                                                const key_type& __k) {
  __node_pointer  __nd = __root();
  __node_pointer* __p  = __root_ptr();
  if (__nd != NULL) {
    while (true) {
      if (__k < __nd->__value_.first) {
        if (__nd->__left_ != NULL) {
          __nd = __nd->__left_;
        } else {
          __parent = __nd;
          return __nd->__left_;
        }
      } else if (__nd->__value_.first < __k) {
        if (__nd->__right_ != NULL) {
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
void __tree<_Tp, _Compare, _Allocator>::__insert_node_at(
    __node_pointer& __parent, __node_pointer& __child,
    __node_pointer __new_node) {
  __new_node->__parent_ = __parent;
  __child               = __new_node;
  if (__begin_node_->__left_ != NULL) {
    __begin_node_ = __begin_node_->__left_;
  }
  __tree_balance_after_insert(__end_node_->__left_, __child);
  ++__size_;
}

template <class _Tp, class _Compare, class _Allocator>
void __tree<_Tp, _Compare, _Allocator>::__tree_balance_after_insert(
    __node_pointer __root, __node_pointer __x) {
  __x->__is_black_ = __x == __root;
  while (__x != __root && !__x->__parent_->__is_black_) {
    if (__tree_is_left_child(__x->__parent_)) {
      __node_pointer __y = __x->__parent_->__parent_->__right_;

      if (__y != NULL && !__y->__is_black_) {
        __x              = __x->__parent_;
        __x->__is_black_ = true;
        __x              = __x->__parent_;
        __x->__is_black_ = __x == __root;
        __y->__is_black_ = true;
      } else {
        if (!__tree_is_left_child(__x)) {
          __x = __x->__parent_;
          __tree_left_rotate(__x);
        }
        __x              = __x->__parent_;
        __x->__is_black_ = true;
        __x              = __x->__parent_;
        __x->__is_black_ = false;
        __tree_right_rotate(__x);
        break;
      }
    } else {
      __node_pointer __y = __x->__parent_->__parent_->__left_;
      if (__y != NULL && !__y->__is_black_) {
        __x              = __x->__parent_;
        __x->__is_black_ = true;
        __x              = __x->__parent_;
        __x->__is_black_ = __x == __root;
        __y->__is_black_ = true;
      } else {
        if (__tree_is_left_child(__x)) {
          __x = __x->__parent_;
          __tree_right_rotate(__x);
        }
        __x              = __x->__parent_;
        __x->__is_black_ = true;
        __x              = __x->__parent_;
        __x->__is_black_ = false;
        __tree_left_rotate(__x);
        break;
      }
    }
  }
}

// __tree_left_rotate
template <class _Tp, class _Compare, class _Allocator>
void __tree<_Tp, _Compare, _Allocator>::__tree_left_rotate(__node_pointer __x) {
  __node_pointer __y = __x->__right_;
  __x->__right_      = __y->__left_;
  if (__y->__left_ != NULL) {
    __y->__left_->__parent_ = __x;
  }
  __y->__parent_ = __x->__parent_;
  if (__tree_is_left_child(__x)) {
    __x->__parent_->__left_ = __y;
  } else {
    __x->__parent_->__right_ = __y;
  }
  __y->__left_   = __x;
  __x->__parent_ = __y;
}

// __tree_right_rotate
template <class _Tp, class _Compare, class _Allocator>
void __tree<_Tp, _Compare, _Allocator>::__tree_right_rotate(
    __node_pointer __x) {
  __node_pointer __y = __x->__left_;
  __x->__left_       = __y->__right_;
  if (__y->__right_ != NULL) {
    __y->__right_->__parent_ = __x;
  }
  __y->__parent_ = __x->__parent_;
  if (__tree_is_left_child(__x)) {
    __x->__parent_->__left_ = __y;
  } else {
    __x->__parent_->__right_ = __y;
  }
  __y->__right_  = __x;
  __x->__parent_ = __y;
}

// __create_node
template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::__node_pointer
__tree<_Tp, _Compare, _Allocator>::__create_node(const value_type& __v) {
  __node_pointer __new_node = __node_alloc_.allocate(1);
  __node_alloc_.construct(__new_node, __v);
  __new_node->__left_     = NULL;
  __new_node->__right_    = NULL;
  __new_node->__parent_   = NULL;
  __new_node->__is_black_ = true;
  return __new_node;
}

template <class _Tp, class _Compare, class _Allocator>
typename __tree<_Tp, _Compare, _Allocator>::iterator
__tree<_Tp, _Compare, _Allocator>::__remove_node_pointer(__node_pointer __ptr) {
  iterator __it(__ptr);
  ++__it;
  if (__begin_node_ == __ptr) {
    __begin_node_ = __r.__ptr_;
  }
  --__size_;
  __tree_remove(__end_node_->__left_, __ptr);
  return __r;
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
  bool __remove_black = __y->__is_black_;
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
          __w->__parent_->is_black_  = true;
          __w->__right_->__is_black_ = true;
          __tree_left_rotate(__w->__parent_);
          break;
        }
      }
      else {
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

}  // namespace ft

#endif  // INCLUDES_MY_RB_TREE_HPP_
