// Copyright (c) 2022 kohkubo

#ifndef INCLUDES_MAP_HEADER_HPP_
#define INCLUDES_MAP_HEADER_HPP_

#include <memory>

#include "pair.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<pair<const Key, T> > >
class map {
 public:
  // types:
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



  class value_compare {
    friend class map;

   protected:
    key_compare comp;

   public:
    explicit value_compare(key_compare c);
    bool operator()(const value_type& x, const value_type& y) const;
  };

  // construct/copy/destroy:
  map();
  explicit map(const key_compare& comp);
  map(const key_compare& comp, const allocator_type& a);
  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare& comp = key_compare());
  template <class InputIterator>
  map(InputIterator first, InputIterator last, const key_compare& comp,
      const allocator_type& a);
  map(const map& m);
  map(const map& m, const allocator_type& a);


  map&                   operator=(const map& m);

  // iterators:
  iterator               begin();
  const_iterator         begin() const;
  iterator               end();
  const_iterator         end() const;

  reverse_iterator       rbegin();
  const_reverse_iterator rbegin() const;
  reverse_iterator       rend();
  const_reverse_iterator rend() const;

  const_iterator         cbegin() const;
  const_iterator         cend() const;
  const_reverse_iterator crbegin() const;
  const_reverse_iterator crend() const;

  // capacity:
  bool                   empty() const;
  size_type              size() const;
  size_type              max_size() const;

  // element access:
  mapped_type&           operator[](const key_type& k);
  mapped_type&           operator[](key_type&& k);

  mapped_type&           at(const key_type& k);
  const mapped_type&     at(const key_type& k) const;

  // modifiers:
  pair<iterator, bool>   insert(const value_type& v);
  iterator               insert(const_iterator position, const value_type& v);
  template <class InputIterator>
  void                     insert(InputIterator first, InputIterator last);

  iterator                 erase(const_iterator position);
  size_type                erase(const key_type& k);
  iterator                 erase(const_iterator first, const_iterator last);
  void                     clear();

  // observers:
  allocator_type           get_allocator() const;
  key_compare              key_comp() const;
  value_compare            value_comp() const;

  // map operations:
  iterator                 find(const key_type& k);
  const_iterator           find(const key_type& k) const;
  size_type                count(const key_type& k) const;

  iterator                 lower_bound(const key_type& k);
  const_iterator           lower_bound(const key_type& k) const;

  iterator                 upper_bound(const key_type& k);
  const_iterator           upper_bound(const key_type& k) const;

  pair<iterator, iterator> equal_range(const key_type& k);
  pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
};

}  // namespace ft

#endif  // INCLUDES_MAP_HEADER_HPP_
