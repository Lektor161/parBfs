#pragma once

#include <cstdint>
#include <vector>
#include <functional>
#include <iostream>

const int di[]{-1, 0, 0, 1, 0, 0};
const int dj[]{0, -1, 0, 0, 1, 0};
const int dk[]{0, 0, -1, 0, 0, 1};

inline std::vector<std::vector<int>> gen_graph(int n) {
    std::vector<std::vector<int>> graph(n * n * n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                for (int p = 0; p < 6; p++) {
                    int ni = i + di[p];
                    int nj = j + dj[p];
                    int nk = k + dk[p];
                    if (ni >= 0 && nj >= 0 && nk >= 0 && ni < n && nj < n && nk < n) {
                        graph[i * n * n + j * n + k].push_back(ni * n * n + nj * n + nk);
                    }
                }
            }
        }
    }
    return graph;
}
