#include <benchmark/benchmark.h>

#include <iostream>
#include <map>
#include <vector>

#include "vector.hpp"

#define MAX_RANGE_SIZE (1 << 22)

static void BM_FtVectorConstructor(benchmark::State& state) {
  for (auto _ : state) ft::vector<int> v;
}
static void BM_StdVectorConstructor(benchmark::State& state) {
  for (auto _ : state) std::vector<int> v;
}
BENCHMARK(BM_FtVectorConstructor);
BENCHMARK(BM_StdVectorConstructor);

static void BM_FtVectorConstructorWithSize(benchmark::State& state) {
  for (auto _ : state) ft::vector<int> v(static_cast<int>(state.range(0)));
}
static void BM_StdVectorConstructorWithSize(benchmark::State& state) {
  for (auto _ : state) std::vector<int> v(static_cast<int>(state.range(0)));
}
BENCHMARK(BM_FtVectorConstructorWithSize)->Range(1, MAX_RANGE_SIZE);
BENCHMARK(BM_StdVectorConstructorWithSize)->Range(1, MAX_RANGE_SIZE);

static void BM_FtVectorConstructorWithSizeAndValue(benchmark::State& state) {
  for (auto _ : state) {
    ft::vector<int> v(static_cast<size_t>(state.range(0)), 100);
  }
}
static void BM_StdVectorConstructorWithSizeAndValue(benchmark::State& state) {
  for (auto _ : state)
    std::vector<int> v(static_cast<size_t>(state.range(0)), 100);
}
BENCHMARK(BM_FtVectorConstructorWithSizeAndValue)->Range(1, MAX_RANGE_SIZE);
BENCHMARK(BM_StdVectorConstructorWithSizeAndValue)->Range(1, MAX_RANGE_SIZE);

static void BM_FtVectorPushBack(benchmark::State& state) {
  ft::vector<int> v;
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) v.push_back(i);
  }
}
static void BM_StdVectorPushBack(benchmark::State& state) {
  std::vector<int> v;
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) v.push_back(i);
  }
}
BENCHMARK(BM_FtVectorPushBack)->Range(1, MAX_RANGE_SIZE);
BENCHMARK(BM_StdVectorPushBack)->Range(1, MAX_RANGE_SIZE);

static void BM_FtVectorClear(benchmark::State& state) {
  ft::vector<int> v;
  for (int i = 0; i < state.range(0); ++i) v.push_back(i);
  for (auto _ : state) v.clear();
}
static void BM_StdVectorClear(benchmark::State& state) {
  std::vector<int> v;
  for (int i = 0; i < state.range(0); ++i) v.push_back(i);
  for (auto _ : state) v.clear();
}
BENCHMARK(BM_FtVectorClear)->Range(1, MAX_RANGE_SIZE);
BENCHMARK(BM_StdVectorClear)->Range(1, MAX_RANGE_SIZE);

static void BM_FtVectorReserve(benchmark::State& state) {
  ft::vector<int> v;
  for (auto _ : state) v.reserve(static_cast<size_t>(state.range(0)));
}
static void BM_StdVectorReserve(benchmark::State& state) {
  std::vector<int> v;
  for (auto _ : state) v.reserve(static_cast<size_t>(state.range(0)));
}
BENCHMARK(BM_FtVectorReserve)->Range(1, MAX_RANGE_SIZE);
BENCHMARK(BM_StdVectorReserve)->Range(1, MAX_RANGE_SIZE);

static void BM_FtVectorInsert(benchmark::State& state) {
  ft::vector<int> v;
  for (int i = 0; i < state.range(0); ++i) v.push_back(i);
  for (auto _ : state) {
    v.insert(v.begin(), state.range(0), 100);
    v.insert(v.end(), state.range(0), 100);
  }
}
static void BM_StdVectorInsert(benchmark::State& state) {
  std::vector<int> v;
  for (int i = 0; i < state.range(0); ++i) v.push_back(i);
  for (auto _ : state) {
    v.insert(v.begin(), state.range(0), 100);
    v.insert(v.end(), state.range(0), 100);
  }
}
BENCHMARK(BM_FtVectorInsert)->Range(1, MAX_RANGE_SIZE);
BENCHMARK(BM_StdVectorInsert)->Range(1, MAX_RANGE_SIZE);

static void BM_FtVectorAssign(benchmark::State& state) {
  ft::vector<int> v;
  for (auto _ : state) {
    v.assign(static_cast<size_t>(state.range(0)), 100);
  }
}
static void BM_StdVectorAssign(benchmark::State& state) {
  std::vector<int> v;
  for (auto _ : state) {
    v.assign(static_cast<size_t>(state.range(0)), 100);
  }
}
BENCHMARK(BM_FtVectorAssign)->Range(1, MAX_RANGE_SIZE);
BENCHMARK(BM_StdVectorAssign)->Range(1, MAX_RANGE_SIZE);

BENCHMARK_MAIN();
