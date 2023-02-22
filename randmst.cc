/*
 * randmst.cc
 * Author: Saketh Mynampati 
 */
#include <iostream>
#include <cstdlib>
#include <random>
#include <math.h>
#include "minheap.hh"
using namespace std;

int main(int argc, char **argv) 
{
    // Initialize random seed.
    srand(time(0));

    // process args
    int flag = stoi(argv[0]);
    int npoints = stoi(argv[1]);
    int ntrials = stoi(argv[2]);
    int ndim = stoi(argv[3]);

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
