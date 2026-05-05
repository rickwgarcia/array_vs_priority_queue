#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <utility>
#include <sys/resource.h>
#include "../graph_list.h"
#include "../graph_matrix.h"
#include "../graph_priority_queue.h"
#include "generate_graphs.h"

struct Measurement {
    double avg_us;
    long peak_kb;
};

template <typename Graph>
Measurement measure(Graph& g, int src, int trials) {
    using clock = std::chrono::high_resolution_clock;
    double total = 0.0;
    long max_delta = 0;
    struct rusage before, after;
    for (int t = 0; t < trials; ++t) {
        getrusage(RUSAGE_SELF, &before);
        auto start = clock::now();
        auto result = g.shortest_path(src);
        auto end = clock::now();
        getrusage(RUSAGE_SELF, &after);
        total += std::chrono::duration<double, std::micro>(end - start).count();
        long delta = after.ru_maxrss - before.ru_maxrss;
        if (delta > max_delta) max_delta = delta;
    }
#ifdef __APPLE__
    long peak_kb = max_delta / 1024;  // macOS reports ru_maxrss in bytes
#else
    long peak_kb = max_delta;         // Linux reports ru_maxrss in KB
#endif
    return {total / trials, peak_kb};
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
    csv << "V,density_label,density,edges,implementation,avg_us,peak_kb\n";

    std::mt19937 rng(seed);

    for (int V : sizes) {
        for (const auto& dp : densities) {
            const std::string& label = dp.first;
            double p = dp.second;

            auto edges = generate_edges(V, p, rng);
            int E = static_cast<int>(edges.size());

            std::cerr << "V=" << V << " density=" << label
                      << " (p=" << p << ") E=" << E << std::endl;

            auto write_row = [&](const std::string& impl, const Measurement& m) {
                csv << V << "," << label << "," << p << "," << E
                    << "," << impl << "," << m.avg_us << "," << m.peak_kb << "\n";
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
    std::cerr << "wrote results.csv" << std::endl;
    return 0;
}
