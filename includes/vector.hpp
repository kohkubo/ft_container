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
        vector()
            : _begin(0), _end(0), _end_cap(0), _alloc(allocator_type()) {}
        explicit vector(const allocator_type &a)
            : _begin(0), _end(0), _end_cap(0), _alloc(a) {}
        explicit vector(size_type n) : _alloc(allocator_type()) {
            __vallocate(n);
            __construct_at_end(n);
        }
        vector(size_type n, const value_type &value);
        template<class InputIterator>
        vector(InputIterator first, InputIterator last);
        ~vector() {
            if (_begin) {
                // std::allocator::deallocate メモリを解放する。
                //__clear();
                _alloc.deallocate(_begin, _end_cap - _begin);
            }
        }
        // =====================================================================
        // Element access
        // =====================================================================
        // access specified element with bounds checking
        // 指定された要素にアクセスする(バウンドチェック)
        reference       at(size_type n) { return _begin[n]; }
        const_reference at(size_type n) const { return _begin[n]; }
        // access specified element without bounds checking
        // 指定された要素にアクセスする(バウンドチェックなし)
        reference       operator[](size_type n) { return _begin[n]; }
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
        // returns an iterator to the beginning
        // 先頭のイテレータを返す
        iterator        begin() { return __make_iter(_begin); }
        const_iterator  begin() const { return __make_iter(_begin); }
        // returns an iterator to the end
        // 終端のイテレータを返す
        iterator        end() { return __make_iter(_end); }
        const_iterator  end() const { return __make_iter(_end); }
        // =====================================================================
        // Capacity
        // =====================================================================
        // checks whether the container is empty
        // containerが空かどうかをチェックする
        bool            empty() const { return _begin == _end; }
        // returns the number of elements in the container
        // コンテナ内の要素数を返す
        size_type       size() const { return _end - _begin; }
        // returns the maximum possible number of elements in the container
        // コンテナで許容される最大要素数を返す
        size_type       max_size() const {
            return std::min<size_type>(
                // numeric_limits
                // 算術型の様々な特性を問い合わせるクラステンプレート
                std::numeric_limits<difference_type>::max(),
                std::numeric_limits<size_type>::max());
        }
        // resize storage
        // 記憶領域を確保する
        void reserve(size_type n) {
            if (n > capacity()) {
                pointer new_begin   = _alloc.allocate(n);
                pointer new_end     = new_begin + size();
                pointer new_end_cap = new_begin + n;
                // 未初期化領域の範囲を配置newで初期化してコピー出力する
                std::uninitialized_copy(_begin, _end, new_begin);
                __destroy(_begin, _end);
                _alloc.deallocate(_begin, capacity());
                _begin   = new_begin;
                _end     = new_end;
                _end_cap = new_end_cap;
            }
        }
        // returns the number of elements that can be held in currently
        // allocated storage 現在確保されている記憶域に保持できる要素数を返す
        size_type capacity() const { return _end_cap - _begin; }
        // =====================================================================
        // Modifiers
        // =====================================================================
        // adds an element to the end
        // 最後に要素を追加する
        void      push_back(const value_type &x) {
            if (_end == _end_cap) {
                reserve(capacity() + 1);
            }
            _alloc.construct(_end, x);
            ++_end;
        }
    private:
        void __throw_length_error() { throw std::length_error("vector"); }
        void __throw_out_of_range() { throw std::out_of_range("vector"); }
        class _construct_transaction {
        public:
            explicit _construct_transaction(vector &v, size_type n)
                : _v(v), _p(v._end), _new_end(v._end + n) {}
            ~_construct_transaction() { _v._end = _p; }
            vector       &_v;
            pointer       _p;
            const_pointer _new_end;
            // TODO ここのorivate何しているか、わかっていない
        private:
            _construct_transaction(const _construct_transaction &) {
                delete this;
            };
            _construct_transaction &operator=(const _construct_transaction &) {
                delete this;
                return *this;
            };
        };
        void __construct_at_end(size_type n) {
            _construct_transaction __tx(*this, n);
            const_pointer          _new_end = __tx._new_end;
            for (pointer _p = __tx._p; _p != _new_end; ++_p) {
                // 引数を元にインスタンスを構築する。
                _alloc.construct(_p, value_type());
            }
        }
        void __construct_at_end(size_type n, const_reference x) {
            _construct_transaction __tx(*this, n);
            const_pointer          _new_end = __tx._new_end;
            for (pointer _p = __tx._p; _p != _new_end; ++_p) {
                _alloc.construct(_p, x);
            }
        }
        inline iterator       __make_iter(pointer p) { return iterator(p); }
        inline const_iterator __make_iter(const_pointer p) {
            return const_iterator(p);
        }
        // 範囲[first, last)の各要素に対してデストラクタを呼び出す。
        inline void __destroy(pointer first, pointer last) {
            for (pointer _p = first; _p != last; ++_p) {
                _alloc.destroy(_p);
            }
        }
        void __vallocate(size_type n) {
            if (n > max_size()) {
                __throw_length_error();
            }
            _begin = _end = _alloc.allocate(n);
            _end_cap      = _begin + n;
        }
    protected:
        pointer        _begin;
        pointer        _end;
        pointer        _end_cap;
        allocator_type _alloc;
    };

}  // namespace ft
#endif
