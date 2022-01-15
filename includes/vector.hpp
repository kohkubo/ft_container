#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <memory>
#include "random_access_iterator.hpp"
#include "type_traits.hpp"

namespace ft {
    template <class T, class Alloc = std::allocator<T> >
    class vector {
    public:
        typedef T                                         value_type;
        typedef Alloc                                     allocator_type;
        typedef value_type                               &reference;
        typedef const value_type                         &const_reference;
        typedef std::size_t                               size_type;
        typedef std::ptrdiff_t                            difference_type;
        typedef typename allocator_type::pointer          pointer;
        typedef typename allocator_type::const_pointer    const_pointer;
        typedef ft::random_access_iterator<pointer>       iterator;
        typedef ft::random_access_iterator<const_pointer> const_iterator;

        // =====================================================================
        // Canonical
        // =====================================================================
        // 1
        // TODO : test
        vector() : _begin(0), _end(0), _end_cap(0), _alloc(Alloc()) {}
        // 2
        // TODO : test
        explicit vector(const Alloc &alloc) : _begin(0), _end(0), _end_cap(0), _alloc(alloc) {}
        // 3
        // TODO : test
        explicit vector(size_type n, const T &value = T(), const Alloc &alloc = Alloc());
        template <class InputIterator>
        // 5 
        // TODO : implement
        vector(InputIterator first, InputIterator last, const Alloc &alloc = Alloc());
        // 6
        // TODO : test
        vector(const vector &x);
        ~vector();
        // =====================================================================
        // Element access
        // =====================================================================
        reference       at(size_type n);
        const_reference at(size_type n) const;
        reference       operator[](size_type n) { 
            // std::cout << "operator[]" << std::endl;
            // std::cout << "n : " << n << std::endl;
            // reference r = _begin[n];
            // std::cout << "r = _begin[" << n << "]" << std::endl;
            // std::cout << "r : " << r << std::endl;
            // std::cout << "&r : " << &r << std::endl;
            return _begin[n];
        }
        const_reference operator[](size_type n) const { return _begin[n]; }
        // access first element
        // 最初の要素にアクセスする
        reference       front() { return *_begin; }
        const_reference front() const { return *_begin; }
        // access last element
        // 最後の要素にアクセスする
        reference       back() { return *(_end - 1); }
        const_reference back() const { return *(_end - 1); }
        // =====================================================================
        // Iterators
        // =====================================================================
        iterator        begin() { return __make_iter(_begin); }
        const_iterator  begin() const { return __make_iter(_begin); }
        iterator        end() { return __make_iter(_end); }
        const_iterator  end() const { return __make_iter(_end); }
        // =====================================================================
        // Capacity
        // =====================================================================
        bool            empty() const { return _begin == _end; }
        size_type       size() const { return _end - _begin; }
        // TODO
        size_type       max_size() const;
        // resize storage
        // 記憶領域を確保する
        // TODO
        void            reserve(size_type n);
        // returns the number of elements that can be held in currently
        // allocated storage 現在確保されている記憶域に保持できる要素数を返す
        size_type       capacity() const { return _end_cap - _begin; }
        // =====================================================================
        // Modifiers
        // =====================================================================
        // TODO
        void            clear();
        iterator        insert(const_iterator pos, const T &value);
        iterator        insert(const_iterator pos, size_type n, const T &value);
        template <class InputIterator>
        iterator insert(const_iterator pos, InputIterator first, InputIterator last);
        iterator erase(const_iterator pos);
        iterator erase(const_iterator first, const_iterator last);
        // TODO
        void     push_back(const T &value);
        void     pop_back();
        void     resize(size_type n, const T &value = T());
        void     swap(vector &x);
    private:
        void                  __throw_length_error() { throw std::length_error("vector"); }
        void                  __throw_out_of_range() { throw std::out_of_range("vector"); }
        inline iterator       __make_iter(pointer p) { return iterator(p); }
        inline const_iterator __make_iter(const_pointer p) { return const_iterator(p); }
        void                  __construct_at_end(size_type n, const_reference x = T());
        inline void           __destroy_range(pointer first, pointer last);
        void                  __vallocate(size_type n);
        void                  __vdeallocate();
    protected:
        pointer        _begin;
        pointer        _end;
        pointer        _end_cap;
        allocator_type _alloc;
    };
}  // namespace ft
#endif
