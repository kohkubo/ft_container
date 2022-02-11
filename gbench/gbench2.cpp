#include <benchmark/benchmark.h>

#include <iostream>
#include <map>
#include <vector>
#include <random>
#include "pair.hpp"
#include "map.hpp"

#include "vector.hpp"

#define MAX_RANGE_SIZE (1 << 22)
#ifndef USE_LIB
# define USE_LIB ft
#endif

static void BM_VectorConstructor(benchmark::State& state) {
  for (auto _ : state) USE_LIB::vector<int> v;
}
BENCHMARK(BM_VectorConstructor);

static void BM_VectorConstructorWithSize(benchmark::State& state) {
  for (auto _ : state) USE_LIB::vector<int> v(static_cast<int>(state.range(0)));
}
BENCHMARK(BM_VectorConstructorWithSize)->Range(1, MAX_RANGE_SIZE);

static void BM_VectorConstructorWithSizeAndValue(benchmark::State& state) {
  for (auto _ : state) {
    USE_LIB::vector<int> v(static_cast<size_t>(state.range(0)), 100);
  }
}
BENCHMARK(BM_VectorConstructorWithSizeAndValue)->Range(1, MAX_RANGE_SIZE);

static void BM_VectorPushBack(benchmark::State& state) {
  USE_LIB::vector<int> v;
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) v.push_back(i);
  }
}
BENCHMARK(BM_VectorPushBack)->Range(1, MAX_RANGE_SIZE);

static void BM_VectorClear(benchmark::State& state) {
  USE_LIB::vector<int> v;
  for (int i = 0; i < state.range(0); ++i) v.push_back(i);
  for (auto _ : state) v.clear();
}
BENCHMARK(BM_VectorClear)->Range(1, MAX_RANGE_SIZE);

static void BM_VectorReserve(benchmark::State& state) {
  USE_LIB::vector<int> v;
  for (auto _ : state) v.reserve(static_cast<size_t>(state.range(0)));
}
BENCHMARK(BM_VectorReserve)->Range(1, MAX_RANGE_SIZE);

static void BM_VectorInsert(benchmark::State& state) {
  USE_LIB::vector<int> v;
  for (int i = 0; i < state.range(0); ++i) v.push_back(i);
  for (auto _ : state) {
    v.insert(v.begin(), state.range(0), 100);
    v.insert(v.end(), state.range(0), 100);
  }
}
BENCHMARK(BM_VectorInsert)->Range(1, MAX_RANGE_SIZE);

static void BM_VectorAssign(benchmark::State& state) {
  USE_LIB::vector<int> v;
  for (auto _ : state) {
    v.assign(static_cast<size_t>(state.range(0)), 100);
  }
}
BENCHMARK(BM_VectorAssign)->Range(1, MAX_RANGE_SIZE);


BENCHMARK_MAIN();
