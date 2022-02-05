#include <benchmark/benchmark.h>

#include <vector>
#include <iostream>
#include "vector.hpp"
#include <map>

static void BM_FtVectorPushBack(benchmark::State& state) {
  ft::vector<int> v;

  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      v.push_back(i);
    }
  }
}
BENCHMARK(BM_FtVectorPushBack)->Range(1, 1 << 22);

static void BM_StdVectorPushBack(benchmark::State& state) {
  std::vector<int> v;
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      v.push_back(i);
    }
  }
}
BENCHMARK(BM_StdVectorPushBack)->Range(1, 1 << 22);

// static void BM_StdMap(benchmark::State& state) {
//   std::map<int, int> v;
//   int i = 0;
//     for (int j = 0; j < state.range(0); ++j) {
//       v.insert(std::make_pair(i, i));
//       ++i;
//     }
//   for (auto _ : state) {
//     for (int j = 0; j < state.range(0); ++j) {
//       v.erase(i);
//       --i;
//     }
//   }
// }
// BENCHMARK(BM_StdMap)->Range(1, 1 << 22);

// static void BM_DenseRangeStd(benchmark::State& state) {
//   for(auto _ : state) {
//     std::vector<int> v(state.range(0), state.range(0));
//     benchmark::DoNotOptimize(v.begin().base());
//     benchmark::ClobberMemory();
//   }
// }
// BENCHMARK(BM_DenseRangeStd)->DenseRange(0, 1024, 128);

// static void BM_DenseRangeFt(benchmark::State& state) {
//   for(auto _ : state) {
//     ft::vector<int> v(state.range(0), state.range(0));
//     benchmark::DoNotOptimize(v.begin().base());
//     benchmark::ClobberMemory();
//   }
// }
// BENCHMARK(BM_DenseRangeFt)->DenseRange(0, 1024, 128);

BENCHMARK_MAIN();
