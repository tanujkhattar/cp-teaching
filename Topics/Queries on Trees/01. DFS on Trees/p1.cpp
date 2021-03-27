#include <iostream>
#include <vector>

using namespace std;
const int N = 2e5 + 10;
// Representing a weighted tree using an adjacency list.
vector<pair<int, int>> g[N];
// Properties to calculate.
int level[N], par[N], sz[N];
int64_t dist[N], sum[N];
// DFS on Rooted Tree.
void dfs(int x, int p) {
  par[x] = p;
  sz[x] = 1;
  for (auto [y, w] : g[x]) {
    if (y == p) continue;
    level[y] = level[x] + 1;
    dist[y] = dist[x] + w;
    dfs(y, x);
    sz[x] += sz[y];
    sum[x] += sum[y] + w;
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int n;
  cin >> n;
  for (int i = 1; i < n; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    g[x].emplace_back(y, w);
    g[y].emplace_back(x, w);
  }
  int root = 1;
  cin >> root;
  dfs(root, root);
  for (int i = 1; i <= n; i++) {
    cout << sz[i] << " ";
  }
}