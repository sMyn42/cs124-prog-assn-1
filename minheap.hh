#include <cassert>
#include <cstdlib>
#include <cinttypes>
#include <cstdio>
#include <vector>
#include <tuple>
using namespace std;

class Heap {
    private:
        vector< tuple<int, double> > heap;
        int max_relevant;
    public:
        Heap (int mr);
        Heap ();
        void insert (tuple<int, double> v);
        tuple<int, double> delmin ();
        tuple<int, double> peekmin ();
        void heapify (int i);
        int test_heap ();
        int size ();
};
int parent (int i);
int left (int i);
int right (int i);