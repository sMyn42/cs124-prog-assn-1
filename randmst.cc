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
// -- tuple<int, double> destination, weight.

// Vertex: given by number 0 through npoints -1.

// Prim's Algorithm
// -- Inputs: Graph Representation (mat, or adj), Source Vertex (int)
// -- Outputs: vector of tuples representing the the different edges included in the tree.

double k (int npoints, int ndim) {
    if (ndim != 1) return npoints > 4000 ? pow(10, (1.0/ndim)) * pow(npoints, -(1.0/ndim)) : 2;
    return 5.2/(npoints + 1);
}

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

    long ts = time(0);

    for (int t = 0; t < ntrials; t++) {

        long ts = time(0);

        vector< tuple<double, double, double, double> > vert;

        if (ndim == 1) {
            //Prim's for 1-Dim space:

            Heap H;
            unordered_set<int> S;

            double* dist = new double[npoints];
            int* prev = new int[npoints];
            int s = 0;
            double tree_weight = 0;
            double max_len = k(npoints, ndim);
            int num_visited = 0;

            H.insert(make_tuple(s, 0));

            for (int i = 0; i < npoints; i++) {
                dist[i] = max_len;
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

                for (int w = 0; w < npoints; w++) {
                    if (S.find(w) != S.end()) {
                        continue;
                    }
                    double ell = dis(gen64);
                    if (ell > max_len) {
                        continue;
                    }
                    if (dist[w] > ell) {
                        dist[w] = ell;
                        prev[w] = v;
                        H.insert(make_tuple(w, dist[w]));
                    }
                    if (H.size() == 0) {
                        H.insert(make_tuple(w, max_len));
                        printf("Sim Edge");
                    }
                }
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
                double coords[] = {0, 0, 0, 0};
                for (int d = 0; d < ndim; d++) {
                    coords[d] = dis(gen64);
                }
                vert.push_back(make_tuple(coords[0], coords[1], coords[2], coords[3]));
            }

            printf("Time taken to add vertices: %li \n", time(0) - ts);
            int ta = time(0);

            double max_len = k(npoints, ndim);

            vector< pair<int, double> >* E = new vector< pair<int, double> >[npoints];

            // Create adj list with pruning
            int num_edges_added = 0;
            for (int v = 0; v < npoints; v++) {
                for (int u = 0; u < npoints; u++) {
                    double ell = distance(vert[v], vert[u]);
                    if (ell < max_len) {
                        E[v].push_back(make_tuple(u, ell));
                        num_edges_added++;
                    }
                }
                printf("Edges added after vertex %i: %i \n", v, num_edges_added);
            }

            printf("Edges added: %i \n", num_edges_added);

            printf("Time taken to add edges: %li \n", time(0) - ta);
            ta = time(0);

            //Prim's for N-Dim spaces:
            Heap H;
            unordered_set<int> S;

            double* dist = new double[npoints];
            int* prev = new int[npoints];
            int s = 0;
            double tree_weight = 0;
            int num_visited = 0;

            H.insert(make_tuple(s, 0));

            for (int i = 0; i < npoints; i++) {
                dist[i] = max_len;
                prev[i] = -1;
            }
            dist[s] = 0;

            while (!(H.size() == 0) && S.size() < npoints) {
                int v = get<0>(H.delmin());
                S.insert(v);

                if (S.size() > num_visited + npoints/10) {
                    // printf("Num Visited: %lu \n", S.size());
                    num_visited = S.size();
                }

                unsigned long adj_size = E[v].size();
                // printf("%li \n", adj_size);

                // printf("Heap is %i long\n", H.size());

                // inspect all adjacent vertices
                for (int w = 0; w < adj_size; w++) {
                    if (S.find(E[v][w].first) != S.end()) {
                        continue;
                    }

                    double ell = E[v][w].second;

                    if (dist[E[v][w].first] > ell) {
                        dist[E[v][w].first] = ell;
                        prev[E[v][w].first] = v;

                        // Add vertex to frontier with given distance.
                        H.insert(make_tuple(E[v][w].first, ell));
                    }

                    if (H.size() == 0) {
                        H.insert(make_tuple(E[v][w].first, max_len));
                        printf("Sim Edge");
                    }
                }
            }

            // printf("Size of heap after Prims: %i\n ", H.size());

            printf("Time taken to run Prim's: %li\n", time(0) - ta);
            ta = time(0);


            // Calculate weights after Prim's
            int c = 0;
            for (int v = 1; v < npoints; v++) {
                tree_weight = tree_weight + dist[v];
                if (dist[v] == max_len) {
                    c++;
                }
            }

            // printf("%i \n", c);

            total_weight = total_weight + tree_weight;

            delete[] dist;
            delete[] prev;
            delete[] E;

            printf("Num Visited: %lu \n", S.size());

            printf("Max Length: %.4f \n", max_len);
        }

        printf("Trial %i took %ld seconds. \n", t, time(0) - ts);

    }

    double avg_w = total_weight / ntrials;

    // ofstream myfile;
    // myfile.open("randmst.log", std::ios_base::app);
    char str[100];
    snprintf(str, 45, "%.7f %i %i %i in %ld seconds\n", avg_w, npoints, ntrials, ndim, time(0) - ts);
    // myfile << str;
    // myfile.close();

    printf("%.5f %i %i %i\n", avg_w, npoints, ntrials, ndim);

    return 0;

}