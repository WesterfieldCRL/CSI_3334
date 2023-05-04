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
#include <random>
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
    vector<bool> canBeServer;

    vector<int> computers1;
    vector<int> computers2;
    vector<int> costs;

    int edges;

    cin >> edges;

    //Graph graph(edges);

    for (int i = 0; i < edges; i++) {
        string computer1;
        string computer2;
        int cost;
        cin >> computer1 >> computer2 >> cost; //read in data

        //Update map of computer names to index
        if (computerToIndex.size() == 0) {
            //if map is empty, add both computers to map
            computerToIndex[computer1] = computerToIndex.size();
            computerToIndex[computer2] = computerToIndex.size();

            //check if a server
            if (computer1.length() > 7) {
                string temp = computer1.substr(computer1.length()-7, 7);
                if (temp == "_server") {
                    canBeServer.push_back(true);
                }
                else {
                    canBeServer.push_back(false);
                }
            }
            if (computer2.length() > 7) {
                string temp = computer2.substr(computer2.length()-7, 7);
                if (temp == "_server") {
                    canBeServer.push_back(true);
                }
                else {
                    canBeServer.push_back(false);
                }
            }
        }
        else {
            //check if computer already in map
            if (computerToIndex.find(computer1) == computerToIndex.end()) {
                computerToIndex[computer1] = computerToIndex.size();

                //check if a server
                if (computer1.length() > 7) {
                    string temp = computer1.substr(computer1.length()-7, 7);
                    if (temp == "_server") {
                        canBeServer.push_back(true);
                    }
                    else {
                        canBeServer.push_back(false);
                    }
                }
            }
            if (computerToIndex.find(computer2) == computerToIndex.end()) {
                computerToIndex[computer2] = computerToIndex.size();

                //check if a server
                if (computer2.length() > 7) {
                    string temp = computer2.substr(computer2.length()-7, 7);
                    if (temp == "_server") {
                        canBeServer.push_back(true);
                    }
                    else {
                        canBeServer.push_back(false);
                    }
                }
            }
        }

        //Add edge to graph
        //graph.addEdge(computerToIndex[computer1], computerToIndex[computer2], cost);
        computers1.push_back(computerToIndex[computer1]);
        computers2.push_back(computerToIndex[computer2]);
        costs.push_back(cost);
    }

    Graph graph(computerToIndex.size());

    for (int i = 0; i < costs.size(); i++) {
        graph.addEdge(computers1[i], computers2[i], costs[i]);
    }
    

    for (int i = 0; i < canBeServer.size(); i++) {
        if (canBeServer[i]) {
            vector<int> distances = graph.dijkstra(i);
            int totalCost = 0;
            for (int i = 0; i < distances.size(); i++) {
                totalCost += distances[i];
            }
            serverCosts.insert(make_pair(totalCost, i));
        }
    }

    pair<int, int> min = serverCosts.getMinItem();

    if (min.first >= INFINITE_COST) {
        cout << "no server can serve the whole network." << endl;
    }
    else {
    
        cout << "total delay: " << min.first << endl;

        

        for (auto it = computerToIndex.begin(); it != computerToIndex.end(); it++) {
            if (it->second == min.second) {
                cout << it->first << endl;
            }
        }
        serverCosts.removeMinItem();

        while (serverCosts.getMinItem().first == min.first && serverCosts.getNumItems() > 0) {
            for (auto it = computerToIndex.begin(); it != computerToIndex.end(); it++) {
                if (it->second == min.second) {
                    cout << it->first << endl;
                }
            }
            serverCosts.removeMinItem();
        }
    }


    return 0;
}