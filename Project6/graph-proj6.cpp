#include "graph-proj6.h"

#include <iostream>

using namespace std;

void Graph::addEdge(int from, int to, int cost)
{
    if (inVertexRange(from) && inVertexRange(to))
    {
        adjacencyList[from].push_back(Edge(to, cost));
    }
    else
    {
        cout << "Error: Vertex out of range" << endl;
    }
}

vector<int> Graph::dijkstra(int source) const
{
    vector<int> distance(adjacencyList.size(), INFINITE_COST);
    vector<bool> visited(adjacencyList.size(), false);
    distance[source] = 0;

    for (int i = 0; i < adjacencyList.size(); i++)
    {
        int min = INFINITE_COST;
        int minIndex = -1;

        for (int j = 0; j < adjacencyList.size(); j++)
        {
            if (!visited[j] && distance[j] < min)
            {
                min = distance[j];
                minIndex = j;
            }
        }

        if (minIndex == -1)
        {
            break;
        }

        visited[minIndex] = true;

        for (list<Edge>::const_iterator it = adjacencyList[minIndex].begin(); it != adjacencyList[minIndex].end(); it++)
        {
            if (distance[minIndex] + it->cost < distance[it->to])
            {
                distance[it->to] = distance[minIndex] + it->cost;
            }
        }
    }

    return distance;
}