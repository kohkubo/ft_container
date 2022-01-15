#ifndef VECTOR_FUNC_HPP
#define VECTOR_FUNC_HPP

#include "vector.hpp"

namespace ft {
    // =========================================================================
    // Canonic
    // =========================================================================
    template <class T, class Alloc>
    vector<T, Alloc>::vector(size_type n, const_reference value, const Alloc &alloc)
        : _alloc(alloc) {
        if (n > max_size()) {
            __throw_length_error();
        }
        __vallocate(n);
        __construct_at_end(n, value);
    }
    template <class T, class Alloc>
    template <class InputIterator>
    vector<T, Alloc>::vector(InputIterator first, InputIterator last, const Alloc &alloc)
        : _alloc(alloc) {
        __vallocate(last - first);
        __construct_at_end(first, last);
    }
    // TODO バグっている
    template <class T, class Alloc>
    vector<T, Alloc>::vector(const vector &v) : _alloc(Alloc()) {
        __vallocate(v.size());
        __construct_at_end(v.size(), v.front());
    }
    // ~vector
    template <class T, class Alloc>
    vector<T, Alloc>::~vector() {
        if (_begin) {
            _alloc.deallocate(_begin, _end_cap - _begin);
        }
    }
    // =========================================================================
    // Element access
    // =========================================================================
    template <class T, class Alloc>
    typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type n) {
        if (n >= size()) {
            __throw_out_of_range();
        }
        return _begin[n];
    }
    template <class T, class Alloc>
    typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(size_type n) const {
        if (n >= size()) {
            __throw_out_of_range();
        }
        return _begin[n];
    }
    // =========================================================================
    // Capacity
    // =========================================================================
    // max_size()
    template <class T, class Alloc>
    typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const {
        return std::min<size_type>(std::numeric_limits<difference_type>::max(),
                                   std::numeric_limits<size_type>::max())
             / sizeof(value_type);
    }
    // reserve()
    template <class T, class Alloc>
    void vector<T, Alloc>::reserve(size_type n) {
        if (n > capacity()) {
            if (n > max_size()) {
                __throw_length_error();
            }
            pointer new_begin   = _alloc.allocate(n);
            pointer new_end     = new_begin + size();
            pointer new_end_cap = new_begin + n;
            std::uninitialized_copy(_begin, _end, new_begin);
            // TODO ダブルフリーが起きる描き方になっている。
            __destroy_range(_begin, _end);
            _alloc.deallocate(_begin, capacity());
            _begin   = new_begin;
            _end     = new_end;
            _end_cap = new_end_cap;
        }
    }
    // =========================================================================
    // private menber function
    // =========================================================================
    template <class T, class Alloc>
    void vector<T, Alloc>::__construct_at_end(size_type n, const_reference x) {
        _end = _begin + n;
        std::uninitialized_fill(_begin, _end, x);
    }
    // __destroy_range
    template <class T, class Alloc>
    inline void vector<T, Alloc>::__destroy_range(pointer first, pointer last) {
        for (; first != last; ++first) {
            _alloc.destroy(first);
        }
    }
    template <class T, class Alloc>
    void vector<T, Alloc>::__vallocate(size_type n) {
        if (n > max_size()) {
            __throw_length_error();
        }
        _begin   = _alloc.allocate(n);
        _end     = _begin;
        _end_cap = _begin + n;
    }
    template <class T, class Alloc>
    void vector<T, Alloc>::__vdeallocate() {
        if (_begin) {
            _alloc.deallocate(_begin, _end_cap - _begin);
            _begin   = 0;
            _end     = 0;
            _end_cap = 0;
        }
    }
    // =========================================================================
    // Modifiers
    // =========================================================================
    // clear()
    template <class T, class Alloc>
    void vector<T, Alloc>::clear() {
        __destroy_range(_begin, _end);
        _end = _begin;
    }
    // push_back()
    template <class T, class Alloc>
    void vector<T, Alloc>::push_back(const_reference x) {
        if (_end == _end_cap) {
            reserve(capacity() + 1);
        }
        _alloc.construct(_end, x);
        ++_end;
    }
}  // namespace ft

#endif
