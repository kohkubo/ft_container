// Copyright (c) 2022 kohkubo

#ifndef INCLUDES_BK_AATREE_HEADER_HPP_
#define INCLUDES_BK_AATREE_HEADER_HPP_

#include <algorithm>
#include <stdexcept>

namespace ft {

// template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
template <typename T>
class AATree {
 public:
  AATree();
  explicit AATree(const AATree &rhs);
  ~AATree();
  const AATree &operator=(const AATree &rhs);

  const T      &findMin() const;
  const T      &findMax() const;
  bool          contains(const T &x) const;
  bool          isEmpty() const;
  void          printTree() const;
  void          clear();
  void          insert(const T &x);
  void          remove(const T &x);
  void          size();

 private:
  struct AANode {
    T       data_;
    AANode *left_;
    AANode *right_;
    int     level_;
    AANode() : left_(NULL), right_(NULL), level_(1) {}
    AANode(const T &data, AANode *left, AANode *right, int level = 1)
        : data_(data), left_(left), right_(right), level_(level) {}
  };
  AANode *__root_;
  AANode *__nullNode_;
  void    __insert(const T &x, AANode *&t);
  void    __remove(const T &x, AANode *&t);
  void    __clear(AANode *&t);
  void    __printTree(AANode *t) const;
  void    __skew(AANode *&t);
  void    __split(AANode *&t);
  void    __rotateWithLeftChild(AANode *&k2);
  void    __rotateWithRightChild(AANode *&k1);
  AANode *__clone(AANode *t) const {
    if (t == t->left_)
      return __nullNode_;
    else
      return new AANode(t->data_, __clone(t->left_), __clone(t->right_), t->level_);
  }
};

}  // namespace ft

#endif  // INCLUDES_BK_AATREE_HEADER_HPP_
