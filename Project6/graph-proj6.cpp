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
    if (inVertexRange(from) && inVertexRange(to)) {
        adjacencyList[from].push_back(Edge(to, cost));
    }
    else {
        cout << "Error: Vertex out of range" << endl;
    }
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
    ArrayHeap<pair<int, int>> heap; //pair of (distance, vertex)

    for (int i = 0; i < adjacencyList.size(); i++) {
        dist.push_back(INFINITE_COST);
    }

    dist[source] = 0;

    heap.insert(make_pair(0, source));

    while (heap.getNumItems() > 0) {
        //remove min item
        pair<int, int> min = heap.getMinItem();
        heap.removeMinItem();

        int minVertex = min.second;
        int minCost = min.first;

        //relax edges
        for (auto it = adjacencyList[minVertex].begin(); it != adjacencyList[minVertex].end(); it++) {
            int newCost = minCost + it->cost;
            if (newCost < dist[it->to]) {
                dist[it->to] = newCost;
                heap.insert(make_pair(newCost, it->to));
            }
        }
    }

    return dist;
}