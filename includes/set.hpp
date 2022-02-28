#ifndef INCLUDES_SET_HPP_
#define INCLUDES_SET_HPP_

#include <memory>

#include "algorithm.hpp"
#include "rb_tree.hpp"
#include "reverse_iterator.hpp"

namespace ft {
template <class Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<Key> >
class set {
 public:
  typedef Key                                      key_type;
  typedef key_type                                 value_type;
  typedef Compare                                  key_compare;
  typedef key_compare                              value_compare;
  typedef Allocator                                allocator_type;
  typedef typename allocator_type::reference       reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::size_type       size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::pointer         pointer;
  typedef typename allocator_type::const_pointer   const_pointer;

 private:
  typedef ft::__tree<value_type, value_compare, allocator_type> __base;
  __base                                                        __tree_;
  typedef typename __base::__node_pointer                       __node_pointer;

 public:
  typedef typename __base::iterator            iterator;
  typedef typename __base::const_iterator      const_iterator;
  typedef ft::reverse_iterator<iterator>       reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  // ===========================================================================
  // construct/copy/destroy:
  // ===========================================================================
  set() : __tree_(){};
  explicit set(const key_compare&    comp,
               const allocator_type& alloc = allocator_type())
      : __tree_(comp, alloc){};
  template <class InputIterator>
  set(InputIterator first, InputIterator last,
      const key_compare&    comp  = key_compare(),
      const allocator_type& alloc = allocator_type())
      : __tree_(first, last, comp, alloc){};
  set(const set& other): __tree_(other.__tree_) {}
  ~set(){};
  set& operator=(const set& other) {
    clear();
    insert(other.begin(), other.end());
    return *this;
  }
  allocator_type   get_allocator() const { return __tree_.get_allocator(); }
  // ===========================================================================
  // iterators:
  // ===========================================================================
  iterator         begin() { return __tree_.begin(); }
  const_iterator   begin() const { return __tree_.begin(); }
  iterator         end() { return __tree_.end(); }
  const_iterator   end() const { return __tree_.end(); }
  reverse_iterator rbegin() { return __tree_.rbegin(); }
  const_reverse_iterator rbegin() const { return __tree_.rbegin(); }
  reverse_iterator       rend() { return __tree_.rend(); }
  const_reverse_iterator rend() const { return __tree_.rend(); }
  // ===========================================================================
  // capacity:
  // ===========================================================================
  bool                   empty() const { return __tree_.empty(); }
  size_type              size() const { return __tree_.size(); }
  size_type              max_size() const { return __tree_.max_size(); }
  // ===========================================================================
  // modifiers:
  // ===========================================================================
  void                   clear() { __tree_.clear(); }
  pair<iterator, bool>   insert(const value_type& value) {
    return __tree_.insert(value);
  }
  iterator insert(iterator hint, const value_type& value) {
    return __tree_.insert(hint, value);
  }
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    __tree_.insert(first, last);
  }
  void      erase(iterator pos) { __tree_.erase(pos); }
  void      erase(iterator first, iterator last) { __tree_.erase(first, last); }
  size_type erase(const key_type& key) { return __tree_.erase(key); }
  void      swap(set& other) { __tree_.swap(other.__tree_); }
  // ===========================================================================
  // loolup:
  // ===========================================================================
  size_type count(const key_type& key) const { return __tree_.count(key); }
  iterator  find(const key_type& key) { return __tree_.find(key); }
  const_iterator find(const key_type& key) const { return __tree_.find(key); }
  pair<iterator, iterator> equal_range(const key_type& key) {
    return __tree_.equal_range(key);
  }
  pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
    return __tree_.equal_range(key);
  }
  iterator lower_bound(const key_type& key) { return __tree_.lower_bound(key); }
  const_iterator lower_bound(const key_type& key) const {
    return __tree_.lower_bound(key);
  }
  iterator upper_bound(const key_type& key) { return __tree_.upper_bound(key); }
  const_iterator upper_bound(const key_type& key) const {
    return __tree_.upper_bound(key);
  }
  // ===========================================================================
  // observers:
  // ===========================================================================
  key_compare   key_comp() const { return __tree_.__comp_; }
  value_compare value_comp() const { return __tree_.__comp_; }
};
// =============================================================================
// non-member functions:
// =============================================================================
template <class Key, class Compare, class Allocator>
inline bool operator==(const set<Key, Compare, Allocator>& lhs,
                       const set<Key, Compare, Allocator>& rhs) {
  return lhs.size() == rhs.size() &&
         ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}
template <class Key, class Compare, class Allocator>
inline bool operator!=(const set<Key, Compare, Allocator>& lhs,
                       const set<Key, Compare, Allocator>& rhs) {
  return !(lhs == rhs);
}
template <class Key, class Compare, class Allocator>
inline bool operator<(const set<Key, Compare, Allocator>& lhs,
                      const set<Key, Compare, Allocator>& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}
template <class Key, class Compare, class Allocator>
inline bool operator<=(const set<Key, Compare, Allocator>& lhs,
                       const set<Key, Compare, Allocator>& rhs) {
  return !(rhs < lhs);
}
template <class Key, class Compare, class Allocator>
inline bool operator>(const set<Key, Compare, Allocator>& lhs,
                      const set<Key, Compare, Allocator>& rhs) {
  return rhs < lhs;
}
template <class Key, class Compare, class Allocator>
inline bool operator>=(const set<Key, Compare, Allocator>& lhs,
                       const set<Key, Compare, Allocator>& rhs) {
  return !(lhs < rhs);
}
template <class Key, class Compare, class Allocator>
inline void swap(set<Key, Compare, Allocator>& lhs,
                 set<Key, Compare, Allocator>& rhs) {
  lhs.swap(rhs);
}
}  // namespace ft
#endif  // INCLUDES_SET_HPP_
