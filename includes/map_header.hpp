// Copyright (c) 2022 kohkubo

#ifndef INCLUDES_MAP_HEADER_HPP_
#define INCLUDES_MAP_HEADER_HPP_

#include <memory>

#include "aatree.hpp"
#include "pair.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "type_traits.hpp"

namespace ft {

// template <class Key, class CP, class Compare, bool =
// is_empty<Compare>::value> class __map_value_compare : private Compare {
//  public:
//   __map_value_compare() : Compare() {}
//   __map_value_compare(Compare c) : Compare(c) {}
//   const Compare& key_comp() const { return *this; }
//   bool           operator()(const CP& x, const CP& y) const {
//     return static_cast<const Compare&>(*this)(x.__get_value().first,
//     y.__get_value().first);
//   }
//   bool operator()(const CP& x, const Key& y) const {
//     return static_cast<const Compare&>(*this)(x.__get_value().first, y);
//   }
//   bool operator()(const Key& x, const CP& y) const {
//     return static_cast<const Compare&>(*this)(x, y.__get_value().first);
//   }
//   void swap(__map_value_compare& y) { std::swap(static_cast<Compare&>(*this),
//   static_cast<Compare&>(y)); }
// };

// template <class Key, class CP, class Compare, bool b>
// inline void swap(__map_value_compare<Key, CP, Compare, b>& x,
// __map_value_compare<Key, CP, Compare, b>& y) {
//   x.swap(y);
// }

// template <class Key, class T>
// struct __value_type {
//   typedef Key                                   key_type;
//   typedef T                                     mapped_type;
//   typedef ft::pair<const key_type, mapped_type> value_type;

//   value_type&                                   __get_value() { return __cc_;
//   } const value_type&                             __get_value() const {
//   return __cc_; }

//  private:
//   value_type __cc_;

//  private:
//   __value_type();
//   __value_type(const __value_type&);
//   __value_type& operator=(const __value_type&);
//   ~__value_type();
// };

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
  map();
  explicit map(const Compare& comp, const Alloc& alloc = Alloc());
  template <class InputIterator>
  map(InputIterator first, InputIterator last, const Compare& comp = Compare(),
      const Alloc& alloc = Alloc());
  map(const map& x);
  map&                   operator=(const map& m);
  allocator_type         get_allocator() const;
  // ===========================================================================
  // element access:
  // ===========================================================================
  mapped_type&           operator[](const key_type& k);
  // ===========================================================================
  // iterators:
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
  // capacity:
  // ===========================================================================
  bool                   empty() const;
  size_type              size() const;
  size_type              max_size() const;
  // ===========================================================================
  // modifiers:
  // ===========================================================================
  void                   clear();
  pair<iterator, bool>   insert(const value_type& v);
  iterator               insert(iterator position, const value_type& v);
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
  const_iterator           find(const key_type& k) const;
  pair<iterator, iterator> equal_range(const key_type& k);
  pair<const_iterator, const_iterator> equal_range(const key_type& k) const;
  iterator                             lower_bound(const key_type& k);
  const_iterator                       lower_bound(const key_type& k) const;
  iterator                             upper_bound(const key_type& k);
  const_iterator                       upper_bound(const key_type& k) const;
  // ===========================================================================
  // observers:
  // ===========================================================================
  key_compare                          key_comp() const;
  value_compare                        value_comp() const;
  // ===========================================================================
  // private:
  // ===========================================================================
 private:
  typedef AATree<value_type> __Base;
  __Base                     __tree_;
};

}  // namespace ft

#endif  // INCLUDES_MAP_HEADER_HPP_
