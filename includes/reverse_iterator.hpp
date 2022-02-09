// Copyright (c) 2022 kohkubo

#ifndef INCLUDES_REVERSE_ITERATOR_HPP_
#define INCLUDES_REVERSE_ITERATOR_HPP_

#include "iterator.hpp"
#include "random_access_iterator.hpp"

namespace ft {
template <class Iterator>
class reverse_iterator
    : public iterator<typename iterator_traits<Iterator>::iterator_category,
                      typename iterator_traits<Iterator>::difference_type,
                      typename iterator_traits<Iterator>::value_type,
                      typename iterator_traits<Iterator>::pointer,
                      typename iterator_traits<Iterator>::reference> {
 protected:
  Iterator _current;

 public:
  typedef Iterator                                            iterator_type;
  typedef typename iterator_traits<Iterator>::difference_type difference_type;
  typedef typename iterator_traits<Iterator>::value_type      value_type;
  typedef typename iterator_traits<Iterator>::pointer         pointer;
  typedef typename iterator_traits<Iterator>::reference       reference;
  typedef
      typename iterator_traits<Iterator>::iterator_category iterator_category;
  // ===========================================================================
  // Canonical
  // ===========================================================================
  reverse_iterator() : _current() {}
  explicit reverse_iterator(Iterator current) : _current(current) {}
  explicit reverse_iterator(pointer p) : _current(p) {}
  reverse_iterator(const reverse_iterator &rhs) : _current(rhs._current) {}
  template <class Iterator2>
  reverse_iterator(const reverse_iterator<Iterator2> &rhs)
      : _current(rhs.base()) {}
  reverse_iterator &operator=(const reverse_iterator &rhs) {
    _current = rhs.base();
    return *this;
  }
  ~reverse_iterator() {}
  // ===========================================================================
  // base
  // ===========================================================================
  Iterator  base() const { return _current; }
  // ===========================================================================
  // Operator
  // ===========================================================================
  reference operator*() const {
    Iterator tmp = _current;
    return *--tmp;
  }
  pointer           operator->() const { return &(operator*()); }
  reverse_iterator &operator++() {
    --_current;
    return *this;
  }
  reverse_iterator operator++(int) {
    reverse_iterator __tmp(*this);
    --_current;
    return __tmp;
  }
  reverse_iterator &operator--() {
    ++_current;
    return *this;
  }
  reverse_iterator operator--(int) {
    reverse_iterator __tmp(*this);
    ++_current;
    return __tmp;
  }
  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(_current - n);
  }
  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(_current + n);
  }
  reverse_iterator &operator+=(difference_type n) {
    _current -= n;
    return *this;
  }
  reverse_iterator &operator-=(difference_type n) {
    _current += n;
    return *this;
  }
  reference operator[](difference_type n) const { return *(*this + n); }
};
// =============================================================================
// Operator
// =============================================================================

template <class Iter1, class Iter2>
bool operator==(const reverse_iterator<Iter1> &lhs,
                const reverse_iterator<Iter2> &rhs) {
  return lhs.base() == rhs.base();
}
template <class Iter1, class Iter2>
bool operator!=(const reverse_iterator<Iter1> &lhs,
                const reverse_iterator<Iter2> &rhs) {
  return !(lhs == rhs);
}
template <class Iter1, class Iter2>
bool operator<(const reverse_iterator<Iter1> &lhs,
               const reverse_iterator<Iter2> &rhs) {
  return lhs.base() < rhs.base();
}
template <class Iter1, class Iter2>
bool operator>(const reverse_iterator<Iter1> &lhs,
               const reverse_iterator<Iter2> &rhs) {
  return lhs.base() > rhs.base();
}
template <class Iter1, class Iter2>
bool operator<=(const reverse_iterator<Iter1> &lhs,
                const reverse_iterator<Iter2> &rhs) {
  return lhs.base() <= rhs.base();
}
template <class Iter1, class Iter2>
bool operator>=(const reverse_iterator<Iter1> &lhs,
                const reverse_iterator<Iter2> &rhs) {
  return lhs.base() >= rhs.base();
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
    const reverse_iterator<Iterator> &lhs,
    const reverse_iterator<Iterator> &rhs) {
  return lhs.base() - rhs.base();
}
}  // namespace ft

#endif  // INCLUDES_REVERSE_ITERATOR_HPP_
