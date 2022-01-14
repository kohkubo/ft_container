
#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {
    template <class Iterator>
    class reverse_iterator
        : public iterator<typename iterator_traits<Iterator>::iterator_category,
                          typename iterator_traits<Iterator>::value_type,
                          typename iterator_traits<Iterator>::difference_type,
                          typename iterator_traits<Iterator>::pointer,
                          typename iterator_traits<Iterator>::reference> {
    protected:
        Iterator _current;
    public:
        typedef Iterator iterator_type;
        typedef
            typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::value_type  value_type;
        typedef typename iterator_traits<Iterator>::pointer     pointer;
        typedef typename iterator_traits<Iterator>::reference   reference;

        reverse_iterator() : _current() {}
        explicit reverse_iterator(Iterator current)
            : _current(current) {
        }  // explicit
           // 暗黙の変換およびコピー初期化で使用できないことを指定します。
        reverse_iterator(const reverse_iterator &rhs)
            : _current(rhs._current) {}
        template <class Iterator2>
        reverse_iterator(const reverse_iterator<Iterator2> &rhs)
            : _current(rhs.base()) {}

        Iterator base() const { return _current; }
        Iterator operator*() const {
            Iterator tmp = _current;
            return --tmp;
        }
        pointer operator->() const {
            return addressof(operator*());
        }  // pointer operator->() const { return &(operator*()); }
        reverse_iterator &operator++() {
            --_current;
            return *this;
        }
        reverse_iterator operator++(int) {
            reverse_iterator __tmp(*this);
            --_current;
            return __tmp;
        }
        reverse_iterator &operator--() {
            ++_current;
            return *this;
        }
        reverse_iterator operator--(int) {
            reverse_iterator __tmp(*this);
            ++_current;
            return __tmp;
        }
        reverse_iterator operator+(difference_type n) const {
            return reverse_iterator(_current - n);
        }
        reverse_iterator operator-(difference_type n) const {
            return reverse_iterator(_current + n);
        }
        reverse_iterator &operator+=(difference_type n) {
            _current -= n;
            return *this;
        }
        reverse_iterator &operator-=(difference_type n) {
            _current += n;
            return *this;
        }
        reference operator[](difference_type n) const { return *(*this + n); }

        template <class Iterator_right>
        bool operator==(const reverse_iterator<Iterator_right> &rhs) const {
            return _current == rhs.base();
        }
        template <class Iterator_right>
        bool operator!=(const reverse_iterator<Iterator_right> &rhs) const {
            return _current != rhs.base();
        }
        template <class Iterator_right>
        bool operator<(const reverse_iterator<Iterator_right> &rhs) const {
            return _current > rhs.base();
        }
        template <class Iterator_right>
        bool operator>(const reverse_iterator<Iterator_right> &rhs) const {
            return _current < rhs.base();
        }
        template <class Iterator_right>
        bool operator<=(const reverse_iterator<Iterator_right> &rhs) const {
            return _current >= rhs.base();
        }
        template <class Iterator_right>
        bool operator>=(const reverse_iterator<Iterator_right> &rhs) const {
            return _current <= rhs.base();
        }
        template <class Iterator_right>
        difference_type operator-(
            const reverse_iterator<Iterator_right> &rhs) const {
            return rhs.base() - _current;
        }
    };

}  // namespace ft

#endif
