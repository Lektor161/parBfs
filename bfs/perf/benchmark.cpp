#include <cstdint>

#include "../src/generator.hpp"
#include "../src/bfs.hpp"
#include <benchmark/benchmark.h>

const auto graph = gen_graph(500);

static void benchmark_seq(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        std::vector<int> distance(graph.size(), -1);
        state.ResumeTiming();
        seq_bfs(0, distance, graph);
    } 
}
static void benchmark_par(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        std::vector<int> distance(graph.size(), -1);
        state.ResumeTiming();
        par_bfs(0, distance, graph);
    } 
}

BENCHMARK(benchmark_seq)->Iterations(5)->Unit(benchmark::kSecond)->UseRealTime();
BENCHMARK(benchmark_par)->Iterations(5)->Unit(benchmark::kSecond)->UseRealTime();

BENCHMARK_MAIN();