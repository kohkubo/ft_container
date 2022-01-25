#ifndef INCLUDES_MY_AATREE_HEADER_HPP_
#define INCLUDES_MY_AATREE_HEADER_HPP_

#include <memory>

#include "iterator.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
namespace ft {

template <class _TreeIterator>
class __map_iterator {
  typedef typename _TreeIterator::_NodeTypes       _NodeTypes;
  typedef typename _TreeIterator::__pointer_traits __pointer_traits;
  _TreeIterator                                    __i_;

 public:
  typedef bidirectional_iterator_tag                    iterator_category;
  typedef typename _NodeTypes::__map_value_type         value_type;
  typedef typename _TreeIterator::difference_type       difference_type;
  typedef value_type&                                   reference;
  typedef typename _NodeTypes::__map_value_type_pointer pointer;
  __map_iterator() {}
  __map_iterator(_TreeIterator __i) : __i_(__i) {}
  reference operator*() const { return __i_->__get_value(); }
  pointer   operator->() const {
    // TODO 動く？
    return pointer(std::addressof(__i_->__get_value()));
  }
  __map_iterator& operator++() {
    ++__i_;
    return *this;
  }
  __map_iterator operator++(int) {
    __map_iterator __t(*this);
    ++(*this);
    return __t;
  }
  __map_iterator& operator--() {
    --__i_;
    return *this;
  }
  __map_iterator operator--(int) {
    __map_iterator __t(*this);
    --(*this);
    return __t;
  }
  friend bool operator==(const __map_iterator& __x, const __map_iterator& __y) {
    return __x.__i_ == __y.__i_;
  }
  friend bool operator!=(const __map_iterator& __x, const __map_iterator& __y) {
    return __x.__i_ != __y.__i_;
  }
  template <class, class, class, class>
  friend class map;
  template <class, class, class, class>
  friend class multimap;
  template <class>
  friend class __map_const_iterator;
};

template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<pair<const Key, T> > >
class AATree {
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
  typedef ft::tree_iterator<pointer>       iterator;
  typedef ft::tree_iterator<const_pointer> const_iterator;
  typedef ft::reverse_iterator<iterator>            reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>      const_reverse_iterator;
  // ===========================================================================
  // construct/copy/destroy:
  // ===========================================================================
  AATree();
  explicit AATree(const Compare& comp, const Alloc& alloc = Alloc());
  ~AATree();
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
  // private:
  // ===========================================================================
 private:
  struct __AANode {
    value_type* data_;
    __AANode*   left_;
    __AANode*   right_;
    size_t      level_;
    __AANode() : data_(NULL), left_(NULL), right_(NULL), level_(1) {}
    __AANode(value_type* data)
        : data_(data), left_(NULL), right_(NULL), level_(1) {}
  };
  typedef __AANode    node_type;
  typedef node_type*  node_pointer;
  typedef node_type*& node_reference;
  typedef typename allocator_type::template rebind<node_type>::other
                      node_allocator_type;
  node_allocator_type __node_alloc_;
  node_pointer        __root_;
  node_pointer        __null_node_;
  allocator_type      __alloc_;
  key_compare         __compare_;
  node_pointer        __create_node(const value_type& v);
  void                __skew(node_reference x);
  void                __split(node_reference x);
  void                __rotateWithLeftChild(node_reference k2);
  void                __rotateWithRightChild(node_reference k1);
  void                __clear(node_reference node);
  node_pointer        __insert(const value_type& v, node_reference node);
};
}  // namespace ft

#endif  // INCLUDES_MY_AATREE_HEADER_HPP_
