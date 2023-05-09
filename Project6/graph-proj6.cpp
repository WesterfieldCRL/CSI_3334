/* CSI 3334
 * Project 6 -- Network Brodcasting
 * Filename: graph-proj6.cpp
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains the implementation of the Graph class.
 */

#include "graph-proj6.h"
#include "arrayheap-student-proj6.h"
#include <utility>
#include <vector>

#include <iostream>

using namespace std;

/**
 * Graph
 *
 * This function is the constructor for the Graph class. It initializes the
 * adjacency list to the correct size.
 * 
 * Parameters:
 *   numVertices - the number of vertices in the graph
 * 
 * Return value: none
 */

void Graph::addEdge(int from, int to, int cost) {
    adjacencyList[from].push_back(Edge(to, cost));
}

/**
 * inVertexRange
 *
 * This function checks if a vertex is in the range of the adjacency list.
 * 
 * Parameters:
 *   vertex - the vertex to check
 * 
 * Return value: true if the vertex is in the range, false otherwise
 */

vector<int> Graph::dijkstra(int source) const {
    vector<int> dist;
    vector<int> keys;
    ArrayHeap<pair<int, int>> heap; //pair of (distance, vertex)

    int tempListSize = adjacencyList.size();
    for (int i = 0; i < tempListSize; i++) {
        dist.push_back(INFINITE_COST);
        keys.push_back(-1);
    }

    dist[source] = 0;

    keys[source] = heap.insert(make_pair(0, source));

    while (heap.getNumItems() > 0) {
        //remove min item
        pair<int, int> min = heap.getMinItem(); //pair of (distance, vertex)
        heap.removeMinItem();

        int minVertex = min.second;
        int minCost = min.first;

        //relax edges
        for (auto it = adjacencyList[minVertex].begin(); it != adjacencyList[minVertex].end(); it++) {
            int newCost = minCost + it->cost;
            if (newCost < dist[it->to]) {

                dist[it->to] = newCost;

                if (keys[it->to] != -1 && heap.isOnHeap(keys[it->to])) {
                    heap.changeItemAtKey(keys[it->to], make_pair(newCost, it->to));
                }
                else {
                    keys[it->to] = heap.insert(make_pair(newCost, it->to));
                }
            }
        }
    }
    
    return dist;
}