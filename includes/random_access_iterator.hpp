// Copyright (c) 2020 kohkubo

#ifndef INCLUDES_RANDOM_ACCESS_ITERATOR_HPP_
#define INCLUDES_RANDOM_ACCESS_ITERATOR_HPP_

#include <exception>

#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {
template <class Iterator>
class random_access_iterator {
 public:
  typedef Iterator                                            iterator_type;
  typedef typename iterator_traits<Iterator>::difference_type difference_type;
  typedef typename iterator_traits<Iterator>::value_type      value_type;
  typedef typename iterator_traits<Iterator>::pointer         pointer;
  typedef typename iterator_traits<Iterator>::reference       reference;
  typedef
      typename iterator_traits<Iterator>::iterator_category iterator_category;

 private:
  iterator_type __iter_;

 public:
  // ===========================================================================
  // Canonical
  // ===========================================================================
  random_access_iterator() : __iter_(0) {}
  explicit random_access_iterator(pointer p) : __iter_(p) {}
  random_access_iterator &operator=(const iterator_type &rhs) {
    __iter_ = rhs.base();
    return *this;
  }
  ~random_access_iterator() {}
  // ===========================================================================
  // base
  // ===========================================================================
  iterator_type base() const { return __iter_; }
  // ===========================================================================
  // Operator
  // ===========================================================================
  reference     operator*() const { return *__iter_; }
  pointer operator->() const { return reinterpret_cast<pointer>(*__iter_); }
  random_access_iterator &operator++() {
    ++__iter_;
    return *this;
  }
  random_access_iterator operator++(int) {
    random_access_iterator __tmp(*this);
    ++__iter_;
    return __tmp;
  }
  random_access_iterator &operator--() {
    --__iter_;
    return *this;
  }
  random_access_iterator operator--(int) {
    random_access_iterator __tmp(*this);
    --__iter_;
    return __tmp;
  }
  random_access_iterator &operator+=(difference_type n) {
    __iter_ += n;
    return *this;
  }
  random_access_iterator &operator-=(difference_type n) {
    __iter_ -= n;
    return *this;
  }
  random_access_iterator operator+(difference_type n) const {
    random_access_iterator __tmp(*this);
    __tmp += n;
    return __tmp;
  }
  random_access_iterator operator-(difference_type n) const {
    random_access_iterator __tmp(*this);
    __tmp -= n;
    return __tmp;
  }
  reference operator[](difference_type n) const { return *(__iter_ + n); }
};
// =============================================================================
// Operator
// =============================================================================
template <class Iterator>
bool operator==(const random_access_iterator<Iterator> &lhs,
                const random_access_iterator<Iterator> &rhs) {
  return lhs.base() == rhs.base();
}
template <class Iter1, class Iter2>
bool operator==(const random_access_iterator<Iter1> &lhs,
                const random_access_iterator<Iter2> &rhs) {
  return lhs.base() == rhs.base();
}
template <class Iterator>
bool operator!=(const random_access_iterator<Iterator> &lhs,
                const random_access_iterator<Iterator> &rhs) {
  return !(lhs == rhs);
}
template <class Iter1, class Iter2>
bool operator!=(const random_access_iterator<Iter1> &lhs,
                const random_access_iterator<Iter2> &rhs) {
  return !(lhs == rhs);
}
template <class Iterator>
bool operator<(const random_access_iterator<Iterator> &lhs,
               const random_access_iterator<Iterator> &rhs) {
  return lhs.base() < rhs.base();
}
template <class Iter1, class Iter2>
bool operator<(const random_access_iterator<Iter1> &lhs,
               const random_access_iterator<Iter2> &rhs) {
  return lhs.base() < rhs.base();
}
template <class Iterator>
bool operator>(const random_access_iterator<Iterator> &lhs,
               const random_access_iterator<Iterator> &rhs) {
  return lhs.base() > rhs.base();
}
template <class Iter1, class Iter2>
bool operator>(const random_access_iterator<Iter1> &lhs,
               const random_access_iterator<Iter2> &rhs) {
  return lhs.base() > rhs.base();
}
template <class Iterator>
bool operator<=(const random_access_iterator<Iterator> &lhs,
                const random_access_iterator<Iterator> &rhs) {
  return lhs.base() <= rhs.base();
}
template <class Iter1, class Iter2>
bool operator<=(const random_access_iterator<Iter1> &lhs,
                const random_access_iterator<Iter2> &rhs) {
  return lhs.base() <= rhs.base();
}
template <class Iterator>
bool operator>=(const random_access_iterator<Iterator> &lhs,
                const random_access_iterator<Iterator> &rhs) {
  return lhs.base() >= rhs.base();
}
template <class Iter1, class Iter2>
bool operator>=(const random_access_iterator<Iter1> &lhs,
                const random_access_iterator<Iter2> &rhs) {
  return lhs.base() >= rhs.base();
}
template <class Iterator>
typename random_access_iterator<Iterator>::difference_type operator-(
    const random_access_iterator<Iterator> &lhs,
    const random_access_iterator<Iterator> &rhs) {
  return lhs.base() - rhs.base();
}
}  // namespace ft
#endif  // INCLUDES_RANDOM_ACCESS_ITERATOR_HPP_
