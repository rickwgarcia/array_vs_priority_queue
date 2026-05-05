#ifndef GRAPH_PRIORITY_QUEUE_H
#define GRAPH_PRIORITY_QUEUE_H

#include <vector>
#include <utility>
#include <climits>
#include "priority_queue.h"

/**
 * @brief Graph implementation using an adjacency list and a custom priority queue for Dijkstra's algorithm.
 */
class GraphPriorityQueue {
    int V; // Number of vertices
    std::vector<std::vector<std::pair<int, int>>> adj_list; // Adjacency list: node -> {neighbor, weight}
    size_t peak_pq_size = 0; // Measured PQ high-water mark from the last shortest_path() call.

public:
    /**
     * @brief Constructor for GraphPriorityQueue.
     * @param n Number of vertices.
     */
    GraphPriorityQueue(int n) {
        V = n;
        adj_list.resize(n);
    }

    /**
     * @brief Computes the shortest path from a source vertex using Dijkstra's algorithm with a priority queue.
     * @param src Source vertex.
     * @return Vector of distances from src to all other vertices.
     */
    std::vector<int> shortest_path(int src) {
        std::vector<int> dist(V, INT_MAX);
        PriorityQueue pq;
        peak_pq_size = 0;

        dist[src] = 0;
        pq.insert({src, 0});
        peak_pq_size = std::max(peak_pq_size, pq.size());

        while (!pq.empty()) {
            std::pair<int, int> top = pq.pop();
            int u = top.first;
            int d = top.second;

            for (size_t i = 0; i < adj_list[u].size(); i++) {
                int v = adj_list[u][i].first;
                int weight = adj_list[u][i].second;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.insert({v, dist[v]});
                    peak_pq_size = std::max(peak_pq_size, pq.size());
                }
            }
        }

        return dist;
    }
    
    /**
     * @brief Adds an undirected edge to the graph.
     * @param u Source vertex.
     * @param v Destination vertex.
     * @param weight Edge weight.
     */
    void add_edge(int u, int v, int weight) {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            adj_list[u].push_back({v, weight});
            adj_list[v].push_back({u, weight}); // undirected
        }
    }

    // Bytes held by the persistent graph storage (this object + adj_list backing).
    size_t memory_footprint() const {
        size_t bytes = sizeof(*this);
        bytes += adj_list.capacity() * sizeof(adj_list[0]);
        for (const auto& row : adj_list)
            bytes += row.capacity() * sizeof(row[0]);
        return bytes;
    }

    // Peak working-set bytes during the last shortest_path() call: dist + measured PQ peak.
    size_t algorithm_footprint() const {
        return V * sizeof(int) + peak_pq_size * sizeof(std::pair<int, int>);
    }

};

#endif // GRAPH_PRIORITY_QUEUE_H
