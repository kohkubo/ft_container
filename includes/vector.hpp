// Copyright (c) 2022 kohkubo

#ifndef INCLUDES_VECTOR_HPP_
#define INCLUDES_VECTOR_HPP_

#include <algorithm>
#include <limits>
#include <iterator>

#include "vector_header.hpp"

namespace ft {


// =============================================================================
// Modifiers
// =============================================================================
template <class T, class Alloc>
void vector<T, Alloc>::clear() {
  __destroy_range(__begin_, __end_);
  __end_ = __begin_;
}
template <class T, class Alloc>
template <class InputIterator>
void vector<T, Alloc>::insert(InputIterator pos, InputIterator first,
                              InputIterator last) {
  if (pos == end()) {
    while (first != last) {
      push_back(*first);
      ++first;
      return;
    }
  }
  size_t pos_index = pos - begin();
  size_t n         = last - first;
  if (size() + n > capacity()) {
    reserve(2 * (size() + n));
    pos = begin() + pos_index;
  }
  pointer pos_ptr = __iterator_to_pointer(pos);
  std::uninitialized_copy(pos_ptr, __end_, pos_ptr + n);
  std::uninitialized_copy(first, last, __begin_);
  __end_ += n;
}
template <class T, class Alloc>
void vector<T, Alloc>::insert(iterator pos, size_type n, const_reference x) {
  if (pos == end()) {
    push_back(x);
    return;
  }
  size_t pos_index = pos - begin();
  if (size() + n > capacity()) {
    reserve(2 * (size() + n));
    pos = begin() + pos_index;
  }
  pointer pos_ptr = __iterator_to_pointer(pos);
  std::uninitialized_copy(pos_ptr, __end_, pos_ptr + n);
  std::uninitialized_fill(pos_ptr, __end_, x);
  __end_ += n;
}
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
    iterator pos, const_reference x) {
  size_t pos_index = pos - begin();
  insert(pos, 1, x);
  return begin() + pos_index;
}
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first,
                                                            iterator last) {
  __destroy_range(__iterator_to_pointer(first), __iterator_to_pointer(last));
  std::copy(__iterator_to_pointer(last), __end_, __iterator_to_pointer(first));
  __end_ -= last - first;
  return first;
}
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator pos) {
  return erase(pos, pos + 1);
}
template <class T, class Alloc>
void vector<T, Alloc>::push_back(const_reference x) {
  if (__end_ == __end_cap_) {
    reserve(capacity() + 1);
  }
  __alloc_.construct(__end_, x);
  ++__end_;
}
template <class T, class Alloc>
void vector<T, Alloc>::pop_back() {
  if (__end_ != __begin_) {
    --__end_;
    __alloc_.destroy(__end_);
  }
}
template <class T, class Alloc>
void vector<T, Alloc>::resize(size_type n, const_reference x) {
  if (n > size()) {
    if (n > max_size()) {
      __throw_length_error();
    }
    __end_ = __begin_ + n;
    std::uninitialized_fill(__begin_, __end_, x);
  } else if (n < size()) {
    __destroy_range(__begin_ + n, __end_);
    __end_ = __begin_ + n;
  }
}
// =============================================================================
// private menber function
// =============================================================================
template <class T, class Alloc>
inline void vector<T, Alloc>::__destroy_range(pointer first, pointer last) {
  for (; first != last; ++first) {
    __alloc_.destroy(first);
  }
}
template <class T, class Alloc>
void vector<T, Alloc>::__vallocate(size_type n) {
  if (n > max_size()) {
    __throw_length_error();
  }
  __begin_   = __alloc_.allocate(n);
  __end_     = __begin_;
  __end_cap_ = __begin_ + n;
}
template <class T, class Alloc>
void vector<T, Alloc>::__vdeallocate() {
  if (__begin_) {
    __alloc_.deallocate(__begin_, __end_cap_ - __begin_);
    __begin_   = 0;
    __end_     = 0;
    __end_cap_ = 0;
  }
}
template <class T, class Alloc>
inline typename vector<T, Alloc>::pointer
vector<T, Alloc>::__iterator_to_pointer(iterator it) {
  return &(*it);
}

}  // namespace ft
#endif  // INCLUDES_VECTOR_HPP_
