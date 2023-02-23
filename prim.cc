#include <iostream>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

const int MAXN = 100000; // maximum number of nodes
vector<pair<int, int>> adj[MAXN]; // adjacency list of the graph
bool visited[MAXN]; // keeps track of nodes already in the tree

// A custom comparison function for the priority queue
struct Compare {
    bool operator() (const pair<int, int>& a, const pair<int, int>& b) const {
        return a.second > b.second;
    }
};

// Prim's algorithm using a binary minheap
void prim(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> minheap;
    int dist[MAXN]; // keeps track of the minimum distance to each node
    fill(dist, dist+MAXN, numeric_limits<int>::max()); // initialize distances to infinity
    dist[start] = 0;
    minheap.push({start, 0});

    while (!minheap.empty()) {
        int u = minheap.top().first;
        minheap.pop();

        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        for (auto& [v, weight] : adj[u]) {
            if (!visited[v] && weight < dist[v]) {
                dist[v] = weight;
                minheap.push({v, weight});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        adj[u].push_back({v, weight});
        adj[v].push_back
