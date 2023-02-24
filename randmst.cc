#include <iostream>
#include <cstdlib>
#include <random>
#include <math.h>
#include <tuple>
#include <vector>
#include "minheap.hh"
using namespace std;

// Graph representations:
// adj mat
// -- npoints by npoints array
// -- weight at index i, j with vertex i to vertex j edge represented.

// adj list
// -- npoints lists each containing tuples of vertex number and edge weight.
// -- tuple<int, double> destination, weight.

// Vertex: given by number 0 through npoints -1.

// Prim's Algorithm
// -- Inputs: Graph Representation (mat, or adj), Source Vertex (int)
// -- Outputs: vector of tuples representing the the different edges included in the tree.

int main(int argc, char **argv) 
{
    // Initialize random seed.
    srand(time(0));
    
    // process args
    int flag = stoi(argv[1]);
    int npoints = stoi(argv[2]);
    int ntrials = stoi(argv[3]);
    int ndim = stoi(argv[4]);

    double vert[npoints][ndim];
    double mat[npoints][npoints];

    // generate points
    switch (flag) {
        case 0:
            break;
        case 1: // n vertices, random weights
            for (int i = 0; i < npoints; i++) {
                for (int j = 0; j < npoints; j++) {
                    mat[i][j] = (float)rand()/(float)(RAND_MAX);;
                }
            }
            break;
        case 2: // n vertices in unit square
        case 3: // n vertices in unit cube, hypercube, etc.
            // add vertices and locations
            for (int i = 0; i < npoints; i++) {
                for (int k = 0; k < ndim; k++) {
                    vert[i][k] = (float)rand()/(float)(RAND_MAX);
                }
            }
            for (int i = 0; i < npoints; i++) {
                for (int j = 0; j < npoints; j++) {
                    mat[i][j] = 0;
                    for (int k = 0; k < ndim; k++) {
                        mat[i][j] += vert[i][k] - vert[j][k];
                    }
                    mat[i][j] = sqrt(mat[i][j]);
                }
            }
            break;
        case 4: // testing
        case 5: // testing
            break;
    }

    return 0;

}

// Function to find total weight of tree given the adjacency list
int total_tree_weight(const vector<vector<pair<int, int>>>& adj_list) {
    int n = adj_list.size();
    vector<bool> visited(n, false);
    int total_weight = 0;
    // Perform DFS starting from node 0
    auto dfs = [&](auto&& self, int u) -> void {
        visited[u] = true;
        for (auto [v, weight] : adj_list[u]) {
            if (!visited[v]) {
                total_weight += weight;
                self(self, v);
            }
        }
    };
    dfs(dfs, 0);
    return total_weight;
}



