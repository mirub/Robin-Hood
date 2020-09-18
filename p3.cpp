// Copyright Banu Miruna-Elena, 2020
#include <bits/stdc++.h>

#define NMAX 100010
#define oo (1 << 30)
#define NO_PARENT (-1)
#define MIN_ENERGY 0

using namespace std;

class Task {
 public:
  void solve() {
    read_input();
    print_output();
  }

 private:
  int n, m;
  int robin;
  double energy;
  vector<pair<int, int>> adj[NMAX];
  // Priority queue implemented as max-heap by default
  priority_queue<pair<double, int>, vector<pair<double, int>>> pq;
  // The max energies Robin Hood has upon reaching any node
  vector<double> e;
  // The parent node for each node on max energy roads
  vector<int> p;

  void read_input() {
    ifstream fin("p3.in");
    fin >> n >> m >> energy;
    e.resize(n + 1);
    p.resize(n + 1);
    // Set the starting node to 1
    robin = 1;
    for (int i = 1, x, y, pr; i <= m; ++i) {
      fin >> x >> y >> pr;
      adj[x].push_back({y, pr});
    }
    fin.close();
  }

  void get_result() { Dijkstra(robin, e, p); }

  void Dijkstra(int source, vector<double> &e, vector<int> &p) {
    // Suppose no node can be reached
    for (int i = 1; i <= n; ++i) {
      // Set maximum energy to 0
      e[i] = MIN_ENERGY;
      // Set parent to 0
      p[i] = NO_PARENT;
    }

    // The parent node to the source is 0
    p[source] = 0;
    // The energy in the beginning is 0
    e[source] = energy;

    // Add the starting node to the priority queue
    pq.push({e[source], source});

    while (!pq.empty()) {
      auto entry = pq.top();
      pq.pop();

      // Get the nde index
      int node = entry.second;

      for (auto &edge : adj[node]) {
        int neighbour = edge.first;
        int cost_edge = edge.second;

        // Calculate the new possible energy
        double aux_energy = (double) e[node] * (1 - (((double)cost_edge)/100));

        // If the energy spent is lower, then choose this way
        if (e[neighbour] < aux_energy) {
          // Update the energy
          e[neighbour] = aux_energy;
          // Update the parent
          p[neighbour] = node;
          // Add the node to the queue
          pq.push({e[neighbour], neighbour});
        }
      }
    }
  }

  vector<int> rebuild_path(int node, vector<int> &p) {
    // If the node cannot be reaached
    if (p[node] == NO_PARENT) {
      return vector<int>();
    }
    vector<int> path;

    // So long as the node has a parent
    while (node != 0) {
      path.push_back(node);
      node = p[node];;
    }

    // The path constructed is node -> ... -> parent
    // but the result needs to be parent -> ... -> node
    reverse(path.begin(), path.end());

    return path;
  }

  void print_output() {
    ofstream fout("p3.out");
    get_result();
    fout << setprecision(15) << e[n] << '\n';
    vector<int> path = rebuild_path(n, p);
    for (auto &it : path) {
        fout << it << " ";
    }
    fout.close();
  }
};

int main() {
  Task *task = new Task();
  task->solve();
  delete task;

  return 0;
}
