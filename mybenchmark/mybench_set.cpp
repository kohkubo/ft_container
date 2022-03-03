#include <random>
#include <set>

#include "mybench.hpp"
#include "set.hpp"

LIB::set<int> g_s;
LIB::set<int> g_s2;

#define BM_SET(name, func, loop)     \
  {                                  \
    LIB::set<int> s;                 \
    ft::Stopwatch sw(name, loop);    \
    for (int i = 1; i < loop; i++) { \
      func                           \
    }                                \
  }

void bench_set(void) {
  std::srand(std::time(NULL));
  for (int i = 0; i < LOOP3; i++) {
    int key = rand();
    g_s.insert(key);
    key = rand();
    g_s2.insert(key);
  }
  BM_SET("set_constructor", LIB::set<int> test;, LOOP);
  BM_SET("set_operator=", s = g_s;, LOOP2);
  BM_SET("set_get_allocator", g_s.get_allocator();, LOOP);
  // itertor
  BM_SET("set_begin", g_s.begin();, LOOP);
  BM_SET("set_end", g_s.end();, LOOP);
  BM_SET("set_rbegin", g_s.rbegin();, LOOP);
  BM_SET("set_rend", g_s.rend();, LOOP);
  // capacity
  BM_SET("set_empty", g_s.empty();, LOOP);
  BM_SET("set_size", g_s.size();, LOOP);
  BM_SET("set_max_size", g_s.max_size();, LOOP);
  // modifiers
  BM_SET("set_clear", LIB::set<int> s2(g_s); s2.clear();, LOOP2);
  BM_SET("set_insert", s.insert(i);, LOOP2);
  BM_SET("set_erase", LIB::set<int> s2(g_s); s2.erase(s2.begin());, LOOP2);
  BM_SET("set_swap", g_s.swap(g_s2);, LOOP);
  // non-member
  BM_SET("set_swap", swap(s, s);, LOOP);
  BM_SET("set_operator==", bool tmp = g_s == g_s2; (void)tmp;, LOOP);
  BM_SET("set_operator!=", bool tmp = g_s != g_s2; (void)tmp;, LOOP);
  BM_SET("set_operator<", bool tmp = g_s < g_s2; (void)tmp;, LOOP);
  BM_SET("set_operator<=", bool tmp = g_s <= g_s2; (void)tmp;, LOOP);
  BM_SET("set_operator>", bool tmp = g_s > g_s2; (void)tmp;, LOOP);
  BM_SET("set_operator>=", bool tmp = g_s >= g_s2; (void)tmp;, LOOP);
}
