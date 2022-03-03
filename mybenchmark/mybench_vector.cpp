#include <vector>

#include "mybench.hpp"
#include "vector.hpp"

#define BM_VECTOR(name, func, loop)  \
  {                                  \
    LIB::vector<int> v;              \
    LIB::vector<int> v2(loop);       \
    ft::Stopwatch    sw(name, loop); \
    for (int i = 1; i < loop; i++) { \
      func                           \
    }                                \
  }

void bench_vector(void) {
  BM_VECTOR("vector_constructor", LIB::vector<int> test;, LOOP);
  BM_VECTOR("vector_operator=", v = v;, LOOP);
  BM_VECTOR("vector_assign", v.assign(i, 0); v.clear();, LOOP2);
  BM_VECTOR("vector_get_allocator", v.get_allocator();, LOOP);
  BM_VECTOR("vector_at", v2.at(i - 1);, LOOP);
  BM_VECTOR("vector_operator[]", v2[i - 1];, LOOP);
  BM_VECTOR("vector_front", v2.front();, LOOP);
  BM_VECTOR("vector_back", v2.back();, LOOP);
  BM_VECTOR("vector_begin", v2.begin();, LOOP);
  BM_VECTOR("vector_end", v2.end();, LOOP);
  BM_VECTOR("vector_rbegin", v2.rbegin();, LOOP);
  BM_VECTOR("vector_rend", v2.rend();, LOOP);
  BM_VECTOR("vector_capacity", v2.capacity();, LOOP);
  BM_VECTOR("vector_max_size", v2.max_size();, LOOP);
  BM_VECTOR("vector_size", v2.size();, LOOP);
  BM_VECTOR("vector_empty", v2.empty();, LOOP);
  BM_VECTOR("vector_reserve", v.reserve(LOOP);, LOOP);
  BM_VECTOR("vector_push_back", v.push_back(0);, LOOP);
  BM_VECTOR("vector_pop_back", v2.pop_back();, LOOP);
  BM_VECTOR("vector_insert", v.insert(v.begin(), 0);, LOOP2);
  BM_VECTOR("vector_erase", v2.erase(v2.begin());, LOOP2);
  BM_VECTOR("vector_clear", v2.clear();, LOOP2);
  BM_VECTOR("vector_resize", v.resize(LOOP);, LOOP2);
  BM_VECTOR("vector_swap", v.swap(v2);, LOOP);
  BM_VECTOR("vector_swap", swap(v, v2);, LOOP);
  BM_VECTOR("vector_operator==", bool tmp = v == v2; (void)tmp;, LOOP);
  BM_VECTOR("vector_operator!=", bool tmp = v != v2; (void)tmp;, LOOP);
  BM_VECTOR("vector_operator<", bool tmp = v < v2; (void)tmp;, LOOP);
  BM_VECTOR("vector_operator<=", bool tmp = v <= v2; (void)tmp;, LOOP);
  BM_VECTOR("vector_operator>", bool tmp = v > v2; (void)tmp;, LOOP);
  BM_VECTOR("vector_operator>=", bool tmp = v >= v2; (void)tmp;, LOOP);
}