#include <iostream>
#include <vector>
#include "graph_list.h"
#include "graph_matrix.h"
#include "graph_priority_queue.h"

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
    int num_nodes = 5;

    std::cout << "--- GraphList Example ---" << std::endl;
    GraphList gl(num_nodes);
    gl.add_edge(0, 1, 2);
    gl.add_edge(0, 3, 6);
    gl.add_edge(1, 2, 3);
    gl.add_edge(1, 4, 8);
    gl.add_edge(2, 4, 1);
    gl.add_edge(3, 4, 4);
    print_distances("GraphList", gl.shortest_path(0));

    std::cout << "--- GraphMatrix Example ---" << std::endl;
    GraphMatrix gm(num_nodes);
    gm.add_edge(0, 1, 2);
    gm.add_edge(0, 3, 6);
    gm.add_edge(1, 2, 3);
    gm.add_edge(1, 4, 8);
    gm.add_edge(2, 4, 1);
    gm.add_edge(3, 4, 4);
    print_distances("GraphMatrix", gm.shortest_path(0));

    std::cout << "--- GraphPriorityQueue Example ---" << std::endl;
    GraphPriorityQueue gpq(num_nodes);
    gpq.add_edge(0, 1, 2);
    gpq.add_edge(0, 3, 6);
    gpq.add_edge(1, 2, 3);
    gpq.add_edge(1, 4, 8);
    gpq.add_edge(2, 4, 1);
    gpq.add_edge(3, 4, 4);
    print_distances("GraphPriorityQueue", gpq.shortest_path(0));

    return 0;
}
