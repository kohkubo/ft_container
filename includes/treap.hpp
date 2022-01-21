#ifndef TREAP_HPP
#define TREAP_HPP

#include <iostream>
#include <limits>
#include <stdexcept>

#include "treap_header.hpp"

namespace ft {

template <typename T>
Treap<T>::Treap() {
  __nullNode_        = new TreapNode();
  __nullNode_->left_ = __nullNode_->right_ = __nullNode_;
  __nullNode_->priority_                   = INT_MAX;
  __root_                                  = __nullNode_;
}

template <typename T>
Treap<T>::Treap(const Treap &rhs) {
  __nullNode_        = new TreapNode();
  __nullNode_->left_ = __nullNode_->right_ = __nullNode_;
  __nullNode_->priority_                   = INT_MAX;
  __root_                                  = __nullNode_;
  *this                                    = rhs;
}

template <typename T>
Treap<T>::~Treap() {
  makeEmpty();
  delete __nullNode_;
}

template <typename T>
const Treap<T> &Treap<T>::operator=(const Treap &rhs) {
  if (this != &rhs) {
    makeEmpty();
    __root_ = __clone(rhs.__root_);
  }
  return *this;
}

template <typename T>
const T &Treap<T>::findMin() const {
  if (isEmpty())
    throw std::underflow_error("Treap is empty");

  TreapNode *ptr = __root_;
  while (ptr->left_ != __nullNode_) ptr = ptr->left_;

  return ptr->data_;
}

template <typename T>
const T &Treap<T>::findMax() const {
  if (isEmpty())
    throw std::underflow_error("Treap is empty");

  TreapNode *ptr = __root_;
  while (ptr->right_ != __nullNode_) ptr = ptr->right_;

  return ptr->data_;
}

template <typename T>
bool Treap<T>::contains(const T &x) const {
  TreapNode *current = __root_;
  __nullNode_->data_ = x;

  for (;;) {
    if (x < current->data_)
      current = current->left_;
    else if (current->data_ < x)
      current = current->right_;
    else
      return true;
  }
}

template <typename T>
bool Treap<T>::isEmpty() const {
  return __root_ == __nullNode_;
}

template <typename T>
void Treap<T>::printTree() const {
  if (isEmpty()) {
    std::cout << "Empty tree" << std::endl;
  } else {
    __printTree(__root_);
  }
}

template <typename T>
void Treap<T>::makeEmpty() {
  __makeEmpty(__root_);
}

template <typename T>
void Treap<T>::insert(const T &x) {
  __insert(x, __root_);
}

template <typename T>
void Treap<T>::remove(const T &x) {
  __remove(x, __root_);
}

template <typename T>
void Treap<T>::__insert(const T &x, TreapNode *&t) {
  if (t == __nullNode_) {
    t = new TreapNode(x, __nullNode_, __nullNode_, __randomNums_.randomInt());
  } else if (x < t->data_) {
    __insert(x, t->left_);
    if (t->left_->priority_ > t->priority_)
      __rotateWithLeftChild(t);
  } else if (t->data_ < x) {
    __insert(x, t->right_);
    if (t->right_->priority_ > t->priority_)
      __rotateWithRightChild(t);
  }
}

template <typename T>
void Treap<T>::__remove(const T &x, TreapNode *&t) {
  if (t == __nullNode_)
    return;
  else if (x < t->data_)
    __remove(x, t->left_);
  else if (t->data_ < x)
    __remove(x, t->right_);
  else {
    if (t->left_->priority_ < t->right_->priority_)
      __rotateWithLeftChild(t);
    else
      __rotateWithRightChild(t);
    if (t != __nullNode_) {
      __remove(x, t);
    } else {
      delete t->left_;
      t->left_ = __nullNode_;  // At a leaf
    }
  }
}

template <typename T>
void Treap<T>::__makeEmpty(TreapNode *&t) {
  if (t != __nullNode_) {
    __makeEmpty(t->left_);
    __makeEmpty(t->right_);
    delete t;
  }
  t = __nullNode_;
}

template <typename T>
void Treap<T>::__printTree(TreapNode *t) const {
  if (t != __nullNode_) {
    __printTree(t->left_);
    std::cout << t->data_ << std::endl;
    __printTree(t->right_);
  }
}

template <typename T>
void Treap<T>::__rotateWithLeftChild(TreapNode *&k2) {
  TreapNode *k1 = k2->left_;
  k2->left_     = k1->right_;
  k1->right_    = k2;
  k2            = k1;
}

template <typename T>
void Treap<T>::__rotateWithRightChild(TreapNode *&k1) {
  TreapNode *k2 = k1->right_;
  k1->right_    = k2->left_;
  k2->left_     = k1;
  k1            = k2;
}

}  // namespace ft

#endif
