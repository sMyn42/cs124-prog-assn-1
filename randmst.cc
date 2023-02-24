#include <iostream>
#include <cstdlib>
#include <random>
#include <math.h>
#include <tuple>
#include <vector>
#include <unordered_set>
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

double distance (tuple<double, double, double, double> x, tuple<double, double, double, double> y) {
    double d = 0;
    d = d + pow(get<0>(x) - get<0>(y), 2.0);
    d = d + pow(get<1>(x) - get<1>(y), 2.0);
    d = d + pow(get<2>(x) - get<2>(y), 2.0);
    d = d + pow(get<3>(x) - get<3>(y), 2.0);
    return sqrt(d);
}

// Running the algorithm fr.
int main(int argc, char **argv) 
{
    // Initialize random seed.
    std::mt19937_64 gen64;
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    gen64.seed(time(0));
    
    // process args
    int flag = stoi(argv[1]);
    int npoints = stoi(argv[2]);
    int ntrials = stoi(argv[3]);
    int ndim = stoi(argv[4]);

    double total_weight = 0;

    for (int t = 0; t < ntrials; t++) {

        vector< tuple<double, double, double, double> > vert;

        // generate points
        switch (ndim) {
            case 0:
                break;
            case 1: // n vertices, random weights
                break;
            case 2: // n vertices in unit square
            case 3: // n vertices in unit cube, hypercube, etc.
            case 4:
                // Create vector of all vertices and positions for 2-4 dimensions.
                for (int v = 0; v < npoints; v++) {
                    double coords[] = {0, 0, 0, 0};
                    for (int d = 0; d < ndim; d++) {
                        coords[d] = dis(gen64);
                    }
                    vert.push_back(make_tuple(coords[0], coords[1], coords[2], coords[3]));
                }



                break;
        }

        // Run Prim's
        switch (ndim) {
            case 0:
                break;
            case 1: // n vertices, random weights\
                // lolz
                break;
            case 2: // n vertices in unit square
            case 3: // n vertices in unit cube, hypercube, etc.
            case 4:
                //Prim's for N-Dim spaces:
                Heap H;
                unordered_set<int> S;

                double dist[npoints];
                int prev[npoints];
                int s = 0;
                double tree_weight = 0;
                double max_len = 0.0001;

                H.insert(make_tuple(s, 0));

                for (int i = 0; i < npoints; i++) {
                    dist[i] = 2;
                    prev[i] = -1;
                }
                dist[s] = 0;

                while (!(H.size() == 0)) {
                    int v = get<0>(H.delmin());
                    S.insert(v);

                    printf("Num Visited: %lu \n", S.size());

                    // while (S.size() < npoints - 1) {
                    // for (int u = 0; u < npoints; u++) {
                        for (int w = 0; w < npoints; w++) {
                            if (S.find(w) != S.end()) {
                                continue;
                            }
                            double ell = distance(vert[v], vert[w]);
                            // if (ell > max_len) {
                            //     continue;
                            // }
                            // Time Intensive: check if this distance is better, 
                            // --- make this the shortest known distance and 
                            // add it to the minheap
                            if (dist[w] > ell) {
                                printf("AYE");
                                dist[w] = ell;
                                prev[w] = v;
                                H.insert(make_tuple(w, dist[w]));
                            }
                        }
                    // }
                    // }
                }

                // Calculate weights after Prim's
                for (int v = 1; v < npoints; v++) {
                    tree_weight = tree_weight + distance(vert[v], vert[prev[v]]);
                }

                total_weight = total_weight + tree_weight;
        }
    }

    printf("%f \n", total_weight / ntrials);
    return 0;

}