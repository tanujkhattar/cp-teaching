#include <iostream>
#include <vector>

using namespace std;
const int N = 2e5 + 10;
const int M = 2 * N;
// Representing an unrooted weighted tree 
// using an edge list, we 2 directed edges 
// for every edge. pos[e] represents 
// position of e in the edge list of U[e].
int U[M], V[M], W[M], pos[M];
vector<int> g[N];
void add_edge(int e, int x, int y, int w) {
  U[e] = x;
  V[e] = y;
  W[e] = w;
  pos[e] = g[x].size();
  g[x].push_back(e);
}
// Properties to calculate for every edge.
int far[M];
// Additional information.
int vis[M];
vector<int> prefix_max[N], suffix_max[N];
int val_or_zero(vector<int>& v, int idx) {
  if (idx >= 0 && idx < (int)v.size()) return v[idx];
  return 0;
}
void recompute_prefix_suffix_max(int x) {
  int n = g[x].size();
  prefix_max[x].resize(n);
  suffix_max[x].resize(n);
  for (int i = 0, j = n - 1; i < n; i++, j--) {
    prefix_max[x][i] = max(val_or_zero(prefix_max[x], i - 1), far[g[x][i]]);
    suffix_max[x][j] = max(val_or_zero(suffix_max[x], j + 1), far[g[x][j]]);
  }
}

void dfs_brute_force(int xe) {
  if (vis[xe]) return;
  vis[xe] = 1;
  for (auto ye : g[V[xe]]) {
    if (ye != (xe ^ 1)) {
      dfs(ye);
      far[xe] = max(far[xe], far[ye] + W[ye]);
    }
  }
}

// DFS on UnRooted Tree.
void dfs(int x, int pe) {
  if (!vis[x]) {
    // Visiting x for the first time.
    // Explore all edges except parent edge.
    vis[x] = (pe ^ 1);
    for (auto e : g[x])
      if (e != vis[x]) dfs(V[e], e);
    recompute_prefix_suffix_max(x);
  } else if (vis[x] > 1) {
    // Visiting x for the second time.
    // Only 1 outgoing edge would be unexplored.
    dfs(V[vis[x]], vis[x]);
    vis[x] = 1;
    recompute_prefix_suffix_max(x);
  }
  if (pe) {
    int idx = pos[pe ^ 1];
    far[pe] = max(val_or_zero(prefix_max[x], idx - 1),
                  val_or_zero(suffix_max[x], idx + 1)) +
              W[pe];
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int n;
  cin >> n;
  for (int i = 1; i < n; i++) {
    int x, y, w = 1;
    // cin >> x >> y >> w;
    cin >> x >> y;
    add_edge(2 * i, x, y, w);
    add_edge(2 * i + 1, y, x, w);
  }
  for (int i = 1; i <= n; i++) {
    if (vis[i] != 1) {
      dfs(i, 0);
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << suffix_max[i][0] << " ";
  }
}