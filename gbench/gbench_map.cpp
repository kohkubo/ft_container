#include "gbench.hpp"

static void BM_MapInsert(benchmark::State& state) {
  std::srand(std::time(0));
  USE_LIB::map<int, int> m;
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      m.insert(USE_LIB::make_pair(std::rand(), std::rand()));
    }
  }
}
BENCHMARK(BM_MapInsert)->Range(1, MAX_RANGE_SIZE);

static void BM_MapRemove(benchmark::State& state) {
  std::srand(std::time(0));
  USE_LIB::map<int, int> m;
  for (int i = 0; i < state.range(0); ++i) {
    m.insert(USE_LIB::make_pair(std::rand(), std::rand()));
  }
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      m.erase(std::rand());
    }
  }
}
BENCHMARK(BM_MapRemove)->Range(1, MAX_RANGE_SIZE);

BENCHMARK_MAIN();
