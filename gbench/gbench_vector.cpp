#include "gbench.hpp"

static void BM_FT_VectorConstructor(benchmark::State& state) {
  for (auto _ : state) {
    ft::vector<int> v;
  }
}
BENCHMARK(BM_FT_VectorConstructor);

static void BM_STD_VectorConstructor(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<int> v;
  }
}
BENCHMARK(BM_STD_VectorConstructor);

static void BM_FT_VectorConstructorWithSize(benchmark::State& state) {
  for (auto _ : state) {
    ft::vector<int> v(static_cast<int>(state.range(0)));
  }
}
BENCHMARK(BM_FT_VectorConstructorWithSize)->Range(1, MAX_RANGE_SIZE);

static void BM_STD_VectorConstructorWithSize(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<int> v(static_cast<int>(state.range(0)));
  }
}
BENCHMARK(BM_STD_VectorConstructorWithSize)->Range(1, MAX_RANGE_SIZE);

static void BM_FT_VectorConstructorWithSizeAndValue(benchmark::State& state) {
  for (auto _ : state) {
    ft::vector<int> v(static_cast<size_t>(state.range(0)), 100);
  }
}
BENCHMARK(BM_FT_VectorConstructorWithSizeAndValue)->Range(1, MAX_RANGE_SIZE);

static void BM_FT_VectorPushBack(benchmark::State& state) {
  ft::vector<int> v;
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) v.push_back(i);
  }
}
BENCHMARK(BM_FT_VectorPushBack)->Range(1, MAX_RANGE_SIZE);

static void BM_FT_VectorClear(benchmark::State& state) {
  ft::vector<int> v;
  for (int i = 0; i < state.range(0); ++i) v.push_back(i);
  for (auto _ : state) v.clear();
}
BENCHMARK(BM_FT_VectorClear)->Range(1, MAX_RANGE_SIZE);

static void BM_FT_VectorReserve(benchmark::State& state) {
  ft::vector<int> v;
  for (auto _ : state) v.reserve(static_cast<size_t>(state.range(0)));
}
BENCHMARK(BM_FT_VectorReserve)->Range(1, MAX_RANGE_SIZE);

static void BM_FT_VectorInsert(benchmark::State& state) {
  ft::vector<int> v;
  for (int i = 0; i < state.range(0); ++i) v.push_back(i);
  for (auto _ : state) {
    v.insert(v.begin(), state.range(0), 100);
    v.insert(v.end(), state.range(0), 100);
  }
}
BENCHMARK(BM_FT_VectorInsert)->Range(1, MAX_RANGE_SIZE);

static void BM_FT_VectorAssign(benchmark::State& state) {
  ft::vector<int> v;
  for (auto _ : state) {
    v.assign(static_cast<size_t>(state.range(0)), 100);
  }
}
BENCHMARK(BM_FT_VectorAssign)->Range(1, MAX_RANGE_SIZE);

BENCHMARK_MAIN();
