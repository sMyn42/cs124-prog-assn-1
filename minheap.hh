#include <cassert>
#include <cstdlib>
#include <cinttypes>
#include <cstdio>
#include <vector>
using namespace std;

struct node {
    double value;
    node* left;
    node* right;
    node* parent;
};

class heap {
    public:
        node root;
};