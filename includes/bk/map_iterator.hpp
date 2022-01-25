#ifndef INCLUDES_MAP_ITERATOR_HPP_
#define INCLUDES_MAP_ITERATOR_HPP_

#include "random_access_iterator.hpp"

namespace ft {

template <class _TreeIterator>
class map_iterator {
  typedef typename _TreeIterator::_NodeTypes       _NodeTypes;
  typedef typename _TreeIterator::__pointer_traits __pointer_traits;
  _TreeIterator                                    __i_;

 public:
  typedef std::bidirectional_iterator_tag               iterator_category;
  typedef typename _NodeTypes::__map_value_type         value_type;
  typedef typename _TreeIterator::difference_type       difference_type;
  typedef value_type&                                   reference;
  typedef typename _NodeTypes::__map_value_type_pointer pointer;
  map_iterator() {}
  map_iterator(_TreeIterator __i) : __i_(__i) {}
  reference operator*() const { return __i_->__get_value(); }
  pointer   operator->() const {
    return __pointer_traits<pointer>::pointer_to(__i_->__get_value());
  }
  map_iterator& operator++() {
    ++__i_;
    return *this;
  }
  map_iterator operator++(int) {
    map_iterator __t(*this);
    ++(*this);
    return __t;
  }
  map_iterator& operator--() {
    --__i_;
    return *this;
  }
  map_iterator operator--(int) {
    map_iterator __t(*this);
    --(*this);
    return __t;
  }

  friend bool operator==(const map_iterator& __x, const map_iterator& __y) {
    return __x.__i_ == __y.__i_;
  }
  friend bool operator!=(const map_iterator& __x, const map_iterator& __y) {
    return __x.__i_ != __y.__i_;
  }

  template <class, class, class, class>
  friend class map;

  template <class, class, class, class>
  friend class multimap;

  template <class>
  friend class map_const_iterator;
};

template <class _TreeIterator>
class map_const_iterator {
  typedef typename _TreeIterator::_NodeTypes       _NodeTypes;
  typedef typename _TreeIterator::__pointer_traits __pointer_traits;
  _TreeIterator                                    __i_;

 public:
  typedef std::bidirectional_iterator_tag                     iterator_category;
  typedef typename _NodeTypes::__map_value_type               value_type;
  typedef typename _TreeIterator::difference_type             difference_type;
  typedef const value_type&                                   reference;
  typedef typename _NodeTypes::__const_map_value_type_pointer pointer;

  map_const_iterator() {}
  map_const_iterator(_TreeIterator __i) : __i_(__i) {}
  map_const_iterator(
      __map_iterator<typename _TreeIterator::__non_const_iterator> __i)
      : __i_(__i.__i_) {}
  reference operator*() const { return __i_->__get_value(); }
  pointer   operator->() const {
    return __pointer_traits<pointer>::pointer_to(__i_->__get_value());
  }
  map_const_iterator& operator++() {
    ++__i_;
    return *this;
  }
  map_const_iterator operator++(int) {
    map_const_iterator __t(*this);
    ++(*this);
    return __t;
  }
  map_const_iterator& operator--() {
    --__i_;
    return *this;
  }
  map_const_iterator operator--(int) {
    map_const_iterator __t(*this);
    --(*this);
    return __t;
  }

  friend bool operator==(const map_const_iterator& __x,
                         const map_const_iterator& __y) {
    return __x.__i_ == __y.__i_;
  }
  friend bool operator!=(const map_const_iterator& __x,
                         const map_const_iterator& __y) {
    return __x.__i_ != __y.__i_;
  }
  template <class, class, class, class>
  friend class map;

  template <class, class, class, class>
  friend class multimap;

  template <class, class, class>
  friend class __tree_const_iterator;
};

template <class Key, class CP, class Compare>
class map_value_compare<Key, CP, Compare, false> {
    Compare __comp_;
public:
    map_value_compare(): __comp_() {}
    map_value_compare(Compare c) : __comp_(c) {}
    const Compare& key_comp() const { return __comp_; }
    bool operator()(const CP& __x, const CP& __y) const {
        return __comp_(__x.__get_value().first, __y.__get_value().first);
    }
    
};
}




}  // namespace ft

#endif  // INCLUDES_MAP_ITERATOR_HPP_
