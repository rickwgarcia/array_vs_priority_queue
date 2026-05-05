#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <utility>
#include "../graph_list.h"
#include "../graph_matrix.h"
#include "../graph_priority_queue.h"
#include "generate_graphs.h"

struct Measurement {
    double avg_us;
    long graph_kb;
    long algo_kb;
    long total_kb;
};

template <typename Graph>
Measurement measure(Graph& g, int src, int trials) {
    using clock = std::chrono::high_resolution_clock;
    double total = 0.0;
    for (int t = 0; t < trials; ++t) {
        auto start = clock::now();
        auto result = g.shortest_path(src);
        auto end = clock::now();
        total += std::chrono::duration<double, std::micro>(end - start).count();
    }

    long graph_bytes = static_cast<long>(g.memory_footprint());
    long algo_bytes = static_cast<long>(g.algorithm_footprint());
    long graph_kb = graph_bytes / 1024;
    long algo_kb = algo_bytes / 1024;
    long total_kb = (graph_bytes + algo_bytes) / 1024;

    return {total / trials, graph_kb, algo_kb, total_kb};
}

int main() {
    const std::vector<int> sizes = {100, 500, 1000, 2000, 5000};
    const std::vector<std::pair<std::string, double>> densities = {
        {"sparse", 0.06}, {"dense", 0.50}
    };
    const int trials = 5;
    const int seed = 42;
    const int src = 0;

    std::ofstream csv("results.csv");
    csv << "V,density_label,density,edges,implementation,avg_us,graph_kb,algo_kb,total_kb\n";

    std::ofstream stats_csv("graph_stats.csv");
    stats_csv << "V,density_label,density,nodes,edges\n";

    std::mt19937 rng(seed);

    for (int V : sizes) {
        for (const auto& dp : densities) {
            const std::string& label = dp.first;
            double p = dp.second;

            auto edges = generate_edges(V, p, rng);
            int E = static_cast<int>(edges.size());

            stats_csv << V << "," << label << "," << p << "," << V << "," << E << "\n";

            std::cerr << "V=" << V << " density=" << label
                      << " (p=" << p << ") E=" << E << std::endl;

            auto write_row = [&](const std::string& impl, const Measurement& m) {
                csv << V << "," << label << "," << p << "," << E
                    << "," << impl << "," << m.avg_us
                    << "," << m.graph_kb << "," << m.algo_kb << "," << m.total_kb << "\n";
                csv.flush();
            };

            {
                auto g = build_graph<GraphList>(V, edges);
                write_row("GraphList", measure(g, src, trials));
            }
            {
                auto g = build_graph<GraphMatrix>(V, edges);
                write_row("GraphMatrix", measure(g, src, trials));
            }
            {
                auto g = build_graph<GraphPriorityQueue>(V, edges);
                write_row("GraphPriorityQueue", measure(g, src, trials));
            }
        }
    }

    csv.close();
    stats_csv.close();
    std::cerr << "wrote results.csv" << std::endl;
    std::cerr << "wrote graph_stats.csv" << std::endl;
    return 0;
}
