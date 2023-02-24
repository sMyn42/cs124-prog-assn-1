#include <iostream>
#include <fstream>
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
// -- tuple<int, float> destination, weight.

// Vertex: given by number 0 through npoints -1.

// Prim's Algorithm
// -- Inputs: Graph Representation (mat, or adj), Source Vertex (int)
// -- Outputs: vector of tuples representing the the different edges included in the tree.

float k (int npoints) {
    return 2;//.5 * pow(log2(npoints), -0.378) - 0.85;
}

float distance (tuple<float, float, float, float> x, tuple<float, float, float, float> y) {
    float d = 0;
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
    std::uniform_real_distribution<float> dis(0.0, 1.0);
    gen64.seed(time(0));
    
    // process args
    int flag = stoi(argv[1]);
    int npoints = stoi(argv[2]);
    int ntrials = stoi(argv[3]);
    int ndim = stoi(argv[4]);

    float total_weight = 0;

    float max_weight = 0.0;

    long ts = time(0);

    for (int t = 0; t < ntrials; t++) {

        long ts = time(0);

        vector< tuple<float, float, float, float> > vert;

        if (ndim == 1) {
            //Prim's for 1-Dim space:

            Heap H;
            unordered_set<int> S;

            float* dist = new float[npoints];
            int* prev = new int[npoints];
            int s = 0;
            float tree_weight = 0;
            float max_len = k(npoints);
            int num_visited = 0;

            H.insert(make_tuple(s, 0));

            for (int i = 0; i < npoints; i++) {
                dist[i] = 2;
                prev[i] = -1;
            }
            dist[s] = 0;

            while (!(H.size() == 0) && S.size() < npoints) {
                int v = get<0>(H.delmin());
                S.insert(v);

                if (S.size() > num_visited) {
                    printf("Num Visited: %lu \n", S.size());
                    num_visited = S.size();
                }

                // // // while (S.size() < npoints) {
                // // // for (int u = 0; u < npoints; u++) {
                for (int w = 0; w < npoints; w++) {
                    if (S.find(w) != S.end()) {
                        continue;
                    }
                    float ell = dis(gen64);
                    if (ell > max_len) {
                        continue;
                    }
                    // Time Intensive: check if this distance is better, 
                    // --- make this the shortest known distance and 
                    // add it to the minheap
                    if (dist[w] > ell) {
                        // printf("AYE");
                        dist[w] = ell;
                        prev[w] = v;
                        H.insert(make_tuple(w, dist[w]));
                    }
                }
                // // // }
                // // // }
            }

            for (int v = 1; v < npoints; v++) {
                tree_weight = tree_weight + dist[v];
            }

            total_weight = total_weight + tree_weight;

            delete[](dist);
            delete[](prev);
        }
        
        if (ndim == 2 || ndim == 3 || ndim == 4) {

            // Generate Vertices
            for (int v = 0; v < npoints; v++) {
                float coords[] = {0, 0, 0, 0};
                for (int d = 0; d < ndim; d++) {
                    coords[d] = dis(gen64);
                }
                vert.push_back(make_tuple(coords[0], coords[1], coords[2], coords[3]));
            }

            //Prim's for N-Dim spaces:
            Heap H;
            unordered_set<int> S;

            float* dist = new float[npoints];
            int* prev = new int[npoints];
            int s = 0;
            float tree_weight = 0;
            float max_len = k(npoints);
            int num_visited = 0;

            H.insert(make_tuple(s, 0));

            for (int i = 0; i < npoints; i++) {
                dist[i] = 2;
                prev[i] = -1;
            }
            dist[s] = 0;

            while (!(H.size() == 0) && S.size() < npoints) {
                int v = get<0>(H.delmin());
                S.insert(v);

                if (S.size() > num_visited) {
                    printf("Num Visited: %lu \n", S.size());
                    num_visited = S.size();
                }

                // // // while (S.size() < npoints) {
                // // // for (int u = 0; u < npoints; u++) {
                    for (int w = 0; w < npoints; w++) {
                        if (S.find(w) != S.end()) {
                            continue;
                        }
                        float ell = distance(vert[v], vert[w]);
                        if (ell > max_len) {
                            continue;
                        }
                        // Time Intensive: check if this distance is better, 
                        // --- make this the shortest known distance and 
                        // add it to the minheap
                        if (dist[w] > ell) {
                            // printf("AYE");
                            dist[w] = ell;
                            prev[w] = v;
                            H.insert(make_tuple(w, dist[w]));
                        }
                    }
                // // // }
                // // // }
            }

            // Calculate weights after Prim's

            for (int v = 1; v < npoints; v++) {
                tree_weight = tree_weight + distance(vert[v], vert[prev[v]]);
                if (distance(vert[v], vert[prev[v]]) > max_weight) {
                    max_weight = distance(vert[v], vert[prev[v]]);
                }
            }

            total_weight = total_weight + tree_weight;

            delete[] dist;
            delete[] prev;

        }

        printf("Trial %i took %ld seconds. \n", t, time(0) - ts);

    }

    // printf("k estimate: %.6f \n", max_weight);

    float avg_w = total_weight / ntrials;

    ofstream myfile;
    myfile.open("randmst.log", std::ios_base::app);
    char str[100];
    snprintf(str, 45, "%.7f %i %i %i in %ld seconds\n", avg_w, npoints, ntrials, ndim, time(0) - ts);
    myfile << str;
    myfile.close();

    printf("%.5f %i %i %i in %ld seconds\n", avg_w, npoints, ntrials, ndim, time(0) - ts);

    return 0;

}