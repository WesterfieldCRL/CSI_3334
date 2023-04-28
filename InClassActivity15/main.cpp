#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <random>
#include <tuple>

using namespace std;

// INFINITE_COST is a constant we'll use to indicate that "there is no edge
// here". There are other ways to handle a non-edge (such as a pair<bool, int>),
// but we'll keep things simple for this exercise.
int const INFINITE_COST = 100000000;

// This class represents a directed graph, with edges represented with an
// adjacency matrix.
class Graph {
    public:
        // Construct a graph with n nodes, with no edges.
        Graph(int n) :
            adjacencyMatrix(n, vector<int>(n, INFINITE_COST)) {}

        // Check and fail if the given vertex is out of range for this graph.
        // Parameters:
        //  - vtx: the vertex number to check
        void check_vertex_range(size_t vtx) const { assert(vtx < size()); }

        // Get the number of nodes in this graph
        // Return value: the number of graph nodes
        size_t size() const { return adjacencyMatrix.size(); }

        // Add a directed edge from "from" to "to".
        // Parameters:
        //  - from: the source node of the edge
        //  - to: the destination node of the edge
        void add_edge(int from, int to, int cost) {
            check_vertex_range(from);
            check_vertex_range(to);
            assert(cost < INFINITE_COST);
            adjacencyMatrix[from][to] = cost;
        }

        // Get the cost of the edge from "from" to "to". If it is INFINITE_COST,
        // then there is no edge.
        // Parameters:
        //  - from: the source node of the edge
        //  - to: the destination node of the edge
        int edge_cost(int from, int to) const {
            check_vertex_range(from);
            check_vertex_range(to);
            return adjacencyMatrix[from][to];
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
                    int ec = edge_cost(i, j);
                    if (ec != INFINITE_COST) {
                        out << "  " << i << " -> " << j << " [label=" << ec << "];\n";
                    }
                }
            }
            out << "}\n";
        }

    private:
        vector<vector<int>> adjacencyMatrix;

};

// Print a matrix, nicely formatted, replacing values of INFINITE_COST with "-".
// Also print a hash value for quick comparison.
// Parameters:
//  - m: the matrix to print (not assumed to be square)
//  - out: the stream to print to
void printMatrix(vector<vector<int>> const &m, ostream &out=cout) {
    // This code finds the largest non-infinite value, so we know how "wide" to
    // make the print statements below.
    int maxValue = 0;
    unsigned long long hashValue = 0;
    for (auto const &row : m) {
        for (auto cost : row) {
            if (cost != INFINITE_COST) {
                maxValue = max(maxValue, cost);
                hashValue = (hashValue * 101ULL + cost) % 1000000007ULL;
            }
        }
    }

    // Divide maxValue by 10 until it reaches zero; the number of times we do
    // this is the width.
    int width = 0;
    while (maxValue) { width++; maxValue /= 10; }

    out << "hash: " << hashValue << endl;
    for (auto const &row : m) {
        for (auto cost : row) {
            out << " " << setw(width);
            if (cost == INFINITE_COST) {
                out << "-";
            } else {
                out << cost;
            }
        }
        out << endl;
    }
}

// The "relaxation" algorithm. Given a matrix of costs and three vertices,
// identify whether the cost of a->b->c is less than the cost of a->c. In other
// words, does using b as an intermediate vertex reduce the cost of getting from
// a to c? If the cost can be lowered, then put the lower cost in the entry for
// a->c.
//
// Parameters:
//  - costs: a matrix of the current costs, which may be updated in this method
//  if a lower cost is found
//  - a: the source vertex
//  - b: the intermediate vertex
//  - c: the destination vertex
void relax(vector<vector<int>> *costs, int a, int b, int c) {
    int costAB = (*costs)[a][b];
    int costBC = (*costs)[b][c];
    int costAC = (*costs)[a][c];
    if (costAB + costBC < costAC) {
        (*costs)[a][c] = costAB + costBC;
    }
}

// The Floyd-Warshall algorithm for finding All-Pairs Shortest Paths.
//
// This algorithm operates as follows:
//  - fill each entry (i, j) of "costs" with one of:
//      - 0, if i == j
//      - g.edge_cost(i, j), if i != j 
//          (note that edge_cost may be INFINITE_COST)
//  - loop over every intermediate vertex k
//      - loop over every starting vertex i
//          - loop over every destination vertex j
//              - find out if i->k->j costs less than going directly i->j, using
//                the relax() method above.
//
// Parameters:
//  - g: the graph to start from
//  - costs: the matrix of costs to fill in (also the output of this function)
void floydWarshall(Graph const &g, vector<vector<int>> *costs) {
    // Initialize the costs matrix to the edge costs.
    for (int i = 0; i < g.size(); ++i) {
        for (int j = 0; j < g.size(); ++j) {
            if (i == j)
            {
                (*costs)[i][j] = 0;
            }
            else
            {
                (*costs)[i][j] = g.edge_cost(i, j);
            }
        }
    }

    // Loop over every intermediate vertex k.
    for (int k = 0; k < g.size(); ++k) {
        // Loop over every starting vertex i.
        for (int i = 0; i < g.size(); ++i) {
            // Loop over every destination vertex j.
            for (int j = 0; j < g.size(); ++j) {
                relax(costs, i, k, j);
            }
        }
    }
}


