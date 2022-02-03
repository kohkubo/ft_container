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
vector<T, Alloc>::vector(size_type n, const_reference value, const Alloc& alloc)
    : __alloc_(alloc) {
  if (n > max_size()) {
    __throw_length_error();
  }
  __vallocate(n);
  __end_ = __begin_ + n;
  std::uninitialized_fill(__begin_, __end_, value);
}
template <class T, class Alloc>
template <class InputIterator>
vector<T, Alloc>::vector(
    InputIterator                           first,
    typename enable_if<is_input_iterator<InputIterator>::value,
                       InputIterator>::type last,
    const Alloc&                            alloc)
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
vector<T, Alloc>::vector(const vector& v) : __alloc_(Alloc()) {
  __vallocate(v.size());
  std::uninitialized_copy(v.__begin_, v.__end_, __begin_);
  __end_ = __begin_ + v.size();
}
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
// Iterators
// =============================================================================
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() {
  return iterator(__begin_);
}
template <class T, class Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const {
  return const_iterator(__begin_);
}
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::end() {
  return iterator(__end_);
}
template <class T, class Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const {
  return const_iterator(__end_);
}
template <class T, class Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin() {
  return reverse_iterator(end());
}
template <class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin()
    const {
  return const_reverse_iterator(end());
}
template <class T, class Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend() {
  return reverse_iterator(begin());
}
template <class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend()
    const {
  return const_reverse_iterator(begin());
}
// =============================================================================
// Capacity
// =============================================================================
template <class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const {
  return std::min<size_type>(__alloc_.max_size(),
                             std::numeric_limits<size_type>::max());
}
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
    __destroy_range(__begin_, __end_);
    __alloc_.deallocate(__begin_, capacity());
    __begin_   = new_begin;
    __end_     = new_end;
    __end_cap_ = new_end_cap;
  }
}
// =============================================================================
// Others
// =============================================================================
template <class T, class Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& v) {
  if (this != &v) {
    __vdeallocate();
    __vallocate(v.size());
    std::uninitialized_copy(v.__begin_, v.__end_, __begin_);
    __end_ = __begin_ + v.size();
  }
  return *this;
}
template <class T, class Alloc>
void vector<T, Alloc>::assign(size_type n, const_reference val) {
  if (n > max_size()) {
    __throw_length_error();
  }
  if (n > capacity()) {
    __vdeallocate();
    __vallocate(n);
  }
  __destroy_range(__begin_, __end_);
  std::uninitialized_fill_n(__begin_, n, val);
  __end_ = __begin_ + n;
}
template <class T, class Alloc>
template <class InputIterator>
void vector<T, Alloc>::assign(InputIterator first, InputIterator last) {
  size_type n = std::distance(first, last);
  if (n > max_size()) {
    __throw_length_error();
  }
  if (n > capacity()) {
    __vdeallocate();
    __vallocate(n);
  }
  __destroy_range(__begin_, __end_);
  std::uninitialized_copy(first, last, __begin_);
  __end_ = __begin_ + n;
}
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
  size_t n         = std::distance(first, last);
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
// =============================================================================
// Non-member functions
// =============================================================================
template <class T, class Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}
template <class T, class Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs == rhs);
}
template <class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end());
}
template <class T, class Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return rhs < lhs;
}
template <class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(rhs < lhs);
}
template <class T, class Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs < rhs);
}
template <class T, class Alloc>
void vector<T, Alloc>::swap(vector& v) {
  std::swap(__begin_, v.__begin_);
  std::swap(__end_, v.__end_);
  std::swap(__end_cap_, v.__end_cap_);
}
}  // namespace ft
#endif  // INCLUDES_VECTOR_HPP_
