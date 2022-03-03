#include "mybench_vector.cpp"
#include "mybench_map.cpp"
#include "mybench_set.cpp"

int main(void) {
  bench_vector();
  bench_map();
  bench_set();
  return 0;
}