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

int main() {
    enum { INFINITE_COST = 1000000000 };
    ArrayHeap<pair<int, int>> serverCosts; //cost, vertex
    map<string, int> computerToIndex;
    //vector<bool> canBeServer;
    //vector<string> computers1;
    //vector<string> computers2;
    //vector<int> costs;
    
    string computer1;
    string computer2;
    int cost;
    string temp;
    int totalCost;
    //int tempDistances;
    bool isTooBig;
    

    int edges;
    int vertices = 0;
    cin >> edges;

    int costs[edges];
    bool servers[edges];
    pair<int, int> edgeCombos[edges];
    //Graph graph(edges);
    
    for (int i = 0; i < edges; i++) {
        
        cin >> computer1 >> computer2 >> cost; //read in data

        //Update map of computer names to index
        if (computerToIndex.size() == 0) {
            //if map is empty, add both computers to map
            computerToIndex[computer1] = 0;
            computerToIndex[computer2] = 1;
            vertices = 2;
            //check if a server
            servers[0] = false;
            if (computer1.length() > 7) {
                temp = computer1.substr(computer1.length()-7, 7);
                if (temp == "_server") {
                    servers[0] = true;
                }
            }
            servers[1] = false;
            if (computer2.length() > 7) {
                temp = computer2.substr(computer2.length()-7, 7);
                if (temp == "_server") {
                    servers[1] = true;
                }
            }
        }
        else {
            //check if computer already in map
            if (computerToIndex.find(computer1) == computerToIndex.end()) {
                computerToIndex[computer1] = vertices;
                
                //check if a server
                servers[vertices] = false;
                if (computer1.length() > 7) {
                    temp = computer1.substr(computer1.length()-7, 7);
                    if (temp == "_server") {
                        servers[vertices] = true;
                    }
                }
                vertices++;
            }
            if (computerToIndex.find(computer2) == computerToIndex.end()) {
                computerToIndex[computer2] = vertices;
                
                //check if a server
                servers[vertices] = false;
                if (computer2.length() > 7) {
                    temp = computer2.substr(computer2.length()-7, 7);
                    if (temp == "_server") {
                        servers[vertices] = true;
                    }
                }
                vertices++;
            }
        }

        edgeCombos[i] = make_pair(computerToIndex[computer1], computerToIndex[computer2]);
        costs[i] = cost;
    }

    Graph graph(vertices);
    //int tempCosts = costs.size();
    for (int i = 0; i < edges; i++) {
        graph.addEdge(edgeCombos[i].first, edgeCombos[i].second, costs[i]);
    }

    //int tempServerSize = canBeServer.size();
    for (int i = 0; i < vertices; i++) {
        if (servers[i]) {
            vector<int> distances;
            distances = graph.dijkstra(i);
            totalCost = 0;
            //tempDistances = distances.size();
            isTooBig = false;
            for (int j = 0; j < vertices; j++) {
                if (distances.back() >= INFINITE_COST) {
                    isTooBig = true;
                    j = vertices;
                }
                else
                {
                    totalCost += distances.back();
                    distances.pop_back();
                }
            }
            if (!isTooBig) {
                serverCosts.insert(make_pair(totalCost, i));
            }
        }
    }

    pair<int, int> min = serverCosts.getMinItem();

    if (serverCosts.getNumItems() == 0) {
        cout << "no server can serve the whole network" << endl;
    }
    else {
        //vector<string> outputAlphabetically;
        string outputAlphabetically[vertices];
        int numOutputs = 0;
        cout << "total delay: " << min.first << endl;
        serverCosts.removeMinItem();

        for (auto it = computerToIndex.begin(); it != computerToIndex.end(); it++) {
            if (it->second == min.second) {
                outputAlphabetically[numOutputs] = it->first;
                numOutputs++;
            }
        }

        while (serverCosts.getMinItem().first == min.first && serverCosts.getNumItems() > 0) {
            for (auto it = computerToIndex.begin(); it != computerToIndex.end(); it++) {
                if (it->second == serverCosts.getMinItem().second) {
                    outputAlphabetically[numOutputs] = it->first;
                    numOutputs++;
                }
            }
            serverCosts.removeMinItem();
        }

        //int tempValue = outputAlphabetically.size();

        bool swap = false;
        do {
            swap = false;
            for (int i = 0; i < numOutputs-1; i++) {
                if (outputAlphabetically[i] > outputAlphabetically[i+1]) {
                    string tempOutput;
                    tempOutput = outputAlphabetically[i];
                    outputAlphabetically[i] = outputAlphabetically[i+1];
                    outputAlphabetically[i+1] = tempOutput;
                    swap = true;
                }
            }
        } while(swap);

        for (int i = 0; i < numOutputs; i++) {
            cout << outputAlphabetically[i] << endl;
        }

    }


    return 0;
}