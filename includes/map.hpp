#ifndef INCLUDES_MAP_HPP_
#define INCLUDES_MAP_HPP_

#include <memory>

#include "algorithm.hpp"
#include "pair.hpp"
#include "rb_tree.hpp"
#include "reverse_iterator.hpp"
#include "type_traits.hpp"

namespace ft {
template <typename _Key, typename _CP, typename _Compare>
class __map_value_compare : private _Compare {
  _Compare __comp_;
 public:
  __map_value_compare() : __comp_() {}
  __map_value_compare(const _Compare& __comp) : __comp_(__comp) {}

  const _Compare& key_comp() const { return __comp_; }
  bool            operator()(const _CP& __x, const _CP& __y) const {
    return __comp_(__x.first, __y.first);
  }
  bool operator()(const _CP& __x, const _Key& __y) const {
    return __comp_(__x.first, __y);
  }
  bool operator()(const _Key& __x, const _CP& __y) const {
    return __comp_(__x, __y.first);
  }
  void swap(__map_value_compare& __c) { __comp_.swap(__c.__comp_); }
};

template <class _Key, class _Tp, class _Compare = std::less<_Key>,
          class _Allocator = std::allocator<pair<const _Key, _Tp> > >
class map {
 public:
  typedef _Key                              key_type;
  typedef _Tp                               mapped_type;
  typedef pair<const key_type, mapped_type> value_type;
  typedef _Compare                          key_compare;
  typedef _Allocator                        allocator_type;
  typedef value_type&                       reference;
  typedef const value_type&                 const_reference;

 public:
  class value_compare {
    friend class map;

   protected:
    key_compare comp;
    value_compare(key_compare c) : comp(c) {}

   public:
    typedef bool       result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    };
  };

 private:
  typedef __map_value_compare<key_type, value_type, key_compare> __vc;
  typedef __tree<value_type, __vc, allocator_type>               __base;
  __base                                                         __tree_;
  typedef typename __base::__node_pointer                        __node_pointer;

 public:
  typedef typename allocator_type::pointer              pointer;
  typedef typename allocator_type::const_pointer        const_pointer;
  typedef typename allocator_type::size_type            size_type;
  typedef typename allocator_type::difference_type      difference_type;
  typedef typename __base::iterator                     iterator;
  typedef typename __base::const_iterator               const_iterator;
  typedef typename ft::reverse_iterator<iterator>       reverse_iterator;
  typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

  // ===========================================================================
  // construct/copy/destroy:
  // ===========================================================================
  map() : __tree_(__vc(key_compare())){};
  explicit map(const _Compare& comp, const _Allocator& alloc = _Allocator())
      : __tree_(__vc(comp), alloc){};
  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const _Compare&   comp  = _Compare(),
      const _Allocator& alloc = _Allocator())
      : __tree_(first, last, __vc(comp), alloc){};
  map(const map& other) : __tree_(other.__tree_){};
  ~map(){};
  map& operator=(const map& other) {
    clear();
    insert(other.begin(), other.end());
    return *this;
  };
  allocator_type get_allocator() const { return __tree_.get_allocator(); };
  // ===========================================================================
  // element access:
  // ===========================================================================
  mapped_type&   operator[](const key_type& k) {
    return insert(value_type(k, mapped_type())).first->second;
  };
  // ===========================================================================
  // iterators:
  // ===========================================================================
  iterator               begin() { return __tree_.begin(); };
  const_iterator         begin() const { return __tree_.begin(); };
  iterator               end() { return __tree_.end(); };
  const_iterator         end() const { return __tree_.end(); };
  reverse_iterator       rbegin() { return __tree_.rbegin(); };
  const_reverse_iterator rbegin() const { return __tree_.rbegin(); };
  reverse_iterator       rend() { return __tree_.rend(); };
  const_reverse_iterator rend() const { return __tree_.rend(); };
  // ===========================================================================
  // capacity:
  // ===========================================================================
  bool                   empty() const { return __tree_.empty(); };
  size_type              size() const { return __tree_.size(); };
  size_type              max_size() const { return __tree_.max_size(); };
  // ===========================================================================
  // modifiers:
  // ===========================================================================
  void                   clear() { __tree_.clear(); };
  pair<iterator, bool> insert(const value_type& v) { return __tree_.insert(v); }
  iterator             insert(iterator position, const value_type& v) {
    return __tree_.insert(position, v);
  }
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    __tree_.insert(first, last);
  }
  iterator erase(iterator position) { return __tree_.erase(position); }
  iterator erase(iterator first, iterator last) {
    return __tree_.erase(first, last);
  }
  size_type      erase(const key_type& k) { return __tree_.erase(k); }
  void           swap(map& x) { __tree_.swap(x.__tree_); }
  // ===========================================================================
  // lookup:
  // ===========================================================================
  size_type      count(const key_type& k) const { return __tree_.count(k); }
  iterator       find(const key_type& k) { return __tree_.find(k); }
  const_iterator find(const key_type& k) const { return __tree_.find(k); }
  pair<iterator, iterator> equal_range(const key_type& k) {
    return __tree_.equal_range(k);
  }
  pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
    return __tree_.equal_range(k);
  }
  iterator lower_bound(const key_type& k) { return __tree_.lower_bound(k); }
  const_iterator lower_bound(const key_type& k) const {
    return __tree_.lower_bound(k);
  }
  iterator upper_bound(const key_type& k) { return __tree_.upper_bound(k); }
  const_iterator upper_bound(const key_type& k) const {
    return __tree_.upper_bound(k);
  }
  // ===========================================================================
  // observers:
  // ===========================================================================
  key_compare   key_comp() const { return __tree_.__comp_.key_comp(); }
  value_compare value_comp() const {
    return value_compare(__tree_.__comp_.key_comp());
  }
};
// =============================================================================
// non-member functions:
// =============================================================================
template <class Key, class T, class Compare, class Allocator>
inline bool operator==(const map<Key, T, Compare, Allocator>& __x,
                       const map<Key, T, Compare, Allocator>& __y) {
  return __x.size() == __y.size() &&
         ft::equal(__x.begin(), __x.end(), __y.begin());
}
template <class Key, class T, class Compare, class Allocator>
inline bool operator!=(const map<Key, T, Compare, Allocator>& __x,
                       const map<Key, T, Compare, Allocator>& __y) {
  return !(__x == __y);
}
template <class Key, class T, class Compare, class Allocator>
inline bool operator<(const map<Key, T, Compare, Allocator>& __x,
                      const map<Key, T, Compare, Allocator>& __y) {
  return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(),
                                     __y.end());
}
template <class Key, class T, class Compare, class Allocator>
inline bool operator<=(const map<Key, T, Compare, Allocator>& __x,
                       const map<Key, T, Compare, Allocator>& __y) {
  return !(__y < __x);
}
template <class Key, class T, class Compare, class Allocator>
inline bool operator>(const map<Key, T, Compare, Allocator>& __x,
                      const map<Key, T, Compare, Allocator>& __y) {
  return __y < __x;
}
template <class Key, class T, class Compare, class Allocator>
inline bool operator>=(const map<Key, T, Compare, Allocator>& __x,
                       const map<Key, T, Compare, Allocator>& __y) {
  return !(__x < __y);
}
template <class Key, class T, class Compare, class Allocator>
inline void swap(map<Key, T, Compare, Allocator>& __x,
                 map<Key, T, Compare, Allocator>& __y) {
  __x.swap(__y);
}
}  // namespace ft

#endif  // INCLUDES_MAP_HPP_
