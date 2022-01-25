// Copyright (c) 2022 kohkubo

#ifndef INCLUDES_PAIR_HPP_
#define INCLUDES_PAIR_HPP_

namespace ft {
template <class T1, class T2>
struct pair {
  typedef T1  first_type;
  typedef T2  second_type;

  first_type  first;
  second_type second;

  pair() : first(), second() {}
  pair(const first_type &x, const second_type &y) : first(x), second(y) {}
  pair(const pair &rhs) : first(rhs.first), second(rhs.second) {}
  template <class U, class V>
  pair(const pair<U, V> &rhs) : first(rhs.first), second(rhs.second) {}
  pair &operator=(const pair &rhs) {
    first  = rhs.first;
    second = rhs.second;
    return *this;
  }
  template <class U, class V>
  pair &operator=(const pair<U, V> &rhs) {
    first  = rhs.first;
    second = rhs.second;
    return *this;
  }
};

template <class T1, class T2>
pair<T1, T2> make_pair(T1 key, T2 value) {
  return pair<T1, T2>(key, value);
}
}  // namespace ft

#endif  // INCLUDES_PAIR_HPP_
