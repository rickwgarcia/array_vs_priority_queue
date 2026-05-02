#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <vector>
#include <climits>

/**
 * @brief Graph implementation using an adjacency matrix.
 */
class GraphMatrix {
    int V; // Number of vertices
    std::vector<std::vector<int>> adj_matrix; // Adjacency matrix

public:
    /**
     * @brief Constructor for GraphMatrix.
     * @param n Number of vertices.
     */
    GraphMatrix(int n) {
        V = n;
        adj_matrix = std::vector<std::vector<int>>(n, std::vector<int>(n, -1));
    }

    /**
     * @brief Adds an undirected edge to the graph.
     * @param u Source vertex.
     * @param v Destination vertex.
     * @param weight Edge weight.
     */
    void add_edge(int u, int v, int weight) {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            adj_matrix[u][v] = weight;
            adj_matrix[v][u] = weight; // undirected
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
     
            for (int v = 0; v < V; v++) {
                int weight = adj_matrix[u][v]; 
                if (weight != -1 && !visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
        
        return dist;  
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

#endif // GRAPH_MATRIX_H
