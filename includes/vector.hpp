// Copyright (c) 2022 kohkubo

#ifndef INCLUDES_VECTOR_HPP_
#define INCLUDES_VECTOR_HPP_

#include <iostream>
#include <memory>

#include "random_access_iterator.hpp"
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

  // =====================================================================
  // Canonical
  // =====================================================================
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
  // =====================================================================
  // Element access
  // =====================================================================
  reference       at(size_type n);
  const_reference at(size_type n) const;
  reference       operator[](size_type n) { return __begin_[n]; }
  const_reference operator[](size_type n) const { return __begin_[n]; }
  reference       front() { return *__begin_; }
  const_reference front() const { return *__begin_; }
  reference       back() { return *(__end_ - 1); }
  const_reference back() const { return *(__end_ - 1); }
  // =====================================================================
  // Iterators
  // =====================================================================
  iterator        begin() { return __make_iter(__begin_); }
  const_iterator  begin() const { return __make_iter(__begin_); }
  iterator        end() { return __make_iter(__end_); }
  const_iterator  end() const { return __make_iter(__end_); }
  // =====================================================================
  // Capacity
  // =====================================================================
  bool            empty() const { return __begin_ == __end_; }
  size_type       size() const { return __end_ - __begin_; }
  // TODO(kohkubo)
  size_type       max_size() const;
  // TODO(kohkubo)
  void            reserve(size_type n);
  size_type       capacity() const { return __end_cap_ - __begin_; }
  // =====================================================================
  // Modifiers
  // =====================================================================
  // TODO(kohkubo)
  void            clear();
  iterator        insert(const_iterator pos, const T &value);
  iterator        insert(const_iterator pos, size_type n, const T &value);
  template <class InputIterator>
  iterator insert(const_iterator pos, InputIterator first, InputIterator last);
  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);
  // TODO(kohkubo)
  void     push_back(const T &value);
  void     pop_back();
  void     resize(size_type n, const T &value = T());
  void     swap(vector &x);

 private:
  void            __throw_length_error() { throw std::length_error("vector"); }
  void            __throw_out_of_range() { throw std::out_of_range("vector"); }
  inline iterator __make_iter(pointer p) { return iterator(p); }
  inline const_iterator __make_iter(const_pointer p) {
    return const_iterator(p);
  }
  void        __construct_at_end(size_type n, const_reference x = T());
  // template <class InputIterator>
  // void __construct_at_end(
  //     InputIterator first,
  //     typename enable_if<is_input_iterator<InputIterator>::value,
  //                        InputIterator>::type last);
  inline void __destroy_range(pointer first, pointer last);
  void        __vallocate(size_type n);
  void        __vdeallocate();
  size_t      __distance(pointer first, pointer last) const;

 protected:
  pointer        __begin_;
  pointer        __end_;
  pointer        __end_cap_;
  allocator_type __alloc_;
};
}  // namespace ft

#endif  // INCLUDES_VECTOR_HPP_
