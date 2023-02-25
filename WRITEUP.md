# Walkthrough of code setup:

    We started by implementing a function that would generate a random graph by a given size and dimensionality, with random edge weights or points in a certain space. It then proceeds to implement Prim's algorithm, which is a greedy algorithm used to find a minimum spanning tree for a weighted undirected graph. The minimum spanning tree is represented as a vector of tuples that contain information about the edges included in the tree.

The input parameters to the code are passed through the command line and are as follows:

   # flag: 
    a integer that determines which type of graph to generate (0 is empty, 1 is random edge weights, 2 is unit square, 3 is unit hypercube, 4 and 5 are testing)
   # npoints: 
    the number of vertices in the graph
   # ntrials: 
   the number of trials to run the algorithm
   # ndim: 
   the dimensionality of the space in which the points are located (only used if flag is 2 or 3)


In minheap.cc, we used a min-heap data structure with methods for insertion, deletion of the minimum element, and accessing the minimum element without removal. The implementation is based on an array representation of the heap, where the left child of a node at index i is at index 2i+1 and the right child is at index 2i+2, and the parent of a node at index i is at index (i-1)/2.

The insert method inserts a new tuple (consisting of an integer key and a double value) into the heap by appending it to the end of the array and then swapping it with its parent if the parent has a larger value. This process is repeated until the heap property is restored.

The delmin method removes the minimum element (which is always at the root of the heap), replaces it with the last element in the array, and then restores the heap property by repeatedly swapping the new root with its smallest child until the heap property is restored.

The peekmin method simply returns the minimum element without removing it.

The heapify method is a helper function used by delmin to restore the heap property. Given an index i, it finds the smallest of the three elements at indices i, 2i+1, and 2i+2, swaps it with the element at index i, and then recursively calls heapify on the new position of the swapped element.

The test_heap method is a simple test suite for the heap. It inserts three tuples with keys 1, 2, and 3 and values 0.2, 0.1, and 1.6, respectively, and then checks that the minimum element is returned in the correct order after each deletion.

 
# Result discussion:
For large values if n, j