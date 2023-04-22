#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <random>
#include <cassert>
#include <algorithm>


using namespace std;

// This class represents a directed graph, with edges represented with an
// adjacency matrix.
class Graph {
    public:
        // Construct a graph with num_vertices nodes, with no edges.
        Graph(int num_vertices) :
            adjacencyMatrix(num_vertices, vector<bool>(num_vertices, false)) {}

        // Check and fail if the given vertex is out of range for this graph.
        // Parameters:
        //  - vtx: the vertex number to check
        void check_vertex_range(size_t vtx) const { assert(0 <= vtx and vtx < size()); }

        // Get the number of nodes in this graph
        // Return value: the number of graph nodes
        size_t size() const { return adjacencyMatrix.size(); }

        // Add a directed edge from "from" to "to".
        // Parameters:
        //  - from: the source node of the edge
        //  - to: the destination node of the edge
        void add_edge(int from, int to) {
            check_vertex_range(from);
            check_vertex_range(to);
            adjacencyMatrix[from][to] = true;
        }

        // Check if there is a directed edge from "from" to "to".
        // Parameters:
        //  - from: the source node of the edge
        //  - to: the destination node of the edge
        bool has_edge(int from, int to) const {
            check_vertex_range(from);
            check_vertex_range(to);
            return adjacencyMatrix[from][to];
        }

        // Print the entire adjacency matrix to the given stream. Note that to
        // make the formatting layout nicely, only the last digit of the row and
        // column headers are printed (so instead of "12", print only "2").
        // Parameters:
        //  - out: the stream to send the output to
        void printMatrix(ostream &out=cout) const {
            out << " ";
            for (size_t j = 0; j < size(); ++j) {
                out << " " << (j % 10); // only print out the last digit
            }
            out << endl;
            for (size_t i = 0; i < size(); ++i) {
                out << (i % 10); // only print out the last digit
                for (size_t j = 0; j < size(); ++j) {
                    out << " " << (adjacencyMatrix[i][j] ? 1 : 0);
                }
                out << endl;
            }
        }

        // Print only the actual edges to the given stream, in a format that can
        // be rendered by GraphViz. If you put the output of this into GraphViz,
        // it will show you the graph visually.
        // See https://dreampuf.github.io/GraphvizOnline/
        // Parameters:
        //  - out: the stream to send the output to
        void printGraphviz(ostream &out=cout) const {
            out << "digraph G {\n"; // for "directed graph"
            for (size_t i = 0; i < size(); ++i) {
                for (size_t j = 0; j < size(); ++j) {
                    if (has_edge(i, j)) {
                        out << "  " << i << " -> " << j << ";\n";
                    }
                }
            }
            out << "}\n";
        }

    private:
        vector<vector<bool> > adjacencyMatrix;

};

// Define a new type for keeping track of the status of a vertex during DFS/BFS
// search.
typedef enum { UNVISITED, BEING_VISITED, VISITED } VisitStatus;

// dfs is a recursive algorithm for searching the graph "g" from the vertex
// "current".
//
// Start by setting the status of current to BEING_VISITED.
// Then explore the UNVISITED neighbors of the current vertex (recursively).
// Then set the status of current to VISITED, and add it to the finish_order.
//
// Write this using recursion. If you finish early and want an extra challenge,
// then try rewriting it iteratively (using a stack to simulate the recursion).
// If you rewrite it iteratively, be careful in what order you visit nodes so
// you get the same behavior as the recursive method.
//
// Parameters:
//  - g: the graph to search
//  - current: the vertex where the search is currently at
//  - status: a vector with one entry for each vertex, containing UNVISITED,
//            BEING_VISITED, or VISITED
//  - finish_order: an initially empty vector which you should append current to
//                  once current becomes VISITED
void dfs(Graph const &g, int current, vector<VisitStatus> *status, vector<int> *finish_order) {
    // FILL IN HERE -- my code is 8 lines long
    if (status->at(current) != UNVISITED) {
        return;
    }
    status->at(current) = BEING_VISITED;
    for (int i = 0; i < g.size(); i++) {
        if (g.has_edge(current, i) /*&& status->at(i) == UNVISITED*/) {
            dfs(g, i, status, finish_order);
        }
    }
    status->at(current) = VISITED;
    finish_order->push_back(current);
}

// bfs is a non-recursive algorithm for searching the graph "g" from the vertex
// "current".
//
// Start by:
//  - setting the status of current to BEING_VISITED
//  - put current on the queue
// Then, while the queue is not empty:
//  - pull vertex x off the front
//  - for each neighbor y of x that is UNVISITED
//      - mark y as BEING_VISITED and put y on the queue
//  - mark x as VISITED
//
// Parameters:
//  - g: the graph to search
//  - current: the vertex where the search is currently at
//  - status: a vector with one entry for each vertex, containing UNVISITED,
//            BEING_VISITED, or VISITED
//  - discovery_order: an initially empty vector which you should append current
//                     to once current becomes BEING_VISITED
void bfs(Graph const &g, int current, vector<VisitStatus> *status, vector<int> *discovery_order) {
    // FILL IN HERE -- my code is 16 lines long
    /*status->at(current) = BEING_VISITED;
    vector<int> queue;
    queue.push_back(current);
    while (!queue.empty())
    {
        int x = queue.front();
        
        queue.erase(queue.begin());
        for (int i = 0; i < g.size(); i++) {
            if (g.has_edge(x, i) && status->at(i) == UNVISITED) {
                status->at(i) = BEING_VISITED;  
                
                queue.push_back(i);
            }
        }
        status->at(x) = VISITED;
        discovery_order->push_back(x);
    }*/

    //same thing but implemented with queue
    queue<int> q;
    q.push(current);
    status->at(current) = BEING_VISITED;
    discovery_order->push_back(current);

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < g.size(); i++) {
            if (g.has_edge(x, i) && status->at(i) == UNVISITED) {
                discovery_order->push_back(i);
                status->at(i) = BEING_VISITED;
                q.push(i);
            }
        }
        status->at(x) = VISITED;
    }
}

