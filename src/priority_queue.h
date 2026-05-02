#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <utility>
#include <algorithm>

/**
 * @brief Simple Priority Queue implementation using a min-heap.
 */
class PriorityQueue {
    std::vector<std::pair<int, int>> arr; // Min-heap storage: {node, distance}

public:
    /**
     * @brief Inserts a node-distance pair into the priority queue.
     * @param val Pair of {node, distance}.
     */
    void insert(std::pair<int, int> val) {
        arr.push_back(val); 
        int i = arr.size() - 1;                  
        heapify_up(i); 
    }
    
    /**
     * @brief Removes and returns the element with the minimum distance.
     * @return Pair of {node, distance}.
     */
    std::pair<int, int> pop() {
        if (arr.empty()) {
            return {-1, -1}; 
        }
        std::pair<int, int> top = arr[0];
        int i = arr.size() - 1; 
        std::swap(arr[0], arr[i]); 
        arr.pop_back();
        if (!arr.empty()) {
            heapify_down(0);
        }
        return top;
    }  

    /**
     * @brief Checks if the priority queue is empty.
     * @return True if empty, false otherwise.
     */
    bool empty() {
        return arr.empty();
    }
    

private: 
    /**
     * @brief Restores the min-heap property by moving an element down.
     * @param i Index of the element to heapify down.
     */
    void heapify_down(int i) {
        int smallest = i; 
        int left = 2 * i + 1; 
        int right = 2 * i + 2; 
        int n = arr.size();
        
        if (left < n && arr[left].second < arr[smallest].second) {
            smallest = left; 
        }
        if (right < n && arr[right].second < arr[smallest].second) {
            smallest = right; 
        }   
    
        if (smallest != i) {
            std::swap(arr[smallest], arr[i]); 
            heapify_down(smallest); 
        }       
    } 
    
    /**
     * @brief Restores the min-heap property by moving an element up.
     * @param i Index of the element to heapify up.
     */
    void heapify_up(int i) {
        while (i > 0 && arr[(i - 1) / 2].second > arr[i].second) { 
            std::swap(arr[i], arr[(i - 1) / 2]);        
            i = (i - 1) / 2; 
        }
    } 
};

#endif // PRIORITY_QUEUE_H
