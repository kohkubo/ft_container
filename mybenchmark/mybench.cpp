#include "mybench_vector.cpp"
#include "mybench_map.cpp"
#include "mybench_set.cpp"
#include "mybench_stack.cpp"

int main(void) {
  bench_vector();
  bench_map();
  bench_set();
  bench_stack();
  return 0;
}