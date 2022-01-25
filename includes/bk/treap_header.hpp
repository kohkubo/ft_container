#ifndef INCLUDES_TREAP_HEADER_HPP_
#define INCLUDES_TREAP_HEADER_HPP_

#include <iostream>
#include <limits>

#include "random.hpp"

namespace ft {

template <typename T>
class Treap {
 public:
  Treap();
  explicit Treap(const Treap &rhs);
  ~Treap();
  const Treap &operator=(const Treap &rhs);

  const T     &findMin() const;
  const T     &findMax() const;
  bool         contains(const T &x) const;
  bool         isEmpty() const;
  void         printTree() const;
  void         makeEmpty();
  void         insert(const T &x);
  void         remove(const T &x);

 private:
  struct TreapNode {
    T          data_;
    TreapNode *left_;
    TreapNode *right_;
    int        priority_;

    TreapNode() : left_(NULL), right_(NULL), priority_(INT_MAX) {}
    TreapNode(const T &data, TreapNode *left, TreapNode *right, int priority)
        : data_(data), left_(left), right_(right), priority_(priority) {}
  };
  TreapNode *__root_;
  TreapNode *__nullNode_;
  Random     __randomNums_;

  void       __insert(const T &x, TreapNode *&t);
  void       __remove(const T &x, TreapNode *&t);
  void       __makeEmpty(TreapNode *&t);
  void       __printTree(TreapNode *t) const;
  void       __rotateWithLeftChild(TreapNode *&k2);
  void       __rotateWithRightChild(TreapNode *&k1);
  TreapNode *__clone(TreapNode *t) const {
    if (t == t->left_)
      return __nullNode_;
    else
      return new TreapNode(t->data_, __clone(t->left_), __clone(t->right_),
                           t->priority_);
  }
};

}  // namespace ft

#endif  // INCLUDES_TREAP_HEADER_HPP_
