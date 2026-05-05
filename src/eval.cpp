#include <iostream>
#include <vector>
#include "graph_list.h"
#include "graph_matrix.h"
#include "graph_priority_queue.h"
#include "measure.h"

// basic function to print out the resulting shortest path to each node from the source
void print_distances(const std::string& type, const std::vector<int>& distances) {
    std::cout << type << " shortest paths from node 0:" << std::endl;
    for (size_t i = 0; i < distances.size(); ++i) {
        std::cout << "  Node " << i << ": ";
        if (distances[i] == INT_MAX) {
            std::cout << "INF";
        } else {
            std::cout << distances[i];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    // --- Sparse Graph 1 ---
    // Vertices: {A=0, B=1, C=2, D=3, E=4, F=5}
    // Edges: (A,B,4) (A,C,2) (B,D,5) (C,D,1) (D,E,3) (E,F,2)
    int sparse1_nodes = 6;

    std::cout << "--- Sparse Graph 1: GraphList (Array Adjacency List) ---" << std::endl;
    GraphList s1_gl(sparse1_nodes);
    s1_gl.add_edge(0, 1, 4);
    s1_gl.add_edge(0, 2, 2);
    s1_gl.add_edge(1, 3, 5);
    s1_gl.add_edge(2, 3, 1);
    s1_gl.add_edge(3, 4, 3);
    s1_gl.add_edge(4, 5, 2);
    print_distances("GraphList", time_shortest_path("GraphList", s1_gl, 0));

    std::cout << "--- Sparse Graph 1: GraphPriorityQueue (Heap Adjacency List) ---" << std::endl;
    GraphPriorityQueue s1_gpq(sparse1_nodes);
    s1_gpq.add_edge(0, 1, 4);
    s1_gpq.add_edge(0, 2, 2);
    s1_gpq.add_edge(1, 3, 5);
    s1_gpq.add_edge(2, 3, 1);
    s1_gpq.add_edge(3, 4, 3);
    s1_gpq.add_edge(4, 5, 2);
    print_distances("GraphPriorityQueue", time_shortest_path("GraphPriorityQueue", s1_gpq, 0));

    // --- Sparse Graph 2 ---
    // Vertices: {1..7} mapped to {0..6}
    // Edges: (1,2,3) (1,3,6) (2,4,2) (3,5,4) (4,6,7) (5,7,1) (2,5,5)
    int sparse2_nodes = 7;

    std::cout << "--- Sparse Graph 2: GraphList (Array Adjacency List) ---" << std::endl;
    GraphList s2_gl(sparse2_nodes);
    s2_gl.add_edge(0, 1, 3);
    s2_gl.add_edge(0, 2, 6);
    s2_gl.add_edge(1, 3, 2);
    s2_gl.add_edge(2, 4, 4);
    s2_gl.add_edge(3, 5, 7);
    s2_gl.add_edge(4, 6, 1);
    s2_gl.add_edge(1, 4, 5);
    print_distances("GraphList", time_shortest_path("GraphList", s2_gl, 0));

    std::cout << "--- Sparse Graph 2: GraphPriorityQueue (Heap Adjacency List) ---" << std::endl;
    GraphPriorityQueue s2_gpq(sparse2_nodes);
    s2_gpq.add_edge(0, 1, 3);
    s2_gpq.add_edge(0, 2, 6);
    s2_gpq.add_edge(1, 3, 2);
    s2_gpq.add_edge(2, 4, 4);
    s2_gpq.add_edge(3, 5, 7);
    s2_gpq.add_edge(4, 6, 1);
    s2_gpq.add_edge(1, 4, 5);
    print_distances("GraphPriorityQueue", time_shortest_path("GraphPriorityQueue", s2_gpq, 0));

    // --- Dense Graph 1 ---
    // Vertices: {A=0, B=1, C=2, D=3, E=4}
    // Edges: (A,B,2) (A,C,5) (A,D,1) (A,E,4) (B,C,3) (B,D,2) (B,E,6) (C,D,3) (C,E,1) (D,E,2)
    int dense1_nodes = 5;

    std::cout << "--- Dense Graph 1: GraphMatrix (Array Adjacency Matrix) ---" << std::endl;
    GraphMatrix d1_gm(dense1_nodes);
    d1_gm.add_edge(0, 1, 2);
    d1_gm.add_edge(0, 2, 5);
    d1_gm.add_edge(0, 3, 1);
    d1_gm.add_edge(0, 4, 4);
    d1_gm.add_edge(1, 2, 3);
    d1_gm.add_edge(1, 3, 2);
    d1_gm.add_edge(1, 4, 6);
    d1_gm.add_edge(2, 3, 3);
    d1_gm.add_edge(2, 4, 1);
    d1_gm.add_edge(3, 4, 2);
    print_distances("GraphMatrix", time_shortest_path("GraphMatrix", d1_gm, 0));

    std::cout << "--- Dense Graph 1: GraphPriorityQueue (Heap Adjacency List) ---" << std::endl;
    GraphPriorityQueue d1_gpq(dense1_nodes);
    d1_gpq.add_edge(0, 1, 2);
    d1_gpq.add_edge(0, 2, 5);
    d1_gpq.add_edge(0, 3, 1);
    d1_gpq.add_edge(0, 4, 4);
    d1_gpq.add_edge(1, 2, 3);
    d1_gpq.add_edge(1, 3, 2);
    d1_gpq.add_edge(1, 4, 6);
    d1_gpq.add_edge(2, 3, 3);
    d1_gpq.add_edge(2, 4, 1);
    d1_gpq.add_edge(3, 4, 2);
    print_distances("GraphPriorityQueue", time_shortest_path("GraphPriorityQueue", d1_gpq, 0));

    // --- Dense Graph 2 ---
    // Vertices: {1..6} mapped to {0..5}
    // Edges: (1,2,3) (1,3,2) (1,4,6) (1,5,5) (1,6,4)
    //        (2,3,1) (2,4,2) (2,5,4) (2,6,7)
    //        (3,4,3) (3,5,6) (3,6,5)
    //        (4,5,2) (4,6,4)
    //        (5,6,1)
    int dense2_nodes = 6;

    std::cout << "--- Dense Graph 2: GraphMatrix (Array Adjacency Matrix) ---" << std::endl;
    GraphMatrix d2_gm(dense2_nodes);
    d2_gm.add_edge(0, 1, 3);
    d2_gm.add_edge(0, 2, 2);
    d2_gm.add_edge(0, 3, 6);
    d2_gm.add_edge(0, 4, 5);
    d2_gm.add_edge(0, 5, 4);
    d2_gm.add_edge(1, 2, 1);
    d2_gm.add_edge(1, 3, 2);
    d2_gm.add_edge(1, 4, 4);
    d2_gm.add_edge(1, 5, 7);
    d2_gm.add_edge(2, 3, 3);
    d2_gm.add_edge(2, 4, 6);
    d2_gm.add_edge(2, 5, 5);
    d2_gm.add_edge(3, 4, 2);
    d2_gm.add_edge(3, 5, 4);
    d2_gm.add_edge(4, 5, 1);
    print_distances("GraphMatrix", time_shortest_path("GraphMatrix", d2_gm, 0));

    std::cout << "--- Dense Graph 2: GraphPriorityQueue (Heap Adjacency List) ---" << std::endl;
    GraphPriorityQueue d2_gpq(dense2_nodes);
    d2_gpq.add_edge(0, 1, 3);
    d2_gpq.add_edge(0, 2, 2);
    d2_gpq.add_edge(0, 3, 6);
    d2_gpq.add_edge(0, 4, 5);
    d2_gpq.add_edge(0, 5, 4);
    d2_gpq.add_edge(1, 2, 1);
    d2_gpq.add_edge(1, 3, 2);
    d2_gpq.add_edge(1, 4, 4);
    d2_gpq.add_edge(1, 5, 7);
    d2_gpq.add_edge(2, 3, 3);
    d2_gpq.add_edge(2, 4, 6);
    d2_gpq.add_edge(2, 5, 5);
    d2_gpq.add_edge(3, 4, 2);
    d2_gpq.add_edge(3, 5, 4);
    d2_gpq.add_edge(4, 5, 1);
    print_distances("GraphPriorityQueue", time_shortest_path("GraphPriorityQueue", d2_gpq, 0));

    // --- Dense Graph 3 ---
    // Vertices: {0..9}, 28 edges -- comfortably above the dense
    // threshold E >= 0.5 * V(V-1)/2 = 22.5 for V=10 (max possible = 45).
    int dense3_nodes = 10;

    std::cout << "--- Dense Graph 3: GraphMatrix (Array Adjacency Matrix) ---" << std::endl;
    GraphMatrix d3_gm(dense3_nodes);
    d3_gm.add_edge(0, 1, 8);
    d3_gm.add_edge(0, 2, 6);
    d3_gm.add_edge(0, 3, 4);
    d3_gm.add_edge(0, 4, 2);
    d3_gm.add_edge(0, 5, 9);
    d3_gm.add_edge(0, 9, 1);
    d3_gm.add_edge(1, 2, 9);
    d3_gm.add_edge(1, 4, 5);
    d3_gm.add_edge(1, 5, 3);
    d3_gm.add_edge(1, 6, 1);
    d3_gm.add_edge(1, 8, 6);
    d3_gm.add_edge(2, 3, 1);
    d3_gm.add_edge(2, 5, 6);
    d3_gm.add_edge(2, 7, 2);
    d3_gm.add_edge(2, 9, 7);
    d3_gm.add_edge(3, 4, 2);
    d3_gm.add_edge(3, 6, 7);
    d3_gm.add_edge(3, 7, 5);
    d3_gm.add_edge(3, 9, 1);
    d3_gm.add_edge(4, 5, 3);
    d3_gm.add_edge(4, 7, 8);
    d3_gm.add_edge(4, 8, 6);
    d3_gm.add_edge(5, 7, 2);
    d3_gm.add_edge(5, 8, 9);
    d3_gm.add_edge(6, 7, 5);
    d3_gm.add_edge(6, 9, 1);
    d3_gm.add_edge(7, 8, 6);
    d3_gm.add_edge(8, 9, 7);
    print_distances("GraphMatrix", time_shortest_path("GraphMatrix", d3_gm, 0));

    std::cout << "--- Dense Graph 3: GraphPriorityQueue (Heap Adjacency List) ---" << std::endl;
    GraphPriorityQueue d3_gpq(dense3_nodes);
    d3_gpq.add_edge(0, 1, 8);
    d3_gpq.add_edge(0, 2, 6);
    d3_gpq.add_edge(0, 3, 4);
    d3_gpq.add_edge(0, 4, 2);
    d3_gpq.add_edge(0, 5, 9);
    d3_gpq.add_edge(0, 9, 1);
    d3_gpq.add_edge(1, 2, 9);
    d3_gpq.add_edge(1, 4, 5);
    d3_gpq.add_edge(1, 5, 3);
    d3_gpq.add_edge(1, 6, 1);
    d3_gpq.add_edge(1, 8, 6);
    d3_gpq.add_edge(2, 3, 1);
    d3_gpq.add_edge(2, 5, 6);
    d3_gpq.add_edge(2, 7, 2);
    d3_gpq.add_edge(2, 9, 7);
    d3_gpq.add_edge(3, 4, 2);
    d3_gpq.add_edge(3, 6, 7);
    d3_gpq.add_edge(3, 7, 5);
    d3_gpq.add_edge(3, 9, 1);
    d3_gpq.add_edge(4, 5, 3);
    d3_gpq.add_edge(4, 7, 8);
    d3_gpq.add_edge(4, 8, 6);
    d3_gpq.add_edge(5, 7, 2);
    d3_gpq.add_edge(5, 8, 9);
    d3_gpq.add_edge(6, 7, 5);
    d3_gpq.add_edge(6, 9, 1);
    d3_gpq.add_edge(7, 8, 6);
    d3_gpq.add_edge(8, 9, 7);
    print_distances("GraphPriorityQueue", time_shortest_path("GraphPriorityQueue", d3_gpq, 0));

    return 0;
}
