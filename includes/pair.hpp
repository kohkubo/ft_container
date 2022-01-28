// Copyright (c) 2022 kohkubo

#ifndef INCLUDES_PAIR_HPP_
#define INCLUDES_PAIR_HPP_

namespace ft {
template <class _T1, class _T2>
struct pair {
  typedef _T1 first_type;
  typedef _T2 second_type;
  _T1         first;
  _T2         second;

  pair() : first(), second() {}
  pair(_T1 const& __t1, _T2 const& __t2) : first(__t1), second(__t2) {}
  template <class _U1, class _U2>
  pair(const pair<_U1, _U2>& __p) : first(__p.first), second(__p.second) {}

  pair& operator=(pair const& __p) {
    first  = __p.first;
    second = __p.second;
    return *this;
  }
};

template <class _T1, class _T2>
inline bool operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return __x.first == __y.first && __x.second == __y.second;
}

template <class _T1, class _T2>
inline bool operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return !(__x == __y);
}

template <class _T1, class _T2>
inline bool operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return __x.first < __y.first ||
         (!(__y.first < __x.first) && __x.second < __y.second);
}

template <class _T1, class _T2>
inline bool operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return __y < __x;
}

template <class _T1, class _T2>
inline bool operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return !(__x < __y);
}

template <class _T1, class _T2>
inline bool operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return !(__y < __x);
}

template <class T1, class T2>
pair<T1, T2> make_pair(T1 key, T2 value) {
  return pair<T1, T2>(key, value);
}
}  // namespace ft

#endif  // INCLUDES_PAIR_HPP_
