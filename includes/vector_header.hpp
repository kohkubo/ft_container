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
  typedef T                                         value_type;
  typedef Alloc                                     allocator_type;
  typedef value_type                               &reference;
  typedef const value_type                         &const_reference;
  typedef std::size_t                               size_type;
  typedef std::ptrdiff_t                            difference_type;
  typedef typename allocator_type::pointer          pointer;
  typedef typename allocator_type::const_pointer    const_pointer;
  typedef ft::random_access_iterator<pointer>       iterator;
  typedef ft::random_access_iterator<const_pointer> const_iterator;
  typedef ft::reverse_iterator<iterator>            reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>      const_reverse_iterator;
  // ===========================================================================
  // Canonical
  // ===========================================================================
  vector() : __begin_(0), __end_(0), __end_cap_(0), __alloc_(Alloc()) {}
  explicit vector(const Alloc &alloc)
      : __begin_(0), __end_(0), __end_cap_(0), __alloc_(alloc) {}
  explicit vector(size_type n, const T &value = T(),
                  const Alloc &alloc = Alloc());
  template <class InputIterator>
  vector(InputIterator                           first,
         typename enable_if<is_input_iterator<InputIterator>::value,
                            InputIterator>::type last,
         const Alloc                            &alloc = Alloc());
  vector(const vector &x);
  ~vector();
  // ===========================================================================
  // Element access
  // ===========================================================================
  reference              at(size_type n);
  const_reference        at(size_type n) const;
  reference              operator[](size_type n) { return __begin_[n]; }
  const_reference        operator[](size_type n) const { return __begin_[n]; }
  reference              front() { return *__begin_; }
  const_reference        front() const { return *__begin_; }
  reference              back() { return *(__end_ - 1); }
  const_reference        back() const { return *(__end_ - 1); }
  // ===========================================================================
  // Iterators
  // ===========================================================================
  iterator               begin();
  const_iterator         begin() const;
  iterator               end();
  const_iterator         end() const;
  reverse_iterator       rbegin();
  const_reverse_iterator rbegin() const;
  reverse_iterator       rend();
  const_reverse_iterator rend() const;
  // ===========================================================================
  // Capacity
  // ===========================================================================
  bool                   empty() const { return __begin_ == __end_; }
  size_type              size() const { return __end_ - __begin_; }
  size_type              max_size() const;
  void                   reserve(size_type n);
  size_type              capacity() const { return __end_cap_ - __begin_; }
  // ===========================================================================
  // Modifiers
  // ===========================================================================
  void                   clear();
  iterator               insert(iterator pos, const_reference value);
  void insert(iterator pos, size_type n, const_reference value);
  template <class InputIterator>
  void     insert(typename vector<T, Alloc>::iterator pos, InputIterator first,
                  InputIterator last);
  iterator erase(iterator pos);
  iterator erase(iterator first, iterator last);
  void     push_back(const_reference value);
  void     pop_back();
  void     resize(size_type n, const_reference value = T());
  void     swap(vector &x);
  // ===========================================================================
  // Others
  // ===========================================================================
  vector  &operator=(const vector &x);
  void     assign(size_type n, const_reference value);
  template <class InputIterator>
  void           assign(InputIterator first, InputIterator last);
  allocator_type get_allocator() const { return __alloc_; }
  // ===========================================================================
  // Private members
  // ===========================================================================
 private:
  void            __throw_length_error() { throw std::length_error("vector"); }
  void            __throw_out_of_range() { throw std::out_of_range("vector"); }
  inline void     __destroy_range(pointer first, pointer last);
  void            __vallocate(size_type n);
  void            __vdeallocate();
  inline pointer  __iterator_to_pointer(iterator it);
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
bool operator==(const vector<T, Alloc> &x, const vector<T, Alloc> &y);
template <class T, class Alloc>
bool operator!=(const vector<T, Alloc> &x, const vector<T, Alloc> &y);
template <class T, class Alloc>
bool operator<(const vector<T, Alloc> &x, const vector<T, Alloc> &y);
template <class T, class Alloc>
bool operator>(const vector<T, Alloc> &x, const vector<T, Alloc> &y);
template <class T, class Alloc>
bool operator<=(const vector<T, Alloc> &x, const vector<T, Alloc> &y);
template <class T, class Alloc>
bool operator>=(const vector<T, Alloc> &x, const vector<T, Alloc> &y);
template <class T, class Alloc>
void swap(vector<T, Alloc> &x, vector<T, Alloc> &y);
}  // namespace ft
#endif  // INCLUDES_VECTOR_HEADER_HPP_
