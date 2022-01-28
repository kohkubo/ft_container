#ifndef INCLUDES_POINTER_TRAITS_HPP_
#define INCLUDES_POINTER_TRAITS_HPP_

#include <cstddef>

namespace ft {
template <class Ptr>
struct pointer_traits {
  typedef typename Ptr::element_type    element_type;
  typedef typename Ptr::difference_type difference_type;
  typedef typename Ptr::pointer         pointer;
};

template <class _Tp>
struct pointer_traits<_Tp*> {
  typedef _Tp       element_type;
  typedef ptrdiff_t difference_type;
  typedef _Tp*      pointer;
};

}  // namespace ft

#endif  // INCLUDES_POINTER_TRAITS_HPP_
