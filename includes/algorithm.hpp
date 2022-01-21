#ifndef INCLUDES_ALGORITHM_HPP_
#define INCLUDES_ALGORITHM_HPP_

#include "iterator.hpp"

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
inline bool equal(InputIterator1 first1, InputIterator1 last1,
                  InputIterator2 first2, BinaryPredicate pred) {
  for (; first1 != last1; ++first1, ++first2)
    if (!pred(*first1, *first2)) return false;
  return true;
}

template <class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1, InputIterator1 last1,
                  InputIterator2 first2) {
    typedef typename ft::iterator_traits<InputIterator1>::value_type v1;
    typedef typename ft::iterator_traits<InputIterator2>::value_type v2;
    return equal(first1, last1, first2, equal_to<v1, v2>());
}

#endif  // INCLUDES_ALGORITHM_HPP_
