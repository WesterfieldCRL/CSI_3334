#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class AdjacencyMatrixGraph {
    public:
        AdjacencyMatrixGraph(int num_vertices) : 
            adj_matrix(num_vertices, vector<bool>(num_vertices, false)) {}
        void add_edge(int u, int v)
        {
            adj_matrix[u][v] = true;
        }
        bool edge_exists(int u, int v) const
        {
            return adj_matrix[u][v];
        }
        void print_edges(int u) const
        {
            for (int i = 0; i < adj_matrix.size(); i++)
            {
                if (edge_exists(u, i))
                {
                    cout << u << " -> " << i << endl;
                }
            }
        }
        void print_edges() const
        {
            for (int i = 0; i < adj_matrix.size(); i++)
            {
                print_edges(i);
            }
        }
        int count_all_edges() const
        {
            int count = 0;
            for (int i = 0; i < adj_matrix.size(); i++)
            {
                for (int j = 0; j < adj_matrix.size(); j++)
                {
                    if (edge_exists(i, j))
                    {
                        count++;
                    }
                }
            }
            return count;
        }
    private:
        vector<vector<bool> > adj_matrix; // a VxV matrix
        // adj_matrix[u][v] is true if there is an edge u -> v
};

class AdjacencyListGraph {
    public:
        AdjacencyListGraph(int num_vertices) : adj_list(num_vertices) {}
        void add_edge(int u, int v)
        {
            adj_list[u].push_back(v);
        }
        bool edge_exists(int u, int v) const
        {
            return find(adj_list[u].begin(), adj_list[u].end(), v) != adj_list[u].end();
            /*for (list<int>::const_iterator it = adj_list[u].begin(); it != adj_list[u].end(); it++)
            {
                if (*it == v)
                {
                    return true;
                }
            }
            return false;*/
        }
        void print_edges(int u) const
        {
            for (list<int>::const_iterator it = adj_list[u].begin(); it != adj_list[u].end(); it++)
            {
                cout << u << " -> " << *it << endl;
            }
        }
        void print_edges() const
        {
            for (int i = 0; i < adj_list.size(); i++)
            {
                print_edges(i);
            }
        }
        int count_all_edges() const
        {
            int count = 0;
            for (int i = 0; i < adj_list.size(); i++)
            {
                count += adj_list[i].size();
            }
            return count;
        }
    private:
        vector<list<int> > adj_list; // a vector of V lists
        // adj_list[u] is a list with the destinations of all edges leaving vertex u
};

int main() {
    // Just a sample of how the above classes might be used
    const int NUM_VERTICES = 8;
    AdjacencyMatrixGraph matrixGraph(NUM_VERTICES);
    AdjacencyListGraph listGraph(NUM_VERTICES);
    for (int i = 0; i < NUM_VERTICES; ++i) {
        for (int j = i + 1; j < NUM_VERTICES; ++j) {
            matrixGraph.add_edge(i, j);
            listGraph.add_edge(i, j);
        }
    }

    cout << "matrixGraph has " << matrixGraph.count_all_edges() << " edges:\n";
    matrixGraph.print_edges();

    cout << "listGraph has " << listGraph.count_all_edges() << " edges:\n";
    listGraph.print_edges();

    return 0;
}