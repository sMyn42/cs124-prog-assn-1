#include <cassert>
#include <cstdlib>
#include <cinttypes>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

class Heap {
    public:
        vector<tuple<int, double>> heap;
        void insert (tuple<int, double> v) {

        }
        tuple<int, double> delmin () {
            
        }
        tuple<int, double> peekmin () {
            
        }
        void heapify (int i) { // invariant, everything above, and below N are independent max heaps.
            int l = left(i);
            int r = right(i);
            int smallest; // index of largest 
            if (l < heap.size() && get<1>(heap[l]) < get<1>(heap[i])) {
                smallest = l;
            } else {
                smallest = i;
            }

            if (r < heap.size() && get<1>(heap[r]) < get<1>(heap[smallest])) {
                smallest = r;
            }

            if (smallest != i) {
                tuple<int, double> temp = heap[i];
                heap[i] = heap[smallest];
                heap[smallest] = temp;
                heapify(smallest);
            }
        }
};

int parent (int i) {
    return (i - 1) / 2;
}
int left (int i) {
    return 2 * i + 1;
}
int right (int i) {
    return 2 * i + 2;
}