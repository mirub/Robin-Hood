// Copyright Banu Miruna-Elena, 2020
#include <bits/stdc++.h>
using namespace std;
#define oo (1 << 30)

const int kNmax = 100005;

class Task {
 public:
    void solve() {
        read_input();
        print_output();
    }

 private:
    int n;
    int m;
    int source;
    int destination;
    vector<pair<int, int>> adj[kNmax];
    // Minimum distances from source to every node
    vector<int> d;
    // The number of edges towards each node
    // for the topological sort
    vector<int> inDegree;

    void read_input() {
        ifstream fin("p2.in");
        fin >> n >> m;
        fin >> source >> destination;
        inDegree = vector<int>(n + 1, 0);
        for (int i = 1, x, y, e; i <= m; i++) {
            fin >> x >> y >> e;
            adj[x].push_back({y, e});
            ++inDegree[y];
        }
        fin.close();
    }

    // Use Kahn's algorithm to do the topsort
    vector<int> computeBFS() {
        queue<int> q;
        vector<int> topsort;

        // If the node does not have any incoming edges
        // add it to the queue
        for (int i = 1; i <= n; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        // Compute the topsort
        while (!q.empty()) {
            int node = q.front();
            q.pop();

            topsort.push_back(node);

            for (auto &it : adj[node]) {
                // Delete the edge
                --inDegree[it.first];

                // Add any node with inDegree == 0 to
                // the queue
                if (inDegree[it.first] == 0) {
                    q.push(it.first);
                }
            }
        }

        // Check if the graph has more than one connected
        // component
        bool isValid = true;
        for (int i = 1; i <= n; ++i) {
            if (inDegree[i] > 0) {
                isValid = false;
                break;
            }
        }

        // If there is only one component, return topsort
        // Otherwise return an empty vector
        if (isValid) {
            return topsort;
        } else {
            return {};
        }
    }

    // Compute the shortest path using the topsort order
    // of the nodes since it is more efficient this way
    // on directed acyclic graphs
    void get_shortest_path(vector<int> &d, int source) {
        vector<int> topsort;
        topsort = computeBFS();

        d = vector<int>(n + 1, oo);
        d[source] = 0;

        // Find the shortest distances
        for (auto &node : topsort) {
            for (auto &adj_node : adj[node]) {
                if (d[adj_node.first] > d[node] + adj_node.second) {
                    d[adj_node.first] = d[node] + adj_node.second;
                }
            }
        }
    }

    void print_output() {
        ofstream fout("p2.out");
        get_shortest_path(d, source);
        fout << d[destination];
        fout.close();
    }
};

int main() {
    Task *task = new Task();
    task->solve();
    delete task;
    return 0;
}
