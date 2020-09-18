// Copyright Banu Miruna-Elena, 2020
#include <bits/stdc++.h>
using namespace std;

const int kNmax = 100005;

class Task {
 public:
    void solve() {
        read_input();
        get_result();
    }

 private:
    int n;
    int m;
    int k;
    // Set Robin's position to node 1
    int robin;
    vector<int> perms;
    vector<int> lords;
    vector<int> adj[kNmax];
    // Use an unordered map to store each node's
    // positionin the permutation
    unordered_map<int, int> priority;

    void read_input() {
        ifstream fin("p1.in");
        robin = 1;
        fin >> n >> m >> k;

        lords.push_back(0);
        for (int i = 1, y; i <= k; ++i) {
            fin >> y;
            lords.push_back(y);
        }

        perms.push_back(0);
        for (int i = 1, p; i <= n - 1; ++i) {
            fin >> p;
            perms.push_back(p);
            priority.insert({p, i});
        }

        for (int i = 1, u, v; i <= m; i++) {
            fin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        fin.close();
    }

    // Traverse the graph using DFS
    // Use middle as reference for the lower limit
    // of priority for the used nodes
    bool computeDFS(int mid) {
        // Initialize the visited vector with 0
        vector<int> visited(n + 1, 0);
        dfs(robin, visited, mid);
        return check_validity(visited);
    }

    // Recursive function for dfs that checks for visited nodes
    // with priority higher than midd
    void dfs(int node, vector<int> &visited, int mid) {
        visited[node] = 1;
        for (auto &it : adj[node]) {
            if (!visited[it] && priority[it] >= mid) {
                dfs(it, visited, mid);
            }
        }
    }

    // Check if none of the lords have access to Robin's location
    bool check_validity(vector<int> visited) {
        for (int i = 1; i <= k; ++i) {
            if (visited[lords[i]] == 1) {
                return false;
            }
        }
        return true;
    }

    // Use binary search to find the number of blocked towns
    int find_node(int l, int r) {
        if (l <= r) {
            int mid = l + (r - l) / 2;

            // If there is only one node left
            if (r == 1) {
                return r;
            }

            // If the current node is a valid node for Robin's
            // protection
            if (computeDFS(mid)) {
                // Look to the left of the node
                return find_node(l, mid - 1);
            } else {
                // If the current node is invalid but the next one
                // is valid, then the current node is the last town
                // that needs to be blocked
                if (computeDFS(mid + 1)) {
                    return mid;
                }
                // Otherwise, look to the right of the node
                return find_node(mid + 1, r);
            }
        }
        return -1;
    }

    void get_result() {
        ofstream fout("p1.out");
        fout << find_node(robin, n);
        fout.close();
    }
};

int main() {
    Task *task = new Task();
    task->solve();
    delete task;
    return 0;
}
