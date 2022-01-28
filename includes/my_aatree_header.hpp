#ifndef INCLUDES_MY_AATREE_HEADER_HPP_
#define INCLUDES_MY_AATREE_HEADER_HPP_

#include <memory>

#include "iterator.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
namespace ft {

template <class _Key, class _Value>
struct __value_type;

template <class _Tp>
struct __tree_key_value_types {
  typedef _Tp                          key_type;
  typedef _Tp                          __node_value_type;
  typedef _Tp                          __container_value_type;
  static const bool                    __is_map = false;
  static __container_value_type const& __get_value(
      __node_value_type const& __v) {
    return __v;
  }
};

template <class _Key, class _Tp>
struct __tree_key_value_types<__value_type<_Key, _Tp> > {
  typedef _Key                         key_type;
  typedef _Tp                          mapped_type;
  typedef __value_type<_Key, _Tp>      __node_value_type;
  typedef pair<const _Key, _Tp>        __container_value_type;
  typedef __container_value_type       __map_value_type;
  static const bool                    __is_map = true;
  static __container_value_type const& __get_value(
      __node_value_type const& __t) {
    return __t.__get_value();
  }
  template <class _Up>
  static
      typename enable_if<__is_same_uncvref<_Up, __container_value_type>::value,
                         __container_value_type const&>::type
      __get_value(_Up& __t) {
    return __t;
  }
};

template <class _From, class _To>
struct __rebind_pointer {
  typedef typename std::pointer_traits<_From>::template rebind<_To>::other type;
};

template <class _Tp, class _AllocPtr,
          class _KVTypes = __tree_key_value_types<_Tp>,
          bool           = _KVTypes::__is_map>
struct __tree_map_pointer_types {};

template <class _Tp, class _AllocPtr, class _KVTypes>
struct __tree_map_pointer_types<_Tp, _AllocPtr, _KVTypes, true> {
  typedef typename _KVTypes::__map_value_type _Mv;
  typedef
      typename __rebind_pointer<_AllocPtr, _Mv>::type __map_value_type_pointer;
};

template <class _TreeIterator>
class __map_iterator {
  _TreeIterator __i_;

 public:
  typedef _TreeIterator iterator_type;
  typedef
      typename iterator_traits<_TreeIterator>::difference_type difference_type;
  typedef typename iterator_traits<_TreeIterator>::value_type  value_type;
  typedef typename iterator_traits<_TreeIterator>::pointer     pointer;
  typedef typename iterator_traits<_TreeIterator>::reference   reference;
  typedef std::bidirectional_iterator_tag iterator_category;
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

// template <class _Tp, class _NodePtr, class _DiffType>
// class __tree_iterator {
//   typedef __tree_node_types<_NodePtr>              _NodeTypes;
//   typedef _NodePtr                                 __node_pointer;
//   typedef typename _NodeTypes::__node_base_pointer __node_base_pointer;
//   typedef typename _NodeTypes::__end_node_pointer  __end_node_pointer;
//   typedef typename _NodeTypes::__iter_pointer      __iter_pointer;
//   typedef std::pointer_traits<__node_pointer>      __pointer_traits;

//   __iter_pointer                                   __ptr_;

//  public:
//   typedef std::bidirectional_iterator_tag                iterator_category;
//   typedef _Tp                                            value_type;
//   typedef _DiffType                                      difference_type;
//   typedef value_type&                                    reference;
//   typedef typename _NodeTypes::__node_value_type_pointer pointer;

//   __tree_iterator() {}

//   reference operator*() const { return __get_np()->__value_; }
//   pointer   operator->() const {
//     return pointer_traits<pointer>::pointer_to(__get_np()->__value_);
//   }

//   __tree_iterator& operator++() {
//     __ptr_ =
//         static_cast<__iter_pointer>(_VSTD::__tree_next_iter<__end_node_pointer>(
//             static_cast<__node_base_pointer>(__ptr_)));
//     return *this;
//   }

//   __tree_iterator operator++(int) {
//     __tree_iterator __t(*this);
//     ++(*this);
//     return __t;
//   }

//   __tree_iterator& operator--() {
//     __ptr_ = static_cast<__iter_pointer>(
//         _VSTD::__tree_prev_iter<__node_base_pointer>(
//             static_cast<__end_node_pointer>(__ptr_)));
//     return *this;
//   }

//   __tree_iterator operator--(int) {
//     __tree_iterator __t(*this);
//     --(*this);
//     return __t;
//   }

//   friend bool operator==(const __tree_iterator& __x,
//                          const __tree_iterator& __y) {
//     return __x.__ptr_ == __y.__ptr_;
//   }
//   friend bool operator!=(const __tree_iterator& __x,
//                          const __tree_iterator& __y) {
//     return !(__x == __y);
//   }

//  private:
//   explicit __tree_iterator(__node_pointer __p) : __ptr_(__p) {}

//   explicit __tree_iterator(__end_node_pointer __p) : __ptr_(__p) {}

//   __node_pointer __get_np() const {
//     return static_cast<__node_pointer>(__ptr_);
//   }
//   template <class, class, class>
//   friend class __tree;
//   template <class, class, class>
//   friend class __tree_const_iterator;
//   template <class>
//   friend class __map_iterator;
//   template <class, class, class, class>
//   friend class map;
//   template <class, class, class, class>
//   friend class multimap;
//   template <class, class, class>
//   friend class set;
//   template <class, class, class>
//   friend class multiset;
// };

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
  typedef ft::reverse_iterator<iterator>           reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

 private:
  struct __AANode;
  typedef __AANode    node_type;
  typedef node_type*  node_pointer;
  typedef node_type*& node_reference;
  typedef typename allocator_type::template rebind<node_type>::other
      node_allocator_type;
  struct __AANode {
    value_type*  data_;
    node_pointer left_;
    node_pointer right_;
    size_type    level_;
    size_type    size_;
    __AANode() : data_(NULL), left_(NULL), right_(NULL), level_(1), size_(0) {}
    __AANode(value_type* data, node_pointer left = NULL,
             node_pointer right = NULL, size_type level = 1)
        : data_(data), left_(left), right_(right), level_(level), size_(0) {}
  };
  node_allocator_type __node_alloc_;
  node_pointer        __root_;
  node_pointer        __begin_node_;
  node_pointer        __end_node_; // T
  node_pointer        __null_node_;
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
  reference              operator[](const key_type& k);
  reference              operator[](size_type n);
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
  // pair<iterator, bool>   insert(value_type& v);
  void                   insert(const value_type& v);
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
 public:
  node_pointer __create_node(const value_type& v);
  void         __skew(node_reference x);
  void         __split(node_reference x);
  void         __rotateWithLeftChild(node_reference k2);
  void         __rotateWithRightChild(node_reference k1);
  void         __clear(node_reference node);
  void         __insert(const value_type& v, node_reference node);
  node_pointer __clone(node_pointer node) const;
  size_type    __size(node_pointer node) const;
  node_pointer __find(const key_type& k, node_pointer node) const;
  node_pointer __at(size_type i, node_pointer node) const;
};
}  // namespace ft

#endif  // INCLUDES_MY_AATREE_HEADER_HPP_
