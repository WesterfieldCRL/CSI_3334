/* CSI 3334
 * Project 6 -- Network Brodcasting
 * Filename: driver-proj6.cpp
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This program reads in a list of computers and the connections between them
 * from standard input and determines the minimum cost to connect all computers
 * to a server. The program will print the minimum cost to connect all
 * computers to a server.
 */

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>
#include "arrayheap-student-proj6.h"
#include "graph-proj6.h"

using namespace std;

/**
 * main
 *
 * This function reads in a list of computers and the connections between them
 * from standard input and determines the minimum cost to connect all computers
 * to a server. The program will print the minimum cost to connect all
 * computers to a server.
 * 
 * Parameters:
 *   none
 * 
 * Return value: 0 (indicating a successful run)
 */

enum { INFINITE_COST = 1000000000 };

int main () {
    int edges = 0;
    int vertices = 0;
    vector<bool> canBeServer;
    queue<int> edgeQueue;
    map<int, string> computerToIndex;


    //read in data
    cin >> edges;
    for (int i = 0; i < edges; i++) {
        string tempInput;
        
        for (int j = 0; j < 2; j++) {
            cin >> tempInput;
            //add to map if not already in map
            bool isInMap = false;
            for (auto it = computerToIndex.begin(); it != computerToIndex.end(); it++) {
                if (it->second == tempInput) {
                    isInMap = true;
                }
            }

            if (!isInMap) {
                computerToIndex.insert(make_pair(vertices, tempInput));
                vertices++;
                if (tempInput.size() > 7 && tempInput.substr(tempInput.length()-7, 7) == "_server") {
                    canBeServer.push_back(true);
                }
                else {
                    canBeServer.push_back(false);
                }
            }


            for (auto it = computerToIndex.begin(); it != computerToIndex.end(); it++) {
                if (it->second == tempInput) {
                    edgeQueue.push(it->first);
                }
            }
        }

        int tempCost;
        cin >> tempCost;
        edgeQueue.push(tempCost);
    }

    //create graph
    Graph graph(vertices);
    //add edges to graph
    while (!edgeQueue.empty()) {
        int tempComp1 = edgeQueue.front();
        edgeQueue.pop();
        int tempComp2 = edgeQueue.front();
        edgeQueue.pop();
        int tempCost = edgeQueue.front();
        edgeQueue.pop();

        graph.addEdge(tempComp1, tempComp2, tempCost);
    }

    ArrayHeap<pair<int, string>> outputHeap; //cost, vertex

    //call dijkstra on servers
    for (int i = 0; i < vertices; i++) {
        if (canBeServer[i]) {
            vector<int> distances;
            distances = graph.dijkstra(i);
            int totalCost = 0;
            bool isTooBig = false;
            for (int j = 0; j < vertices; j++) {
                if (distances[j] >= INFINITE_COST) {
                    isTooBig = true;
                    //j = vertices;
                }
                else {
                    totalCost += distances[j];
                }
            }
            if (!isTooBig) {
                outputHeap.insert(make_pair(totalCost, computerToIndex[i]));
            }
        }
    }

    //output
    if (outputHeap.getNumItems() == 0) {
        cout << "no server can serve the whole network" << endl;
    }
    else {
        int minDelay = outputHeap.getMinItem().first;
        cout << "total delay: " << minDelay << endl;

        while (outputHeap.getNumItems() > 0 && outputHeap.getMinItem().first == minDelay) {
            cout << outputHeap.getMinItem().second << endl;
            outputHeap.removeMinItem();
        }
    }

    return 0;
}