// main constructs a graph of a specified size, adds a set of randomly chosen
// edges (at the specified density), and then runs the Floyd-Warshall algorithm
// on the graph to find all shortest paths.
//
// Parameters:
//  - argc: the number of command-line arguments
//  - argv: the command-line argument values
//
// You can specify three command line arguments:
//  - the number of nodes (default: 10)
//  - the graph density (default: 20%)
//  - the max edge cost (default: 20)
int main(int argc, char **argv) {
    // Set up parameters for creating the graph -- number of nodes and edges.
    int const NUM_NODES = (argc > 1) ? stoi(argv[1]) : 10;
    assert(0 < NUM_NODES and NUM_NODES <= 1000);

    // "Density" means "percent of possible edges". The value can be between 0 and 100.
    int const GRAPH_DENSITY = (argc > 2) ? stoi(argv[2]) : 20;
    assert(0 <= GRAPH_DENSITY and GRAPH_DENSITY <= 100);
    int const NUM_EDGES = NUM_NODES * (NUM_NODES - 1) * GRAPH_DENSITY / 100;

    // Edges should have cost between 1 and MAX_EDGE_COST
    int const MAX_EDGE_COST = (argc > 3) ? stoi(argv[3]) : 20;

    cout << "Creating a graph with " << NUM_NODES << " nodes, "
         << NUM_EDGES << " edges, and max edge cost " << MAX_EDGE_COST << endl;
    Graph g(NUM_NODES);

    // set up random numbers, with a seed (for reproducible results)
    mt19937 random_number_generator(1845);

    // create a random permutation of edges, then add the first NUM_EDGES of them
    vector<tuple<int, int, int, int>> permutation;
    for (int i = 0; i < NUM_NODES; ++i) {
        for (int j = 0; j < NUM_NODES; ++j) {
            if (i != j) {
                // use a random number for sorting the edges
                int sort_key = random_number_generator();
                int edge_cost = 1 + (random_number_generator() % MAX_EDGE_COST);
                permutation.push_back({sort_key, edge_cost, i, j});
            }
        }
    }

    // sorting by the random number gives a random ordering
    sort(permutation.begin(), permutation.end());

    // add NUM_EDGES edges to the graph
    for (int i = 0; i < NUM_EDGES; ++i) {
        int sort_key, edge_cost, a, b;
        tie(sort_key, edge_cost, a, b) = permutation[i];
        g.add_edge(a, b, edge_cost);
    }

    // construct a matrix of "costs" (one cost per vertex/vertex pair), which
    // are the working space for Floyd Warshall. Note that the costs are not
    // initialized (they should be initialized inside floydWarshall).
    vector<vector<int>> costs(NUM_NODES, vector<int>(NUM_NODES));
    floydWarshall(g, &costs);

    // print the results
    printMatrix(costs);
    cout << endl;

    // use this output to get output you can use to visualize the graph at
    // https://dreampuf.github.io/GraphvizOnline/
    //g.printGraphviz();

    return 0;
}

// Sample outputs for different command line parameters (compare your results
// against these):
//
//
// ./week_14_answer 
// Creating a graph with 10 nodes, 18 edges, and max edge cost 20
// hash: 528401072
//   0 11 10  - 19 14 34 26 37 31
//  35  0 25  - 34 48 23 54 52 20
//  10  1  0  -  9 23 24 29 27 21
//  21  4 29  0 20 15 27 27 38 24
//   1 12 11  -  0 14 35 20 18 32
//   6 17 16  -  5  0 40 12 23 37
//  12  3  2  - 11 25  0 31 29 23
//  20 20 19  - 28 34 43  0 46 40
//   -  -  -  -  -  -  -  -  0  -
//  15  1  5  - 14 28  3 34 32  0
// 
// ./week_14_answer 5 
// Creating a graph with 5 nodes, 4 edges, and max edge cost 20
// hash: 635736428
//   0  - 10  -  -
//  14  0 24  -  -
//   -  -  0  -  -
//   -  -  -  0  -
//  34 20 44  1  0
// 
// ./week_14_answer 5 50 1
// Creating a graph with 5 nodes, 10 edges, and max edge cost 1
// hash: 814513567
//  0 1 1 2 1
//  1 0 2 3 2
//  1 1 0 3 2
//  1 2 1 0 2
//  2 1 2 1 0
// 
// ./week_14_answer 5 90
// Creating a graph with 5 nodes, 18 edges, and max edge cost 20
// hash: 75677159
//   0 19 10  7 11
//  14  0  9 11 10
//   6 11  0  2  1
//   9 25 14  0 15
//   9 20 13  1  0