#ifndef INCLUDES_MY_AATREE_HEADER_HPP_
#define INCLUDES_MY_AATREE_HEADER_HPP_

#include <memory>

#include "iterator.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<pair<const Key, T> > >
class AATree {
 public:
  typedef Key                                      key_type;
  typedef T                                        mapped_type;
  typedef pair<const key_type, mapped_type>        value_type;
  typedef Compare                                  key_compare;
  typedef Alloc                                    allocator_type;
  typedef mapped_type&                             reference;
  typedef const mapped_type&                       const_reference;
  typedef typename allocator_type::pointer         pointer;
  typedef typename allocator_type::const_pointer   const_pointer;
  typedef typename allocator_type::size_type       size_type;
  typedef typename allocator_type::difference_type difference_type;
  // typedef __tree_iterator<value_type, pointer, difference_type> iterator;
  // typedef __tree_iterator<value_type, const_pointer, difference_type>
  //  const_iterator;
  typedef ft::__map_iterator<pointer>              iterator;
  typedef ft::__map_iterator<const_pointer>        const_iterator;
  // typedef ft::reverse_iterator<iterator>           reverse_iterator;
  // typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

 private:
  struct __AANode;
  typedef __AANode      __node_type;
  typedef __node_type*  __node_pointer;
  typedef __node_type*& __node_reference;
  typedef typename allocator_type::template rebind<__node_type>::other
      node_allocator_type;
  struct __AANode {
    value_type*    data_;
    __node_pointer left_;
    __node_pointer right_;
    size_type      level_;
    size_type      size_;
    __AANode() : data_(NULL), left_(NULL), right_(NULL), level_(1), size_(0) {}
    __AANode(value_type* data, __node_pointer left = NULL,
             __node_pointer right = NULL, size_type level = 1)
        : data_(data), left_(left), right_(right), level_(level), size_(0) {}
  };
  node_allocator_type __node_alloc_;
  __node_pointer      __root_;
  __node_pointer      __begin_node_;
  __node_pointer      __end_node_;  // T
  __node_pointer      __null_node_;
  allocator_type      __alloc_;
  key_compare         __compare_;
  size_type           __size_;

 public:
  // ===========================================================================
  // construct/copy/destroy:
  // ===========================================================================
  AATree();
  explicit AATree(const Compare& comp, const Alloc& alloc = Alloc());
  template <class InputIterator>
  AATree(InputIterator first, InputIterator last,
         const Compare& comp = Compare(), const Alloc& alloc = Alloc());
  AATree(const AATree& x);
  AATree& operator=(const AATree& x);
  ~AATree();
  // ===========================================================================
  // element access:
  // ===========================================================================
  reference operator[](const key_type& k);
  // ===========================================================================
  // iterators:
  // ===========================================================================
  // iterator               begin();
  // const_iterator         begin() const;
  // iterator               end();
  // const_iterator         end() const;
  // reverse_iterator       rbegin();
  // const_reverse_iterator rbegin() const;
  // reverse_iterator       rend();
  // const_reverse_iterator rend() const;
  // ===========================================================================
  // capacity:
  // ===========================================================================
  bool      empty() const;
  size_type size() const;
  size_type max_size() const;
  // ===========================================================================
  // modifiers:
  // ===========================================================================
  void      clear();
  // pair<iterator, bool>   insert(value_type& v);
  void      insert(const value_type& v);
  iterator  insert(iterator position, const value_type& v);
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
 public:
  __node_pointer __create_node(const value_type& v);
  void           __skew(__node_reference x);
  void           __split(__node_reference x);
  void           __rotateWithLeftChild(__node_reference k2);
  void           __rotateWithRightChild(__node_reference k1);
  void           __clear(__node_reference node);
  void           __insert(const value_type& v, __node_reference node);
  __node_pointer __clone(__node_pointer node) const;
  size_type      __size(__node_pointer node) const;
  __node_pointer __find(const key_type& k, __node_pointer node) const;
  __node_pointer __at(size_type i, __node_pointer node) const;
};
}  // namespace ft

#endif  // INCLUDES_MY_AATREE_HEADER_HPP_
