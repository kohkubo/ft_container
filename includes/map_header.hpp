// Copyright (c) 2022 kohkubo

#ifndef INCLUDES_MAP_HEADER_HPP_
#define INCLUDES_MAP_HEADER_HPP_

#include <memory>

#include "rb_tree_header.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "type_traits.hpp"

namespace ft {

template <class _Key, class _Tp, class _Compare = std::less<_Key>,
          class _Allocator = std::allocator<pair<const _Key, _Tp> > >
class map {
 public:
  // types:
  typedef _Key                                     key_type;
  typedef _Tp                                      mapped_type;
  typedef pair<const key_type, mapped_type>        value_type;
  typedef _Compare                                 key_compare;
  typedef _Allocator                               allocator_type;
  typedef typename allocator_type::reference       reference;
  typedef typename allocator_type::const_reference const_reference;

 private:
  typedef __tree<value_type, key_compare, allocator_type> __base;
  __base                                                  __tree_;

 public:
  typedef typename allocator_type::pointer         pointer;
  typedef typename allocator_type::const_pointer   const_pointer;
  typedef typename allocator_type::size_type       size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename __base::iterator                iterator;
  // typedef typename __base::iterator                const_iterator;
  // typedef ft::reverse_iterator<iterator>           reverse_iterator;
  // typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

  // ===========================================================================
  // construct/copy/destroy:
  // ===========================================================================
  class value_compare {
    friend class map;

   protected:
    key_compare comp;
    value_compare(key_compare c);

   public:
    typedef bool       result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    };
  };
  // ===========================================================================
  // construct/copy/destroy:
  // ===========================================================================
  map() : __tree_(){};
  explicit map(const _Compare& comp, const _Allocator& alloc = _Allocator());
  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const _Compare&   comp  = _Compare(),
      const _Allocator& alloc = _Allocator());
  map(const map& x);
  map&                 operator=(const map& m);
  allocator_type       get_allocator() const;
  // ===========================================================================
  // element access:
  // ===========================================================================
  mapped_type&         operator[](const key_type& k);
  // ===========================================================================
  // iterators:
  // ===========================================================================
  // iterator             begin();
  // const_iterator         begin() const;
  // iterator             end();
  // const_iterator         end() const;
  // reverse_iterator     rbegin();
  // const_reverse_iterator rbegin() const;
  // reverse_iterator     rend();
  // const_reverse_iterator rend() const;
  // ===========================================================================
  // capacity:
  // ===========================================================================
  bool                 empty() const;
  size_type            size() const;
  size_type            max_size() const;
  // ===========================================================================
  // modifiers:
  // ===========================================================================
  void                 clear();
  pair<iterator, bool> insert(const value_type& v) {
    return __tree_.__insert_unique(v);
  }
  iterator insert(iterator position, const value_type& v);
  template <class InputIterator>
  void                     insert(InputIterator first, InputIterator last);
  iterator                 erase(iterator position);
  iterator                 erase(iterator first, iterator last);
  size_type                erase(const key_type& k);
  void                     swap(map& x);
  // ===========================================================================
  // lookup:
  // ===========================================================================
  size_type                count(const key_type& k) const;
  iterator                 find(const key_type& k);
  // const_iterator           find(const key_type& k) const;
  pair<iterator, iterator> equal_range(const key_type& k);
  // pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
  iterator                 lower_bound(const key_type& k);
  // const_iterator                       lower_bound(const key_type& k) const;
  iterator                 upper_bound(const key_type& k);
  // const_iterator                       upper_bound(const key_type& k) const;
  // ===========================================================================
  // observers:
  // ===========================================================================
  key_compare              key_comp() const;
  value_compare            value_comp() const;
  // ===========================================================================
  // private:
  // ===========================================================================
};

}  // namespace ft

#endif  // INCLUDES_MAP_HEADER_HPP_
