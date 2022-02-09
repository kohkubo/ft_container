#ifndef INCLUDES_STACK_HPP_
#define INCLUDES_STACK_HPP_

#include "vector.hpp"

namespace ft {
template <class _Tp, class _Container = vector<_Tp> >
class stack {
 public:
  typedef _Container                               container_type;
  typedef typename container_type::value_type      value_type;
  typedef typename container_type::reference       reference;
  typedef typename container_type::const_reference const_reference;
  typedef typename container_type::size_type       size_type;

 protected:
  container_type c;

 public:
  // ===========================================================================
  // canonic
  // ===========================================================================
  explicit stack(const container_type &c = container_type()) : c(c) {}
  stack(const stack &other) : c(other.c) {}
  ~stack() {}
  stack &operator=(const stack &other) {
    c = other.c;
    return *this;
  }
  // ===========================================================================
  // Element access
  // ===========================================================================
  reference       top() { return c.back(); }
  const_reference top() const { return c.back(); }
  // ===========================================================================
  // capacity
  // ===========================================================================
  bool            empty() const { return c.empty(); }
  size_type       size() const { return c.size(); }
  // ===========================================================================
  // Modifiers
  // ===========================================================================
  void            push(const value_type &x) { c.push_back(x); }
  void            pop() { c.pop_back(); }
  void            swap(stack &other) { c.swap(other.c); }
};
// =============================================================================
// operators
// =============================================================================
template <class _Tp, class _Container>
inline bool operator==(const stack<_Tp, _Container> &lhs,
                       const stack<_Tp, _Container> &rhs) {
  return lhs.c == rhs.c;
}
template <class _Tp, class _Container>
inline bool operator!=(const stack<_Tp, _Container> &lhs,
                       const stack<_Tp, _Container> &rhs) {
  return !(lhs == rhs);
}
template <class _Tp, class _Container>
inline bool operator<(const stack<_Tp, _Container> &lhs,
                      const stack<_Tp, _Container> &rhs) {
  return lhs.c < rhs.c;
}
template <class _Tp, class _Container>
inline bool operator<=(const stack<_Tp, _Container> &lhs,
                       const stack<_Tp, _Container> &rhs) {
  return lhs.c <= rhs.c;
}
template <class _Tp, class _Container>
inline bool operator>(const stack<_Tp, _Container> &lhs,
                      const stack<_Tp, _Container> &rhs) {
  return lhs.c > rhs.c;
}
template <class _Tp, class _Container>
inline bool operator>=(const stack<_Tp, _Container> &lhs,
                       const stack<_Tp, _Container> &rhs) {
  return lhs.c >= rhs.c;
}
}  // namespace ft
#endif  // INCLUDES_STACK_HPP_
