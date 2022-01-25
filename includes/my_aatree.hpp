#ifndef INCLUDES_MY_AATREE_HPP_
#define INCLUDES_MY_AATREE_HPP_

#include "my_aatree_header.hpp"

namespace ft {
// =============================================================================
// Canonical
// =============================================================================
template <typename Key, typename T, typename Compare, typename Alloc>
AATree<Key, T, Compare, Alloc>::AATree() : __alloc_(Alloc()) {
  __null_node_ = __create_node(value_type());
  __root_      = __null_node_;
}
template <typename Key, typename T, typename Compare, typename Alloc>
AATree<Key, T, Compare, Alloc>::AATree(const Compare& comp, const Alloc& alloc)
    : __compare_(comp), __alloc_(alloc) {
  __null_node_ = __create_node(value_type());
  __root_      = __null_node_;
}
template <typename Key, typename T, typename Compare, typename Alloc>
AATree<Key, T, Compare, Alloc>::~AATree() {
  clear();
  __alloc_.deallocate(__null_node_->data_, 1);
  __node_alloc_.deallocate(__null_node_, 1);
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
// =============================================================================
// lookup:
// =============================================================================
// find
template <typename Key, typename T, typename Compare, typename Alloc>
typename AATree<Key, T, Compare, Alloc>::iterator
AATree<Key, T, Compare, Alloc>::find(const key_type& k) {
  node_pointer current      = __root_;
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
typename AATree<Key, T, Compare, Alloc>::node_pointer
AATree<Key, T, Compare, Alloc>::__create_node(const value_type& v) {
  pointer tmp = __alloc_.allocate(1);
  __alloc_.construct(tmp, v);
  node_pointer tmp_node = __node_alloc_.allocate(1);
  __node_alloc_.construct(tmp_node, node_type(tmp));
  return tmp_node;
}
// rotateWithLeftChild
template <typename Key, typename T, typename Compare, typename Alloc>
void AATree<Key, T, Compare, Alloc>::__rotateWithLeftChild(node_pointer& k2) {
  node_pointer tmp = k2->left_;
  k2->left_        = tmp->right_;
  tmp->right_      = k2;
  k2               = tmp;
}
// rotateWithRightChild
template <typename Key, typename T, typename Compare, typename Alloc>
void AATree<Key, T, Compare, Alloc>::__rotateWithRightChild(node_pointer& k1) {
  node_pointer tmp = k1->right_;
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
typename AATree<Key, T, Compare, Alloc>::node_pointer
AATree<Key, T, Compare, Alloc>::__insert(const value_type& v,
                                         node_reference    node) {
  if (node == __null_node_) {
    node = __create_node(v);
    return node;
  } else if (__compare_(v.first, node->data_->first)) {
    __insert(v, node->left_);
  } else if (__compare_(node->data_->first, v.first)) {
    __insert(v, node->right_);
  } else {
    return NULL;
  }
  __skew(node);
  __split(node);
}
}  // namespace ft

#endif  // INCLUDES_MY_AATREE_HPP_
