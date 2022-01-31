#ifndef INCLUDES_AATREE_HPP_
#define INCLUDES_AATREE_HPP_

#include <iostream>

#include "aatree_header.hpp"

namespace ft {

template <typename T>
AATree<T>::AATree() {
  __nullNode_        = new AANode;
  __nullNode_->left_ = __nullNode_->right_ = __nullNode_;
  __nullNode_->level_                      = 0;
  __root_                                  = __nullNode_;
}

template <typename T>
AATree<T>::AATree(const AATree &rhs) {
  __nullNode_        = new AANode;
  __nullNode_->left_ = __nullNode_->right_ = __nullNode_;
  __nullNode_->level_                      = 0;
  __root_                                  = __clone(rhs.__root_);
}

template <typename T>
AATree<T>::~AATree() {
  clear();
  delete __nullNode_;
}

template <typename T>
const AATree<T> &AATree<T>::operator=(const AATree &rhs) {
  if (this != &rhs) {
    clear();
    __root_ = __clone(rhs.__root_);
  }
  return *this;
}

template <typename T>
const T &AATree<T>::findMin() const {
  if (isEmpty())
    throw std::underflow_error("AATree::findMin()");
  AANode *ptr = __root_;
  while (ptr->left_ != __nullNode_)
    ptr = ptr->left_;
  return ptr->data_;
}

template <typename T>
const T &AATree<T>::findMax() const {
  if (isEmpty())
    throw std::underflow_error("AATree::findMax()");
  AANode *ptr = __root_;
  while (ptr->right_ != __nullNode_)
    ptr = ptr->right_;
  return ptr->data_;
}

template <typename T>
bool AATree<T>::contains(const T &x) const {
  AANode *current    = __root_;
  __nullNode_->data_ = x;

  for (;;) {
    if (x < current->data_)
      current = current->left_;
    else if (current->data_ < x)
      current = current->right_;
    else
      return current != __nullNode_;
  }
}

template <typename T>
bool AATree<T>::isEmpty() const {
  return __root_ == __nullNode_;
}

template <typename T>
void AATree<T>::printTree() const {
  if (__root_ == __nullNode_)
    return;
  __printTree(__root_);
  std::cout << std::endl;
}

template <typename T>
void AATree<T>::clear() {
  __clear(__root_);
}

template <typename T>
void AATree<T>::insert(const T &x) {
  __insert(x, __root_);
}

template <typename T>
void AATree<T>::remove(const T &x) {
  __remove(x, __root_);
}

template <typename T>
void AATree<T>::__insert(const T &x, AANode *&t) {
  if (t == __nullNode_) {
    t = new AANode(x, __nullNode_, __nullNode_);
  } else if (x < t->data_) {
    __insert(x, t->left_);
  } else if (t->data_ < x) {
    __insert(x, t->right_);
  } else {
    return;
  }
  __skew(t);
  __split(t);
}

template <typename T>
void AATree<T>::__remove(const T &x, AANode *&t) {
  static AANode *lastNode, *deleteNode = __nullNode_;
  if (t == __nullNode_)
    return;

  lastNode = t;
  if (x < t->data_)
    __remove(x, t->left_);
  else {
    deleteNode = t;
    __remove(x, t->right_);
  }

  if (t == lastNode) {
    if (deleteNode == __nullNode_ || x != deleteNode->data_)
      return;
    deleteNode->data_ = t->data_;
    deleteNode        = __nullNode_;
    t                 = t->right_;
    delete lastNode;
  } else if (t->left_->level_ < t->level_ - 1 || t->right_->level_ < t->level_ - 1) {
    if (t->right_->level_ > --t->level_)
      t->right_->level_ = t->level_;
    __skew(t);
    __skew(t->right_);
    __skew(t->right_->right_);
    __split(t);
    __split(t->right_);
  }
}

template <typename T>
void AATree<T>::__clear(AANode *&t) {
  if (t != __nullNode_) {
    __clear(t->left_);
    __clear(t->right_);
    delete t;
    t = __nullNode_;
  }
}

template <typename T>
void AATree<T>::__printTree(AANode *t) const {
  if (t != __nullNode_) {
    __printTree(t->left_);
    std::cout << t->data_ << " ";
    __printTree(t->right_);
  }
}

template <typename T>
void AATree<T>::__skew(AANode *&t) {
  if (t->left_->level_ == t->level_)
    __rotateWithLeftChild(t);
}

template <typename T>
void AATree<T>::__split(AANode *&t) {
  if (t->right_->right_->level_ == t->level_) {
    __rotateWithRightChild(t);
    t->level_++;
  }
}

template <typename T>
void AATree<T>::__rotateWithLeftChild(AANode *&t) {
  AANode *tmp = t->left_;
  t->left_    = tmp->right_;
  tmp->right_ = t;
  t           = tmp;
}

template <typename T>
void AATree<T>::__rotateWithRightChild(AANode *&t) {
  AANode *tmp = t->right_;
  t->right_   = tmp->left_;
  tmp->left_  = t;
  t           = tmp;
}

}  // namespace ft

#endif  // INCLUDES_AATREE_HPP_
