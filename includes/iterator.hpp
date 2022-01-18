// Copyright (c) 2020 kohkubo

#ifndef INCLUDES_ITERATOR_HPP_
#define INCLUDES_ITERATOR_HPP_

#include <cstddef>
#include <iterator>

#include "type_traits.hpp"

namespace ft {
template <class Iterator>
struct iterator_traits {
  typedef typename Iterator::difference_type   difference_type;
  typedef typename Iterator::value_type        value_type;
  typedef typename Iterator::pointer           pointer;
  typedef typename Iterator::reference         reference;
  typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T *> {
  typedef ptrdiff_t                       difference_type;
  typedef T                               value_type;
  typedef T                              *pointer;
  typedef T                              &reference;
  typedef std::random_access_iterator_tag iterator_category;
};
template <class T>
struct iterator_traits<const T *> {
  typedef ptrdiff_t                       difference_type;
  typedef T                               value_type;
  typedef const T                        *pointer;
  typedef const T                        &reference;
  typedef std::random_access_iterator_tag iterator_category;
};

// has_iterator_category
template <class T>
struct has_iterator_category {
  static no_type check(...);
  template <class U>
  static yes_type check(typename U::iterator_category * = 0);
  static const bool value = sizeof(check<T>(0)) == sizeof(yes_type);
};

// has_iterator_category_is_convertible
template <class T, class U,
          bool = has_iterator_category<iterator_traits<T> >::value>
struct has_iterator_category_is_convertible
    : is_convertible<typename iterator_traits<T>::iterator_category, U> {};

template <class T, class U>
struct has_iterator_category_is_convertible<T, U, false> : false_type {};

// is_input_iterator
template <class T>
struct is_input_iterator
    : has_iterator_category_is_convertible<T, std::input_iterator_tag> {};
}  // namespace ft

#endif  // INCLUDES_ITERATOR_HPP_
