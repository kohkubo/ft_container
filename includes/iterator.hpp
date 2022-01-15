#ifndef ITERATOR_HPP
#define ITERATOR_HPP

typedef long int ptrdiff_t;
namespace ft {
    template <class Iterator>
    struct iterator_traits {
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
    };

    template <class T>
    struct iterator_traits<T *> {
        typedef ptrdiff_t difference_type;
        typedef T         value_type;
        typedef T        *pointer;
        typedef T        &reference;
    };
    template <class T>
    struct iterator_traits<const T *> {
        typedef ptrdiff_t difference_type;
        typedef T         value_type;
        typedef const T  *pointer;
        typedef const T  &reference;
    };
}  // namespace ft

#endif
