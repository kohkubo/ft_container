// Copyright (c) 2020 kohkubo

#ifndef INCLUDES_ITERATOR_HPP_
#define INCLUDES_ITERATOR_HPP_

#include <cstddef>
#include <iterator>

#include "type_traits.hpp"

namespace ft {
template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T *, class Reference = T &>
struct iterator {
  typedef T         value_type;
  typedef Distance  difference_type;
  typedef Pointer   pointer;
  typedef Reference reference;
  typedef Category  iterator_category;
};

template <class Iterator>
struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type        value_type;
  typedef typename Iterator::difference_type   difference_type;
  typedef typename Iterator::pointer           pointer;
  typedef typename Iterator::reference         reference;
};

template <class T>
struct iterator_traits<T *> {
  typedef ptrdiff_t                       difference_type;
  typedef typename remove_cv<T>::type     value_type;
  typedef value_type                     *pointer;
  typedef value_type                     &reference;
  typedef std::random_access_iterator_tag iterator_category;
};
}  // namespace ft

#endif  // INCLUDES_ITERATOR_HPP_
