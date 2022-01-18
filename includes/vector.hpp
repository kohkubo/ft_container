// Copyright (c) 2022 kohkubo

#ifndef INCLUDES_VECTOR_HPP_
#define INCLUDES_VECTOR_HPP_

#include <algorithm>
#include <limits>

#include "vector_header.hpp"

namespace ft {
// =============================================================================
// Canonic
// =============================================================================
template <class T, class Alloc>
vector<T, Alloc>::vector(size_type n, const_reference value, const Alloc &alloc)
    : __alloc_(alloc) {
  if (n > max_size()) {
    __throw_length_error();
  }
  __vallocate(n);
  __construct_at_end(n, value);
}
template <class T, class Alloc>
template <class InputIterator>
vector<T, Alloc>::vector(
    InputIterator                           first,
    typename enable_if<is_input_iterator<InputIterator>::value,
                       InputIterator>::type last,
    const Alloc                            &alloc)
    : __alloc_(alloc) {
  size_t        n  = 0;
  InputIterator it = first;
  while (it != last) {
    ++it;
    ++n;
  }
  __vallocate(n);
  __end_ = __begin_ + n;
  std::uninitialized_copy(first, last, __begin_);
}
template <class T, class Alloc>
vector<T, Alloc>::vector(const vector &v) : __alloc_(Alloc()) {
  __vallocate(v.size());
  std::uninitialized_copy(v.__begin_, v.__end_, __begin_);
  __end_ = __begin_ + v.size();
}
// ~vector
template <class T, class Alloc>
vector<T, Alloc>::~vector() {
  if (__begin_) {
    __alloc_.deallocate(__begin_, __end_cap_ - __begin_);
  }
}
// =============================================================================
// Element access
// =============================================================================
template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type n) {
  if (n >= size()) {
    __throw_out_of_range();
  }
  return __begin_[n];
}
template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(
    size_type n) const {
  if (n >= size()) {
    __throw_out_of_range();
  }
  return __begin_[n];
}
// =============================================================================
// Capacity
// =============================================================================
// max_size()
template <class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const {
  return std::min<size_type>(std::numeric_limits<difference_type>::max(),
                             std::numeric_limits<size_type>::max()) /
         sizeof(value_type);
}
// reserve()
template <class T, class Alloc>
void vector<T, Alloc>::reserve(size_type n) {
  if (n > capacity()) {
    if (n > max_size()) {
      __throw_length_error();
    }
    pointer new_begin   = __alloc_.allocate(n);
    pointer new_end     = new_begin + size();
    pointer new_end_cap = new_begin + n;
    std::uninitialized_copy(__begin_, __end_, new_begin);
    // TODO(kohkubo) ダブルフリーが起きる描き方になっている？
    __destroy_range(__begin_, __end_);
    __alloc_.deallocate(__begin_, capacity());
    __begin_   = new_begin;
    __end_     = new_end;
    __end_cap_ = new_end_cap;
  }
}
// =============================================================================
// private menber function
// =============================================================================
template <class T, class Alloc>
void vector<T, Alloc>::__construct_at_end(size_type n, const_reference x) {
  __end_ = __begin_ + n;
  std::uninitialized_fill(__begin_, __end_, x);
}
// template <class T, class Alloc>
// template <class InputIterator>
// void vector<T, Alloc>::__construct_at_end(
//     InputIterator first,
//     typename enable_if<!is_integral<InputIterator>::value,
//     InputIterator>::type
//                       last) {
//   __end_ = __begin_ + __distance(first, last);
//   std::uninitialized_copy(first, last, __begin_);
// }

// __destroy_range
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

// iterator_to_pointer
template <class T, class Alloc>
inline typename vector<T, Alloc>::pointer
vector<T, Alloc>::__iterator_to_pointer(iterator it) {
  return &(*it);
}

// =============================================================================
// Modifiers
// =============================================================================
// clear()
template <class T, class Alloc>
void vector<T, Alloc>::clear() {
  __destroy_range(__begin_, __end_);
  __end_ = __begin_;
}

// insert()
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
    iterator position, const_reference x) {
  if (position == end()) {
    push_back(x);
    return end() - 1;
  }
  if (size() == capacity()) {
    reserve(size() + 1);
  }
  pointer pos = __iterator_to_pointer(position);
  pointer new_end = __end_ + 1;
  pointer new_pos = __end_;
  __alloc_.construct(__end_, *(__end_ - 1));
  while (new_pos != pos) {
    *(new_pos) = *(new_pos - 1);
    --new_pos;
  }
  *new_pos = x;
  ++__end_;
  return new_pos;
}

// erase()
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(
    typename vector<T, Alloc>::iterator first,
    typename vector<T, Alloc>::iterator last) {
  __destroy_range(__iterator_to_pointer(first), __iterator_to_pointer(last));
  std::copy(__iterator_to_pointer(last), __end_, __iterator_to_pointer(first));
  __end_ -= last - first;
  return first;
}
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(
    typename vector<T, Alloc>::iterator pos) {
  return erase(pos, pos + 1);
}

// push_back()
template <class T, class Alloc>
void vector<T, Alloc>::push_back(const_reference x) {
  if (__end_ == __end_cap_) {
    reserve(capacity() + 1);
  }
  __alloc_.construct(__end_, x);
  ++__end_;
}

// pop_back()
template <class T, class Alloc>
void vector<T, Alloc>::pop_back() {
  if (__end_ != __begin_) {
    --__end_;
    __alloc_.destroy(__end_);
  }
}

// resize()
template <class T, class Alloc>
void vector<T, Alloc>::resize(size_type n, const_reference x) {
  if (n > size()) {
    if (n > max_size()) {
      __throw_length_error();
    }
    __construct_at_end(n - size(), x);
  } else if (n < size()) {
    __destroy_range(__begin_ + n, __end_);
    __end_ = __begin_ + n;
  }
}

// swap()
template <class T, class Alloc>
void vector<T, Alloc>::swap(vector &v) {
  std::swap(__begin_, v.__begin_);
  std::swap(__end_, v.__end_);
  std::swap(__end_cap_, v.__end_cap_);
}
}  // namespace ft

#endif  // INCLUDES_VECTOR_HPP_
