// Copyright (c) 2022 kohkubo

#ifndef INCLUDES_MAP_HPP_
#define INCLUDES_MAP_HPP_

#include <memory>

#include "pair.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<pair<const Key, T> > >
class map {
 public:
  typedef Key                                       key_type;
  typedef T                                         mapped_type;
  typedef pair<const key_type, mapped_type>         value_type;
  typedef Compare                                   key_compare;
  typedef Alloc                                     allocator_type;
  typedef typename allocator_type::reference        reference;
  typedef typename allocator_type::const_reference  const_reference;
  typedef typename allocator_type::pointer          pointer;
  typedef typename allocator_type::const_pointer    const_pointer;
  typedef typename allocator_type::size_type        size_type;
  typedef typename allocator_type::difference_type  difference_type;
  typedef ft::random_access_iterator<pointer>       iterator;
  typedef ft::random_access_iterator<const_pointer> const_iterator;
  typedef ft::reverse_iterator<iterator>            reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>      const_reverse_iterator;
};

}  // namespace ft

#endif  // INCLUDES_MAP_HPP_
