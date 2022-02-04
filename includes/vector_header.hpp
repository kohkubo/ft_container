// Copyright (c) 2022 kohkubo

#ifndef INCLUDES_VECTOR_HEADER_HPP_
#define INCLUDES_VECTOR_HEADER_HPP_

#include <iostream>
#include <memory>

#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "type_traits.hpp"

namespace ft {
template <class T, class Alloc = std::allocator<T> >
class vector {
 public:
  typedef T                                      value_type;
  typedef Alloc                                  allocator_type;
  typedef value_type&                            reference;
  typedef const value_type&                      const_reference;
  typedef std::size_t                            size_type;
  typedef std::ptrdiff_t                         difference_type;
  typedef typename allocator_type::pointer       pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef random_access_iterator<pointer>        iterator;
  typedef random_access_iterator<const_pointer>  const_iterator;
  typedef ft::reverse_iterator<iterator>         reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>   const_reverse_iterator;
  // ===========================================================================
  // Canonical
  // ===========================================================================
  vector() : __begin_(0), __end_(0), __end_cap_(0), __alloc_(Alloc()) {}
  explicit vector(const Alloc& alloc)
      : __begin_(0), __end_(0), __end_cap_(0), __alloc_(alloc) {}
  explicit vector(size_type n, const T& value = T(),
                  const Alloc& alloc = Alloc())
      : __alloc_(alloc) {
    if (n > max_size()) {
      __throw_length_error();
    }
    __vallocate(n);
    __end_ = __begin_ + n;
    std::uninitialized_fill(__begin_, __end_, value);
  }
  template <class InputIterator>
  vector(InputIterator                           first,
         typename enable_if<is_input_iterator<InputIterator>::value,
                            InputIterator>::type last,
         const Alloc&                            alloc = Alloc())
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
  vector(const vector& v) : __alloc_(Alloc()) {
    __vallocate(v.size());
    std::uninitialized_copy(v.__begin_, v.__end_, __begin_);
    __end_ = __begin_ + v.size();
  }
  ~vector() {
    if (__begin_) {
      __alloc_.deallocate(__begin_, __end_cap_ - __begin_);
    }
  }
  // ===========================================================================
  // Element access
  // ===========================================================================
  reference at(size_type n) {
    if (n >= size())
      __throw_out_of_range();
    return __begin_[n];
  }
  const_reference        at(size_type n) const { return at(n); }
  reference              operator[](size_type n) { return __begin_[n]; }
  const_reference        operator[](size_type n) const { return __begin_[n]; }
  reference              front() { return *__begin_; }
  const_reference        front() const { return *__begin_; }
  reference              back() { return *(__end_ - 1); }
  const_reference        back() const { return *(__end_ - 1); }
  // ===========================================================================
  // Iterators
  // ===========================================================================
  iterator               begin() { return iterator(__begin_); }
  const_iterator         begin() const { return const_iterator(__begin_); }
  iterator               end() { return iterator(__end_); }
  const_iterator         end() const { return const_iterator(__end_); }
  reverse_iterator       rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator       rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { const_reverse_iterator(begin()); }
  // ===========================================================================
  // Capacity
  // ===========================================================================
  bool                   empty() const { return __begin_ == __end_; }
  size_type              size() const { return __end_ - __begin_; }
  size_type              max_size() const {
    return std::min(std::numeric_limits<size_type>::max(), __alloc_.max_size());
  }
  void reserve(size_type n) {
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
  size_type capacity() const { return __end_cap_ - __begin_; }
  // ===========================================================================
  // Modifiers
  // ===========================================================================
  void      clear();
  iterator  insert(iterator pos, const_reference value);
  void      insert(iterator pos, size_type n, const_reference value);
  template <class InputIterator>
  void     insert(InputIterator pos, InputIterator first, InputIterator last);
  iterator erase(iterator pos);
  iterator erase(iterator first, iterator last);
  void     push_back(const_reference value);
  void     pop_back();
  void     resize(size_type n, const_reference value = T());
  void     swap(vector& x);
  // ===========================================================================
  // Others
  // ===========================================================================
  vector&  operator=(const vector& v) {
    if (this != &v) {
      __vdeallocate();
      __vallocate(v.size());
      std::uninitialized_copy(v.__begin_, v.__end_, __begin_);
      __end_ = __begin_ + v.size();
    }
    return *this;
  }
  void assign(size_type n, const_reference value) {
    if (n > max_size()) {
      __throw_length_error();
    }
    if (n > capacity()) {
      __vdeallocate();
      __vallocate(n);
    }
    __destroy_range(__begin_, __end_);
    std::uninitialized_fill_n(__begin_, n, value);
    __end_ = __begin_ + n;
  }
  template <class InputIterator>
  void assign(InputIterator first, InputIterator last) {
    size_type n = last - first;
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
  allocator_type get_allocator() const { return __alloc_; }
  // ===========================================================================
  // Private members
  // ===========================================================================
 private:
  void           __throw_length_error() { throw std::length_error("vector"); }
  void           __throw_out_of_range() { throw std::out_of_range("vector"); }
  inline void    __destroy_range(pointer first, pointer last);
  void           __vallocate(size_type n);
  void           __vdeallocate();
  inline pointer __iterator_to_pointer(iterator it);

 protected:
  pointer        __begin_;
  pointer        __end_;
  pointer        __end_cap_;
  allocator_type __alloc_;
};
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
#endif  // INCLUDES_VECTOR_HEADER_HPP_
