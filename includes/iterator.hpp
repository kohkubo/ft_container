#ifndef ITERATOR_HPP
#define ITERATOR_HPP

typedef long int ptrdiff_t;
namespace ft {
    // trait 特性、特色、特徴
    // std::iterator_traits は LegacyIterator
    // 型の性質への統一されたインタフェースを提供する型特性クラスです。
    // これによりアルゴリズムをイテレータの観点のみで実装することが可能となります。
    template <class Iterator>
    class iterator_traits {
    public:
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
    };

    template <class T>
    class iterator_traits<T *> {
    public:
        typedef ptrdiff_t difference_type;
        typedef T         value_type;
        typedef T        *pointer;
        typedef T        &reference;
    };
    template <class T>
    class iterator_traits<const T *> {
    public:
        typedef ptrdiff_t difference_type;
        typedef T         value_type;
        typedef const T  *pointer;
        typedef const T  &reference;
    };

    // std::iteratorの再実装
    template <class Category,
              class T,
              class Distance  = ptrdiff_t,
              class Pointer   = T *,
              class Reference = T &>
    class iterator {
    public:
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };



}  // namespace ft

#endif