// main constructs a graph of a specified size, adds a set of randomly chosen
// edges (at the specified density), and then runs DFS and BFS on the graph
// (starting from vertex 0), and reports the finish order of the reachable
// vertices.
//
// Parameters:
//  - argc: the number of command-line arguments
//  - argv: the command-line argument values
//
// You can specify two command line arguments:
//  - the number of nodes (default: 10)
//  - the graph density (default: 20%)
int main(int argc, char **argv) {
    // Set up parameters for creating the graph -- number of nodes and edges.
    const int NUM_NODES = (argc > 1) ? stoi(argv[1]) : 10;
    assert(0 < NUM_NODES and NUM_NODES <= 1000);

    // "Density" means "percent of possible edges". The value can be between 0 and 100.
    const int GRAPH_DENSITY = (argc > 2) ? stoi(argv[2]) : 20;
    assert(0 <= GRAPH_DENSITY and GRAPH_DENSITY <= 100);
    const int NUM_EDGES = NUM_NODES * (NUM_NODES - 1) * GRAPH_DENSITY / 100;

    cout << "Creating a graph with " << NUM_NODES << " nodes and " << NUM_EDGES << " edges\n";
    Graph g(NUM_NODES);

    // set up random numbers, with a seed (for reproducible results)
    mt19937 random_number_generator(1776);

    // create a random permutation of edges, then add the first NUM_EDGES of them
    vector<pair<unsigned int, pair<int, int> > > permutation;
    for (int i = 0; i < NUM_NODES; ++i) {
        for (int j = 0; j < NUM_NODES; ++j) {
            if (i != j) {
                // use a random number for sorting the edges
                permutation.push_back({(unsigned int)random_number_generator(), {i, j}});
            }
        }
    }

    // sorting by the random number gives a random ordering
    sort(permutation.begin(), permutation.end());

    // add NUM_EDGES edges to the graph
    for (int i = 0; i < NUM_EDGES; ++i) {
        int from = permutation[i].second.first;
        int to = permutation[i].second.second;
        g.add_edge(from, to);
    }

    // "status" keeps track of UNVISITED/BEING_VISITED/VISITED for each vertex
    vector<VisitStatus> status(g.size(), UNVISITED);
    // "finish_order" records when each vertex gets marked VISITED (for DFS)
    // "discovery_order" records when each vertex gets marked BEING_VISITED (for BFS)
    vector<int> finish_order, discovery_order;

    // do a DFS starting from vertex 0, then print the finish_order
    dfs(g, 0, &status, &finish_order);
    cout << "DFS finish order:   ";
    for (auto x : finish_order) { cout << " " << x; }
    cout << endl;

    // reset the status vector
    fill(status.begin(), status.end(), UNVISITED);

    // do a BFS starting from vertex 0, then print the discovery_order
    bfs(g, 0, &status, &discovery_order);
    cout << "BFS discovery order:";
    for (auto x : discovery_order) { cout << " " << x; }
    cout << endl;

    // uncomment this to get output you can use to
    // visualize the graph at https://dreampuf.github.io/GraphvizOnline/
    // g.printGraphviz();

    return 0;
}

// Sample outputs for different command line parameters (compare your results
// against these):
//
// ./week_13_answer
// Creating a graph with 10 nodes and 18 edges
// DFS finish order:    5 2 6 9 3 4 1 0
// BFS discovery order: 0 1 2 9 3 4 5 6
//
// ./week_13_answer 20
// Creating a graph with 20 nodes and 76 edges
// DFS finish order:    15 13 9 17 18 8 19 2 5 6 12 14 7 10 11 3 16 4 1 0
// BFS discovery order: 0 1 2 11 12 4 10 14 17 9 19 3 6 16 18 7 8 13 5 15
//
// ./week_13_answer 20 90
// Creating a graph with 20 nodes and 342 edges
// DFS finish order:    18 19 17 16 15 14 13 12 11 9 10 8 7 6 5 4 3 2 1 0
// BFS discovery order: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 18 19 17
//
// ./week_13_answer 30
// Creating a graph with 30 nodes and 174 edges
// DFS finish order:    24 16 28 29 13 23 20 25 15 17 26 19 22 27 12 11 7 6 14 21 18 10 2 8 9 5 3 4 1 0
// BFS discovery order: 0 1 2 9 11 12 13 20 23 29 4 7 10 18 28 8 26 27 25 5 19 21 22 24 6 14 3 17 16 15