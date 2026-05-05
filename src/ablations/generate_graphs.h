#ifndef GENERATE_GRAPHS_H
#define GENERATE_GRAPHS_H

#include <random>
#include <vector>

struct Edge {
    int u, v, w;
};

// random undirected edge list -- per-pair inclusion probability = density, weights uniform in [1, 100]
inline std::vector<Edge> generate_edges(int V, double density, std::mt19937& rng) {
    std::vector<Edge> edges;
    std::uniform_real_distribution<double> coin(0.0, 1.0);
    std::uniform_int_distribution<int> weight(1, 100);
    for (int u = 0; u < V; ++u) {
        for (int v = u + 1; v < V; ++v) {
            if (coin(rng) < density) {
                edges.push_back({u, v, weight(rng)});
            }
        }
    }
    return edges;
}

// build any Graph type from a shared edge list
template <typename Graph>
Graph build_graph(int V, const std::vector<Edge>& edges) {
    Graph g(V);
    for (const auto& e : edges) {
        g.add_edge(e.u, e.v, e.w);
    }
    return g;
}

#endif // GENERATE_GRAPHS_H
