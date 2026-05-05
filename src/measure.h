#ifndef MEASURE_H
#define MEASURE_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <sys/resource.h>

// wrapper function to measure algorithm walltime -- Avg. over 5 trials
template <typename Graph>
std::vector<int> time_shortest_path(const std::string& type, Graph& g, int src) {
    using clock = std::chrono::high_resolution_clock;
    std::vector<int> result;
    double total_us = 0.0;
    const int trials = 5;
    for (int t = 0; t < trials; ++t) {
        auto start = clock::now();
        result = g.shortest_path(src);
        auto end = clock::now();
        total_us += std::chrono::duration<double, std::micro>(end - start).count();
    }
    std::cout << type << " avg runtime over " << trials << " trials: "
              << (total_us / trials) << " us" << std::endl;
    return result;
}

// wrapper function to measure peak resident-set growth via getrusage -- Max over 5 trials
template <typename Graph>
std::vector<int> memory_shortest_path(const std::string& type, Graph& g, int src) {
    struct rusage before, after;
    std::vector<int> result;
    long max_delta = 0;
    const int trials = 5;
    for (int t = 0; t < trials; ++t) {
        getrusage(RUSAGE_SELF, &before);
        result = g.shortest_path(src);
        getrusage(RUSAGE_SELF, &after);
        long delta = after.ru_maxrss - before.ru_maxrss;
        if (delta > max_delta) max_delta = delta;
    }
#ifdef __APPLE__
    long max_kb = max_delta / 1024;  // macOS reports ru_maxrss in bytes
#else
    long max_kb = max_delta;         // Linux reports ru_maxrss in KB
#endif
    std::cout << type << " peak RSS delta over " << trials << " trials: "
              << max_kb << " KB" << std::endl;
    return result;
}

#endif // MEASURE_H
