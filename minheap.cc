#include <cassert>
#include <cstdlib>
#include <cinttypes>
#include <cstdio>
#include <vector>
#include "minheap.hh"

using namespace std;

Heap::Heap (int mr) {
    max_relevant = mr;
}

Heap::Heap () {
    max_relevant = INT_MAX - 10000;
}

void Heap::insert (tuple<int, double> v) {
    heap.push_back(v);
    int n = heap.size() - 1;
    while (n != 0 && get<1>(heap[parent(n)]) > get<1>(heap[n])) {
        tuple<int, double> temp = heap[n];
        heap[n] = heap[parent(n)];
        heap[parent(n)] = temp;
        n = parent(n);
    }
    if (heap.size() > max_relevant + 5000) {
        heap.resize(max_relevant);
        printf("OH NO!\n");
    }
}

tuple<int, double> Heap::delmin () {
    tuple<int, double> min = heap[0];
    heap[0] = heap.back();    
    heap.resize((heap.size() - 1));
    heapify(0);
    return min;
}

tuple<int, double> Heap::peekmin () {
    return heap[0];
}

int Heap::size () {
    return heap.size();
}

void Heap::heapify (int i) { // invariant, everything above, and below N are independent max heaps.
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

    // swap largest and top node.
    if (smallest != i) {
        tuple<int, double> temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        heapify(smallest);
    }
}

// utility functions to find indices.
int parent (int i) {
    return (i - 1) / 2;
}
int left (int i) {
    return 2 * i + 1;
}
int right (int i) {
    return 2 * i + 2;
}

// heap tests
int Heap::test_heap () {
    Heap h;
    h.insert(make_tuple(1, 0.2));
    h.insert(make_tuple(2, 0.1));
    h.insert(make_tuple(3, 1.6));
    if (get<0>(h.peekmin()) != 2) {
        printf("%i, %f A\n", get<0>(h.peekmin()), get<1>(h.peekmin()));
        return 1;
    }
    h.delmin();
    if (get<0>(h.peekmin()) != 1) {
        printf("%i, %f B\n", get<0>(h.peekmin()), get<1>(h.peekmin()));
        return 1;
    }
    h.delmin();
    if (get<0>(h.peekmin()) != 3) {
        printf("%i, %f C\n", get<0>(h.peekmin()), get<1>(h.peekmin()));
        return 1;
    }
    return 0;
}