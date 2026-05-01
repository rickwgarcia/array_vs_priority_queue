#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;

class GraphMatrix {
    vector<vector<int>> adj_matrix;

public:
    GraphMatrix(int n) {
        adj_matrix = vector<vector<int>>(n, vector<int>(n, 0));
    }

    void add_edge(int u, int v, int weight) {
        adj_matrix[u][v] = weight;
        adj_matrix[v][u] = weight; // undirected
    }  
};


class GraphList {
    int V;
    vector<vector<pair<int, int>>> adj_list; // node, {neighbor, weight}

public:
    GraphList(int n) {
        V = n;
        adj_list.resize(n);
    }

    void add_edge(int u, int v, int weight) {
        adj_list[u].push_back({v, weight});
        adj_list[v].push_back({u, weight}); // undirected
    }
   
    // returns distance from source to all vertices
    vector<int> shortest_path(int src) {  
        vector<int> dist(V, INT_MAX);
        vector<bool> visited(V, false);
        
        dist[src] = 0;
        
        int u;
        while ((u = shortest_unvisited(dist, visited)) != -1) {
            visited[u] = true; // Mark visited 
     
            for (size_t i = 0; i < adj_list[u].size(); i++) {
                int v = adj_list[u][i].first; // Neighbor
                int weight = adj_list[u][i].second;
                if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
        
        return dist;  
    }  
   
private:
    // Returns node index with shortest distance, -1 if no unvisited node exists 
    int shortest_unvisited(const vector<int>& dist, const vector<bool>& visited) {
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


class GraphPriorityQueue {
    map<int, vector<pair<int, int>>> adj_list; // neighbor, weight

public:
    void add_edge(int u, int v, int weight) {
        adj_list[u].push_back({v, weight});
        adj_list[v].push_back({u, weight}); // undirected
    }

};

class PriorityQueue{
    vector<int> arr;
    int n;  

public:

    PriorityQueue(){
        n = 0;
    }
     
    void insert(int in){
       
    }
    
    int top() {
    }

    int pop(){
   
    }

private: 
        
    void heapify(int i){
        int smallest = i; 
        int left = 2*i + 1; 
        int right = 2*i + 2; 
        
        // Check if left or right are smaller 
        if(left < n && arr[left] < arr[smallest]){
            smallest = left; 
        }
        if (right < n && arr[right] < arr[smallest]){
            smallest = right; 
        }   
    
        // If new smallest
        if (smallest != i){
            swap(arr[smallest], arr[i]); 
            heapify(smallest); 
        }       
    }
}; 


