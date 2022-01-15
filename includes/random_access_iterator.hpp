#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include <exception>
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {
    template <class Iterator>
    class random_access_iterator {
    public:
        typedef Iterator iterator_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::value_type      value_type;
        typedef typename iterator_traits<Iterator>::pointer         pointer;
        typedef typename iterator_traits<Iterator>::reference       reference;
    private:
        iterator_type _iter;
    public:
        // =====================================================================
        // Canonical
        // =====================================================================
        random_access_iterator() : _iter(0) {}
        random_access_iterator(pointer p) : _iter(p) {}
        random_access_iterator &operator=(const iterator_type &rhs) {
            _iter = rhs.base();
            return *this;
        }
        ~random_access_iterator() {}
        // =====================================================================
        // base
        // =====================================================================
        iterator_type base() const { return _iter; }
        // =====================================================================
        // Operator
        // =====================================================================
        reference operator*() const { return *_iter; }
        pointer operator->() const { return reinterpret_cast<pointer>(*_iter); }
        random_access_iterator &operator++() {
            ++_iter;
            return *this;
        }
        random_access_iterator operator++(int) {
            random_access_iterator __tmp(*this);
            ++_iter;
            return __tmp;
        }
        random_access_iterator &operator--() {
            --_iter;
            return *this;
        }
        random_access_iterator operator--(int) {
            random_access_iterator __tmp(*this);
            --_iter;
            return __tmp;
        }
        random_access_iterator &operator+=(difference_type n) {
            _iter += n;
            return *this;
        }
        random_access_iterator &operator-=(difference_type n) {
            _iter -= n;
            return *this;
        }
        random_access_iterator operator+(difference_type n) const {
            random_access_iterator __tmp(*this);
            __tmp += n;
            return __tmp;
        }
        random_access_iterator operator-(difference_type n) const {
            random_access_iterator __tmp(*this);
            __tmp -= n;
            return __tmp;
        }
        reference operator[](difference_type n) const { return *(_iter + n); }
    };
    // =========================================================================
    // Operator
    // =========================================================================
    template <class Iterator>
    bool operator==(const random_access_iterator<Iterator> &lhs,
                    const random_access_iterator<Iterator> &rhs) {
        return lhs.base() == rhs.base();
    }
    template <class Iterator>
    bool operator!=(const random_access_iterator<Iterator> &lhs,
                    const random_access_iterator<Iterator> &rhs) {
        return !(lhs == rhs);
    }
    template <class Iterator>
    bool operator<(const random_access_iterator<Iterator> &lhs,
                   const random_access_iterator<Iterator> &rhs) {
        return lhs.base() < rhs.base();
    }
    template <class Iterator>
    bool operator>(const random_access_iterator<Iterator> &lhs,
                   const random_access_iterator<Iterator> &rhs) {
        return lhs.base() > rhs.base();
    }
    template <class Iterator>
    bool operator<=(const random_access_iterator<Iterator> &lhs,
                    const random_access_iterator<Iterator> &rhs) {
        return lhs.base() <= rhs.base();
    }
    template <class Iterator>
    bool operator>=(const random_access_iterator<Iterator> &lhs,
                    const random_access_iterator<Iterator> &rhs) {
        return lhs.base() >= rhs.base();
    }
}  // namespace ft

#endif
