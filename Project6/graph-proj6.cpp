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

    //cout << "dijkstra called on source vertex " << source << endl;

    int tempListSize = adjacencyList.size();
    for (int i = 0; i < tempListSize; i++) {
        dist.push_back(INFINITE_COST);
        keys.push_back(-1);
    }

    dist[source] = 0;

    heap.insert(make_pair(0, source));

    while (heap.getNumItems() > 0) {
        //remove min item
        pair<int, int> min = heap.getMinItem(); //pair of (distance, vertex)
        heap.removeMinItem();

        //cout << "   pulled vertex " << min.second << " with cost " << min.first << endl;

        int minVertex = min.second;
        int minCost = min.first;

        //relax edges
        for (auto it = adjacencyList[minVertex].begin(); it != adjacencyList[minVertex].end(); it++) {
            int newCost = minCost + it->cost;
            if (newCost < dist[it->to]) {
                //cout << "found shorter path to vertex " << it->to << " via vertex " << min.second << " with cost " << newCost << endl;
                dist[it->to] = newCost;
                for (int i = 0; i < keys.size(); i++)
                {
                    //cout << "keys[" << i << "] = " << keys[i] << endl;
                }
                if (keys[it->to] != -1 && heap.isOnHeap(keys[it->to]))
                {
                    //cout << "vertex " << it->to << " already on heap with key " << keys[it->to] << ", updating cost to " << newCost << endl;
                    heap.changeItemAtKey(keys[it->to], make_pair(newCost, it->to));
                }
                else
                {
                    keys[it->to] = heap.insert(make_pair(newCost, it->to));
                    //cout << "inserted vertex " << it->to << " with cost " << newCost << ", key " << keys[it->to] << endl;
                }
            }
        }
    }

    return dist;
}