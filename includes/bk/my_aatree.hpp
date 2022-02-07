#ifndef INCLUDES_AATREE_HPP_
#define INCLUDES_AATREE_HPP_

#include "aatree_header.hpp"

namespace ft {
// =============================================================================
// Canonical
// =============================================================================
template <typename Key, typename T, typename Compare, typename Alloc>
AATree<Key, T, Compare, Alloc>::AATree() : __alloc_(Alloc()), __size_(0) {
  __begin_node_       = __node_pointer();
  __null_node_        = __create_node(value_type());
  __null_node_->left_ = __null_node_->right_ = __null_node_;
  __null_node_->level_                       = 0;
  __root_                                    = __null_node_;
}
template <typename Key, typename T, typename Compare, typename Alloc>
AATree<Key, T, Compare, Alloc>::AATree(const Compare& comp, const Alloc& alloc)
    : __compare_(comp), __alloc_(alloc), __size_(0) {
  __begin_node_       = __node_pointer();
  __null_node_        = __create_node(value_type());
  __null_node_->left_ = __null_node_->right_ = __null_node_;
  __null_node_->level_                       = 0;
  __root_                                    = __null_node_;
}
// =
template <typename Key, typename T, typename Compare, typename Alloc>
AATree<Key, T, Compare, Alloc>& AATree<Key, T, Compare, Alloc>::operator=(
    const AATree& x) {
  if (this != &x) {
    __clear();
    __begin_node_       = __node_pointer();
    __null_node_        = __create_node(value_type());
    __null_node_->left_ = __null_node_->right_ = __null_node_;
    __null_node_->level_                       = 0;
    __root_                                    = __null_node_;
    __size_                                    = 0;
    __copy(x.__root_);
  }
  return *this;
}

template <typename Key, typename T, typename Compare, typename Alloc>
AATree<Key, T, Compare, Alloc>::~AATree() {
  clear();
  __alloc_.deallocate(__null_node_->data_, 1);
  __node_alloc_.deallocate(__null_node_, 1);
}
// =============================================================================
// element access
// =============================================================================
template <typename Key, typename T, typename Compare, typename Alloc>
typename AATree<Key, T, Compare, Alloc>::reference
AATree<Key, T, Compare, Alloc>::operator[](const Key& key) {
  __node_pointer p = __find(key);
  if (p == __null_node_) {
    __insert(value_type(key, T()));
    p = __find(key);
  }
  return p->data_.second;
}

// =============================================================================
// capacity
// =============================================================================
template <typename Key, typename T, typename Compare, typename Alloc>
bool AATree<Key, T, Compare, Alloc>::empty() const {
  return __root_ == __null_node_;
}
template <typename Key, typename T, typename Compare, typename Alloc>
typename AATree<Key, T, Compare, Alloc>::size_type
AATree<Key, T, Compare, Alloc>::size() const {
  return __size_;
}
// =============================================================================
// Iterators
// =============================================================================
template <typename Key, typename T, typename Compare, typename Alloc>
typename AATree<Key, T, Compare, Alloc>::iterator
AATree<Key, T, Compare, Alloc>::begin() {
  return iterator(__root_->left_);
}
// =============================================================================
// modifiers
// =============================================================================
template <typename Key, typename T, typename Compare, typename Alloc>
void AATree<Key, T, Compare, Alloc>::clear() {
  __clear(__root_);
  __root_ = __null_node_;
}
template <typename Key, typename T, typename Compare, typename Alloc>
void AATree<Key, T, Compare, Alloc>::insert(const value_type& v) {
  __insert(v, __root_);
}
// =============================================================================
// lookup:
// =============================================================================
// find
template <typename Key, typename T, typename Compare, typename Alloc>
typename AATree<Key, T, Compare, Alloc>::iterator
AATree<Key, T, Compare, Alloc>::find(const key_type& k) {
  __node_pointer current       = __root_;
  __null_node_->data_->first = k;
  for (;;) {
    if (__compare(k, current->data_->first)) {
      if (current->left_ == __null_node_) {
        return iterator(current);
      }
      current = current->left_;
    } else if (__compare(current->data_->first, k)) {
      if (current->right_ == __null_node_) {
        return iterator(current);
      }
      current = current->right_;
    } else {
      return iterator(current);
    }
  }
}
// =============================================================================
// Private member functions
// =============================================================================
// create_node
template <typename Key, typename T, typename Compare, typename Alloc>
typename AATree<Key, T, Compare, Alloc>::__node_pointer
AATree<Key, T, Compare, Alloc>::__create_node(const value_type& v) {
  pointer tmp = __alloc_.allocate(1);
  __alloc_.construct(tmp, v);
  __node_pointer tmp_node = __node_alloc_.allocate(1);
  __node_alloc_.construct(tmp_node, node_type(tmp));
  tmp_node->left_ = tmp_node->right_ = __null_node_;
  return tmp_node;
}
// rotateWithLeftChild
template <typename Key, typename T, typename Compare, typename Alloc>
void AATree<Key, T, Compare, Alloc>::__rotateWithLeftChild(__node_pointer& k2) {
  __node_pointer tmp = k2->left_;
  k2->left_        = tmp->right_;
  tmp->right_      = k2;
  k2               = tmp;
}
// rotateWithRightChild
template <typename Key, typename T, typename Compare, typename Alloc>
void AATree<Key, T, Compare, Alloc>::__rotateWithRightChild(__node_pointer& k1) {
  __node_pointer tmp = k1->right_;
  k1->right_       = tmp->left_;
  tmp->left_       = k1;
  k1               = tmp;
}
// skew
template <typename Key, typename T, typename Compare, typename Alloc>
void AATree<Key, T, Compare, Alloc>::__skew(node_reference x) {
  if (x->left_->level_ == x->level_) {
    __rotateWithRightChild(x);
  }
}
// split
template <typename Key, typename T, typename Compare, typename Alloc>
void AATree<Key, T, Compare, Alloc>::__split(node_reference x) {
  if (x->right_->right_->level_ == x->level_) {
    __rotateWithLeftChild(x);
    x->level_++;
  }
}
template <typename Key, typename T, typename Compare, typename Alloc>
void AATree<Key, T, Compare, Alloc>::__clear(node_reference node) {
  if (node == __null_node_)
    return;
  __clear(node->left_);
  __clear(node->right_);
  __alloc_.destroy(node->data_);
  __alloc_.deallocate(node->data_, 1);
  __node_alloc_.destroy(node);
  __node_alloc_.deallocate(node, 1);
  node = NULL;
}
template <typename Key, typename T, typename Compare, typename Alloc>
void AATree<Key, T, Compare, Alloc>::__insert(const value_type& v,
                                              node_reference    node) {
  if (node == __null_node_) {
    node = __create_node(v);
    ++__size_;
  } else if (__compare_(v.first, node->data_->first)) {
    __insert(v, node->left_);
  } else if (__compare_(node->data_->first, v.first)) {
    __insert(v, node->right_);
  } else {
    return;
  }
  __skew(node);
  __split(node);
}
// clone
template <typename Key, typename T, typename Compare, typename Alloc>
typename AATree<Key, T, Compare, Alloc>::__node_pointer
AATree<Key, T, Compare, Alloc>::__clone(__node_pointer node) const {
  if (node == node->left_) {
    return __null_node_;
  } else {
    __node_pointer tmp = __create_node(*node->data_);
    tmp->left_       = __clone(node->left_);
    tmp->right_      = __clone(node->right_);
    tmp->level_      = node->level_;
    return tmp;
  }
}
// size
template <typename Key, typename T, typename Compare, typename Alloc>
typename AATree<Key, T, Compare, Alloc>::size_type
AATree<Key, T, Compare, Alloc>::__size(__node_pointer node) const {
  if (node == __null_node_) {
    return 0;
  } else {
    return __size(node->left_) + __size(node->right_) + 1;
  }
}
// find(const key_type& k)
template <typename Key, typename T, typename Compare, typename Alloc>
typename AATree<Key, T, Compare, Alloc>::__node_pointer
AATree<Key, T, Compare, Alloc>::__find(const key_type& k,
                                       __node_pointer    node) const {
  if (node == __null_node_) {
    return __null_node_;
  } else if (__compare(k, node->data_->first)) {
    return __find(k, node->left_);
  } else if (__compare(node->data_->first, k)) {
    return __find(k, node->right_);
  } else {
    return node;
  }
}
// at
template <typename Key, typename T, typename Compare, typename Alloc>
typename AATree<Key, T, Compare, Alloc>::__node_pointer
AATree<Key, T, Compare, Alloc>::__at(size_type i, __node_pointer node) const {
  if (node == __null_node_) {
    return __null_node_;
  } else if (i < __size(node->left_)) {
    return __at(i, node->left_);
  } else if (i > __size(node->left_)) {
    return __at(i - __size(node->left_) - 1, node->right_);
  } else {
    return node;
  }
}

}  // namespace ft

#endif  // INCLUDES_AATREE_HPP_
