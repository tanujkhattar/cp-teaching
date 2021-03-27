#include <iostream>
#include <vector>

using namespace std;
const int N = 2e5 + 10;
const int LOGN = 20;
int dist[N];
vector<int> g[N];
// LCA
int DP[LOGN][N];
void dfs(int x, int p) {
  DP[0][x] = p;
  for (auto y : g[x]) {
    if (y != p) {
      dist[y] = dist[x] + 1;
      dfs(y, x);
    }
  }
}
int lca(int x, int y) {
  if (dist[x] > dist[y]) swap(x, y);
  int d = dist[y] - dist[x];
  for (int i = 0; i < LOGN; i++) {
    if (d & (1 << i)) {
      y = DP[i][y];
    }
  }
  if (x == y) return x;
  for (int i = LOGN - 1; i >= 0; i--) {
    if (DP[i][x] != DP[i][y]) {
      x = DP[i][x];
      y = DP[i][y];
    }
  }
  return DP[0][x];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int n, q;
  cin >> n >> q;
  for (int i = 1; i < n; i++) {
    int x, y;
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  dfs(1, 1);
  for (int i = 1; i < LOGN; i++) {
    for (int x = 1; x <= n; x++) {
      DP[i][x] = DP[i - 1][DP[i - 1][x]];
    }
  }
  while (q--) {
    int x, y;
    cin >> x >> y;
    int LCA = lca(x, y);
    cout << (dist[x] + dist[y] - 2 * dist[LCA]) << "\n";
  }
}