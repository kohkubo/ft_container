#include <map>
#include <random>

#include "map.hpp"
#include "mybench.hpp"

LIB::map<int, int> g_m;
LIB::map<int, int> g_m2;

#define BM_MAP(name, func, loop)     \
  {                                  \
    ft::Stopwatch sw(name, loop);    \
    for (int i = 1; i < loop; i++) { \
      func();                        \
    }                                \
  }

void bm_map_constructor(void) { LIB::map<int, int> m; }
void bm_map_operator(void) {
  LIB::map<int, int> m;
  m = g_m;
}
void bm_map_get_allocator(void) { g_m.get_allocator(); }
void bm_map_operator_square_brackets(void) {
  for (LIB::map<int, int>::iterator it = g_m.begin(); it != g_m.end(); ++it) {
    g_m[it->first];
  }
}
void bm_map_begin(void) { g_m.begin(); }
void bm_map_end(void) { g_m.end(); }
void bm_map_rbegin(void) { g_m.rbegin(); }
void bm_map_rend(void) { g_m.rend(); }
void bm_map_empty(void) { g_m.empty(); }
void bm_map_size(void) { g_m.size(); }
void bm_map_max_size(void) { g_m.max_size(); }
void bm_map_clear(void) { g_m.clear(); }
void bm_map_swap(void) { g_m.swap(g_m2); }
void bm_map_insert(void) {
  LIB::map<int, int> m(g_m);
  for (int i = 0; i < LOOP3; i++) {
    int key = rand();
    m.insert(LIB::make_pair(key, key));
  }
}
void bm_map_erase(void) {
  LIB::map<int, int> m(g_m);
  for (int i = 0; i < LOOP3; i++) {
    int key = rand();
    m.erase(key);
  }
}
void bm_map_find(void) {
  for (int i = 0; i < LOOP3; i++) {
    int key = rand();
    g_m.find(key);
  }
}
void bm_map_count(void) {
  for (int i = 0; i < LOOP3; i++) {
    int key = rand();
    g_m.count(key);
  }
}
void bm_map_lower_bound(void) {
  for (int i = 0; i < LOOP3; i++) {
    int key = rand();
    g_m.lower_bound(key);
  }
}
void bm_map_upper_bound(void) {
  for (int i = 0; i < LOOP3; i++) {
    int key = rand();
    g_m.upper_bound(key);
  }
}
void bm_map_equal_range(void) {
  for (int i = 0; i < LOOP3; i++) {
    int key = rand();
    g_m.equal_range(key);
  }
}
void bm_map_key_comp(void) { g_m.key_comp(); }
void bm_map_value_comp(void) { g_m.value_comp(); }
void bm_map_operator_equal_to(void) {
  bool tmp = g_m == g_m2;
  (void)tmp;
}
void bm_map_operator_not_equal_to(void) {
  bool tmp = g_m != g_m2;
  (void)tmp;
}
void bm_map_operator_less(void) {
  bool tmp = g_m < g_m2;
  (void)tmp;
}
void bm_map_operator_greater(void) {
  bool tmp = g_m > g_m2;
  (void)tmp;
}
void bm_map_operator_less_equal(void) {
  bool tmp = g_m <= g_m2;
  (void)tmp;
}
void bm_map_operator_greater_equal(void) {
  bool tmp = g_m >= g_m2;
  (void)tmp;
}

void bench_map(void) {
  std::srand(time(NULL));
  for (int i = 0; i < LOOP3; i++) {
    int key = std::rand();
    g_m.insert(LIB::make_pair(key, key));
    key = std::rand();
    g_m2.insert(LIB::make_pair(key, key));
  }
  BM_MAP("map_constructor", bm_map_constructor, LOOP);
  BM_MAP("map_operator=", bm_map_operator, LOOP2);
  BM_MAP("map_get_allocator", bm_map_get_allocator, LOOP);
  BM_MAP("map_operator[]", bm_map_operator_square_brackets, LOOP2);
  BM_MAP("map_begin", bm_map_begin, LOOP);
  BM_MAP("map_end", bm_map_end, LOOP);
  BM_MAP("map_rbegin", bm_map_rbegin, LOOP);
  BM_MAP("map_rend", bm_map_rend, LOOP);
  BM_MAP("map_empty", bm_map_empty, LOOP);
  BM_MAP("map_size", bm_map_size, LOOP);
  BM_MAP("map_max_size", bm_map_max_size, LOOP);
  BM_MAP("map_clear", bm_map_clear, LOOP);
  BM_MAP("map_swap", bm_map_swap, LOOP);
  BM_MAP("map_insert", bm_map_insert, LOOP2);
  BM_MAP("map_erase", bm_map_erase, LOOP2);
  BM_MAP("map_find", bm_map_find, LOOP2);
  BM_MAP("map_count", bm_map_count, LOOP2);
  BM_MAP("map_lower_bound", bm_map_lower_bound, LOOP2);
  BM_MAP("map_upper_bound", bm_map_upper_bound, LOOP2);
  BM_MAP("map_equal_range", bm_map_equal_range, LOOP2);
  BM_MAP("map_key_comp", bm_map_key_comp, LOOP);
  BM_MAP("map_value_comp", bm_map_value_comp, LOOP);
  BM_MAP("map_operator_equal_to", bm_map_operator_equal_to, LOOP);
  BM_MAP("map_operator_not_equal_to", bm_map_operator_not_equal_to, LOOP);
  BM_MAP("map_operator_less", bm_map_operator_less, LOOP);
  BM_MAP("map_operator_greater", bm_map_operator_greater, LOOP);
  BM_MAP("map_operator_less_equal", bm_map_operator_less_equal, LOOP);
  BM_MAP("map_operator_greater_equal", bm_map_operator_greater_equal, LOOP);
}