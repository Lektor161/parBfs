#include <gtest/gtest.h>

#include "../src/generator.hpp"
#include "../src/bfs.hpp"

TEST(amo, gus) {    
    const auto graph = gen_graph(200);
    std::vector<int> distance_seq(graph.size(), -1);
    std::vector<int> distance_par(graph.size(), -1);

    seq_bfs(0, distance_seq, graph);
    par_bfs(0, distance_par, graph);

    ASSERT_EQ(distance_seq, distance_par);
}