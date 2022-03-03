#include <stack>
#include <random>

#include "mybench.hpp"
#include "stack.hpp"

LIB::stack<int> g_stack;
LIB::stack<int> g_stack2;

#define BM_STACK(name, func, loop)  \
  {                                  \
    LIB::stack<int> st;              \
    ft::Stopwatch    sw(name, loop); \
    for (int i = 1; i < loop; i++) { \
      func                           \
    }                                \
  }

void bench_stack(void) {
  std::srand(time(NULL));
  for (int i = 0; i < LOOP3; i++) {
    g_stack.push(std::rand());
    g_stack2.push(std::rand());
  }
  BM_STACK("stack_constructor", LIB::stack<int> test;, LOOP);
  BM_STACK("stack_operator=", st = g_stack;, LOOP);
  BM_STACK("stack_top", g_stack.top();, LOOP);
  // capacity
  BM_STACK("stack_empty", g_stack.empty();, LOOP);
  BM_STACK("stack_size", g_stack.size();, LOOP);
  // modify
  BM_STACK("stack_push", g_stack.push(std::rand());, LOOP);
  BM_STACK("stack_pop", g_stack.pop();, LOOP);
  BM_STACK("stack_swap", g_stack.swap(g_stack2);, LOOP);
  // non-menber
  BM_STACK("stack_operator==", bool tmp = g_stack == g_stack2;(void)tmp;, LOOP);
  BM_STACK("stack_operator!=", bool tmp = g_stack != g_stack2;(void)tmp;, LOOP);
  BM_STACK("stack_operator<", bool tmp = g_stack < g_stack2;(void)tmp;, LOOP);
  BM_STACK("stack_operator<=", bool tmp = g_stack <= g_stack2;(void)tmp;, LOOP);
  BM_STACK("stack_operator>", bool tmp = g_stack > g_stack2;(void)tmp;, LOOP);
  BM_STACK("stack_operator>=", bool tmp = g_stack >= g_stack2;(void)tmp;, LOOP);
}