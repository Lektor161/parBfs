#pragma once

#include <atomic>
#include <deque>
#include <queue>
#include <limits>
#include <cstddef>
#include <vector>
#include "generator.hpp"
#include <parlay/primitives.h>
#include <parlay/parallel.h>

inline void seq_bfs(int start, std::vector<int>& distance, const std::vector<std::vector<int>>& edges) {
    std::queue<int> q;
    q.push(start);
    distance[start] = 0;
    while (!q.empty()) {
        int ver = q.front();
        q.pop();
        for (int to: edges[ver]) {
            if (distance[to] == -1) {
                distance[to] = distance[ver] + 1;
                q.push(to);
            }
        }
    }
}

inline void par_bfs(int start, std::vector<int>& distance, const std::vector<std::vector<int>>& edges) {
    parlay::sequence<std::atomic_bool> used(distance.size());
    used[start].store(true);
    distance[start] = 0;

    parlay::sequence<int> front(1, start);

    int frontier_number = 0;
    while (!front.empty()) {
       front = flatten(map(front, [&] (int u) { return edges[u]; }));

       front = filter(front, [&used](int i) {
           bool expected = false;
           return used[i].compare_exchange_strong(expected, true);
       });

        ++frontier_number;
        map(front, [&] (int u) {
            distance[u] = frontier_number;
            return 0;
        });
    }
}