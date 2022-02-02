#ifndef INCLUDES_TREE_UTIL_HPP_
#define INCLUDES_TREE_UTIL_HPP_

#include <iostream>
#define END            "\033[0m"
#define BOLD           "\033[1m"
#define BLACK          "\033[30m"
#define RED            "\033[31m"
#define GREEN          "\033[32m"
#define YELLOW         "\033[33m"
#define BLUE           "\033[34m"
#define MAGENTA        "\033[35m"
#define CYAN           "\033[36m"
#define WHITE          "\033[37m"
#define UNDERLINE      "\033[4m"
#define BOLD_UNDERLINE "\033[1;4m"

namespace ft {

template <class __node_pointer>
inline bool __tree_is_left_child(__node_pointer __x) {
  return __x->__parent_->__left_ == __x;
}

template <class __node_pointer>
inline __node_pointer __tree_min(__node_pointer __x) {
  while (__x->__left_ != NULL)
    __x = __x->__left_;
  return __x;
}
template <class __node_pointer>
inline __node_pointer __tree_max(__node_pointer __x) {
  while (__x->__right_ != NULL)
    __x = __x->__right_;
  return __x;
}
template <class __node_pointer>
inline __node_pointer __tree_next(__node_pointer __x) {
  if (__x->__right_ != NULL) {
    return __tree_min(__x->__right_);
  }
  while (!__tree_is_left_child(__x)) {
    __x = __x->__parent_;
  }
  return __x->__parent_;
}
template <class __node_pointer>
inline __node_pointer __tree_prev(__node_pointer __x) {
  if (__x->__left_ != NULL) {
    return __tree_max(__x->__left_);
  }
  while (__tree_is_left_child(__x)) {
    __x = __x->__parent_;
  }
  return __x->__parent_;
}
// __tree_left_rotate
template <class __node_pointer>
void __tree_left_rotate(__node_pointer __x) {
  __node_pointer __y = __x->__right_;
  __x->__right_      = __y->__left_;
  if (__x->__right_ != NULL) {
    __x->__right_->__parent_ = __x;
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
template <class __node_pointer>
void __tree_right_rotate(__node_pointer __x) {
  __node_pointer __y = __x->__left_;
  __x->__left_       = __y->__right_;
  if (__x->__left_ != NULL) {
    __x->__left_->__parent_ = __x;
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

template <class __node_pointer>
void print_node(__node_pointer __nd) {
  if (__nd == NULL) {
    std::cout << "NULL" << std::endl;
    return;
  }
  std::cout << "node: " << __nd << std::endl;
  std::cout << __nd->__value_.first << " " << __nd->__value_.second
            << std::endl;
  std::cout << " parent: " << __nd->__parent_;
  std::cout << " left: " << __nd->__left_;
  std::cout << " right: " << __nd->__right_;
  std::cout << std::endl;
  std::cout << "==============" << std::endl;
}

// print_tree
template <class __node_pointer>
void print_tree(__node_pointer __nd, size_t __level) {
  if (__nd == NULL) {
    return;
  }
  print_tree(__nd->__right_, __level + 1);
  for (size_t i = 0; i < __level; i++) {
    std::cout << "  ";
  }
  if (!__nd->__is_black_) {
    std::cout << RED;
  }
  std::cout << __nd->__value_.first << " " << END << std::endl;
  print_tree(__nd->__left_, __level + 1);
}

template <class __node_pointer>
void __tree_balance_after_insert(__node_pointer __root, __node_pointer __x) {
  __x->__is_black_ = __x == __root;
  // 追加したノードの親は、黒である
  // rootは、黒である
  // この2つを満たすまで、ループする
  while (__x != __root && !__x->__parent_->__is_black_) {
    // std::cout << "===balance=====" << std::endl;
    // print_tree(__root, 0);
    // std::cout << "===============" << std::endl;
    // 追加したノードの親が、追加したノードの左の子である場合
    if (__tree_is_left_child(__x->__parent_)) {
      __node_pointer __y = __x->__parent_->__parent_->__right_;
      // 追加したノードの親の親が、赤である場合
      if (__y != NULL && !__y->__is_black_) {
        __x              = __x->__parent_;
        __x->__is_black_ = true;
        __x              = __x->__parent_;
        __x->__is_black_ = __x == __root;
        __y->__is_black_ = true;
      } else {
        // 追加したノードの親の親が、黒である場合
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
      // 追加したノードの親が、追加したノードの右の子である場合
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

}  // namespace ft

#endif  // INCLUDES_TREE_UTIL_HPP_
