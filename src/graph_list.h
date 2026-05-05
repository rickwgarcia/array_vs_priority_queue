#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include <vector>
#include <utility>
#include <climits>

/**
 * @brief Graph implementation using an adjacency list.
 */
class GraphList {
    int V; // Number of vertices
    std::vector<std::vector<std::pair<int, int>>> adj_list; // Adjacency list: node -> {neighbor, weight}

public:
    /**
     * @brief Constructor for GraphList.
     * @param n Number of vertices.
     */
    GraphList(int n) {
        V = n;
        adj_list.resize(n);
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
   
    /**
     * @brief Computes the shortest path from a source vertex using Dijkstra's algorithm.
     * @param src Source vertex.
     * @return Vector of distances from src to all other vertices.
     */

    std::vector<int> shortest_path(int src) {
        std::vector<int> dist(V, INT_MAX);
        std::vector<bool> visited(V, false);
        
        dist[src] = 0;
        
        int u;
        while ((u = shortest_unvisited(dist, visited)) != -1) {
            visited[u] = true; // Mark visited 
     
            for (size_t i = 0; i < adj_list[u].size(); i++) {
                int v = adj_list[u][i].first; 
                int weight = adj_list[u][i].second;
                if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
        
        return dist;  
    }  

    // Bytes held by the persistent graph storage (this object + adj_list backing).
    size_t memory_footprint() const {
        size_t bytes = sizeof(*this);
        bytes += adj_list.capacity() * sizeof(adj_list[0]);
        for (const auto& row : adj_list)
            bytes += row.capacity() * sizeof(row[0]);
        return bytes;
    }

    // Peak working-set bytes added by shortest_path: dist + visited.
    size_t algorithm_footprint() const {
        return V * sizeof(int) + V * sizeof(bool);
    }


private:
    /**
     * @brief Finds the unvisited vertex with the minimum distance.
     * @param dist Vector of distances.
     * @param visited Vector of visited statuses.
     * @return Index of the vertex with minimum distance.
     */
    int shortest_unvisited(const std::vector<int>& dist, const std::vector<bool>& visited) {
        int min_node = -1; 
        int min_val = INT_MAX;  
        for (int i = 0; i < V; i++) {
            if (!visited[i] && dist[i] < min_val) {
                min_node = i; 
                min_val = dist[i]; 
            }
        }
        return min_node;
    } 
};

#endif // GRAPH_LIST_H
