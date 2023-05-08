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
    vector<bool> canBeServer;
    vector<string> outputAlphabetically;
    vector<int> computers1;
    vector<int> computers2;
    vector<int> costs;
    bool swap = false;
    string tempOutput;
    string computer1;
    string computer2;
    int cost;
    string temp;
    int totalCost;
    int tempDistances;
    bool isTooBig;
    vector<int> distances;

    int edges;
    int vertices = 0;
    cin >> edges;

    //Graph graph(edges);
    
    for (int i = 0; i < edges; i++) {
        
        cin >> computer1 >> computer2 >> cost; //read in data

        //Update map of computer names to index
        if (computerToIndex.size() == 0) {
            //if map is empty, add both computers to map
            computerToIndex[computer1] = computerToIndex.size();
            computerToIndex[computer2] = computerToIndex.size();
            vertices = 2;
            //check if a server
            canBeServer.push_back(false);
            if (computer1.length() > 7) {
                temp = computer1.substr(computer1.length()-7, 7);
                if (temp == "_server") {
                    canBeServer[0] = true;
                }
            }
            canBeServer.push_back(false);
            if (computer2.length() > 7) {
                temp = computer2.substr(computer2.length()-7, 7);
                if (temp == "_server") {
                    canBeServer[1] = true;
                }
            }
        }
        else {
            //check if computer already in map
            if (computerToIndex.find(computer1) == computerToIndex.end()) {
                computerToIndex[computer1] = computerToIndex.size();
                vertices++;
                //check if a server
                canBeServer.push_back(false);
                if (computer1.length() > 7) {
                    temp = computer1.substr(computer1.length()-7, 7);
                    if (temp == "_server") {
                        canBeServer[canBeServer.size()-1] = true;
                    }
                }
            }
            if (computerToIndex.find(computer2) == computerToIndex.end()) {
                computerToIndex[computer2] = computerToIndex.size();
                vertices++;
                //check if a server
                canBeServer.push_back(false);
                if (computer2.length() > 7) {
                    temp = computer2.substr(computer2.length()-7, 7);
                    if (temp == "_server") {
                        canBeServer[canBeServer.size()-1] = true;
                    }
                }
            }
        }

        computers1.push_back(computerToIndex[computer1]);
        computers2.push_back(computerToIndex[computer2]);
        costs.push_back(cost);
    }

    Graph graph(vertices);
    //int tempCosts = costs.size();
    for (int i = 0; i < edges; i++) {
        graph.addEdge(computers1[i], computers2[i], costs[i]);
    }

    //int tempServerSize = canBeServer.size();
    for (int i = 0; i < vertices; i++) {
        if (canBeServer[i]) {
            distances = graph.dijkstra(i);
            totalCost = 0;
            tempDistances = distances.size();
            isTooBig = false;
            for (int j = 0; j < tempDistances; j++) {
                totalCost += distances[j];
                if (distances[j] >= INFINITE_COST) {
                    isTooBig = true;
                    j = tempDistances;
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
    
        cout << "total delay: " << min.first << endl;
        serverCosts.removeMinItem();

        for (auto it = computerToIndex.begin(); it != computerToIndex.end(); it++) {
            if (it->second == min.second) {
                outputAlphabetically.push_back(it->first);
            }
        }

        while (serverCosts.getMinItem().first == min.first && serverCosts.getNumItems() > 0) {
            for (auto it = computerToIndex.begin(); it != computerToIndex.end(); it++) {
                if (it->second == serverCosts.getMinItem().second) {
                    outputAlphabetically.push_back(it->first);
                }
            }
            serverCosts.removeMinItem();
        }

        int tempValue = outputAlphabetically.size();
        do {
            swap = false;
            for (int i = 0; i < tempValue-1; i++) {
                if (outputAlphabetically[i] > outputAlphabetically[i+1]) {
                    tempOutput = outputAlphabetically[i];
                    outputAlphabetically[i] = outputAlphabetically[i+1];
                    outputAlphabetically[i+1] = tempOutput;
                    swap = true;
                }
            }
        } while(swap);

        for (int i = 0; i < tempValue; i++) {
            cout << outputAlphabetically[i] << endl;
        }

    }


    return 0;
}