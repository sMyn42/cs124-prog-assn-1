#include <iostream>
#include <cstdlib>
#include <random>
#include <math.h>
#include <tuple>
#include <vector>
#include "minheap.hh"
#include "graph.hh"

using namespace std;

// Prim's Algorithm
// -- Inputs: Graph Representation (mat, or adj), Source Vertex (int)
// -- Outputs: vector of tuples representing the the different edges included in the tree.
vector<tuple<int, int, double>> prim(vector<vector<double>> graph, int src)
{
    int n = graph.size();

    // Create a vector to store the MST
    vector<tuple<int, int, double>> mst;

    // Create a vector to keep track of vertices in the MST
    vector<bool> inMST(n, false);

    // Create a min heap
    Heap pq;

    // Insert the source vertex into the min heap
    pq.insert(make_tuple(src, 0));

    while (!pq.heap.empty())
    {
        // Get the vertex with the minimum distance from the heap
        auto curr = pq.delmin();
        int u = get<0>(curr);
        double dist = get<1>(curr);

        // If the vertex is already in the MST, continue to the next vertex
        if (inMST[u])
        {
            continue;
        }

        // Mark the vertex as visited
        inMST[u] = true;

        // Add the vertex and its distance to the source to the MST
        if (u != src)
        {
            mst.push_back(make_tuple(parent[u], u, dist));
        }

        // Iterate over all the adjacent vertices
        for (int v = 0; v < n; v++)
        {
            // Check if the vertex is adjacent and not in the MST
            if (graph[u][v] != 0 && !inMST[v])
            {
                // If the distance to the adjacent vertex is less than its current distance,
                // update the distance and insert it into the heap
                if (graph[u][v] < pq.heap[v].second || pq.heap[v].second == -1)
                {
                    pq.heap[v] = make_tuple(u, graph[u][v]);
                    pq.heapify(v);
                }
            }
        }
    }

    return mst;
}

int main(int argc, char **argv)
{
    // Initialize random seed.
    srand(time(0));

    // process args
    int flag = stoi(argv[1]);
    int npoints = stoi(argv[2]);
    int ntrials = stoi(argv[3]);
    int ndim = stoi(argv[4]);

    vector<vector<double>> graph;

    // generate points
    switch (flag)
    {
    case 0:
        break;
    case 1: // n vertices, random weights
        graph = generateRandomGraph(npoints);
        break;
    case 2: // n vertices in unit square
    case 3: // n vertices in unit cube, hypercube, etc.
        graph = generateGridGraph(npoints, ndim);
        break;
    case 4: // testing
    case 5: // testing
        graph = generateTestGraph();
        break;
    }

    // Print the generated graph
    printGraph(graph);

    // Run Prim's algorithm
    vector<tuple<int, int, double>> mst = prim(graph, 0);

    // Print the MST
    cout << "Minimum Spanning Tree: " << endl;
    for (auto edge : mst)
    {
        cout << get<0>(edge) << " -- " << get<


int main() {
    // create example graph
    // should use the randomly generated graphs instead
    Graph G(6);
    G.add_edge(0, 1, 2.0);
    G.add_edge(0, 2, 3.0);
    G.add_edge(1, 2, 1.0);
    G.add_edge(1, 3, 1.0);
    G.add_edge(2, 3, 2.0);
    G.add_edge(2, 4, 1.0);
    G.add_edge(3, 4, 1.0);
    G.add_edge(3, 5, 4.0);
    G.add_edge(4, 5, 3.0);

    // compute MST using Prim's algorithm
    vector<Edge> MST = prim(G);

    // print MST edges and total weight
    double total_weight = 0.0;
    for (auto& e : MST) {
        cout << e.src << " -- " << e.dest << " (" << e.weight << ")" << endl;
        total_weight += e.weight;
    }
    cout << "Total weight: " << total_weight << endl;

    return 0;
}
