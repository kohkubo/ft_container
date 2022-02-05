#include <benchmark/benchmark.h>

#include <vector>

#include "vector.hpp"

static void BM_FtVector(benchmark::State& state) {
  ft::vector<int> v;
  for (auto _ : state) {
    v.push_back(1);
  }
}
BENCHMARK(BM_FtVector)->Range(1, 1 << 10);

static void BM_StdVector(benchmark::State& state) {
  std::vector<int> v;
  for (auto _ : state) {
    v.push_back(1);
  }
}
BENCHMARK(BM_StdVector)->Range(1, 1 << 10);

BENCHMARK_MAIN();
