// https://www.spoj.com/problems/DISQUERY/
// Accepted solution using Edge Decomposition Tree
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>

using namespace std;

const int N = 2e5 + 10;
const int LOGN = 20;
int U[N], V[N], W[N];
int dsu[2][N], root[2][N], E[2][N], tree[2][N][2];
int DP[2][LOGN][N], level[2][N];

int build_tree(int n, int E[N], int dsu[N], int root[N], int tree[N][2]) {
  function<int(int)> f = [&](int x) {
    return dsu[x] = (x == dsu[x] ? x : f(dsu[x]));
  };
  for (int i = 1; i <= n; i++) {
    dsu[i] = root[i] = i;
  }
  for (int i = 1; i < n; i++) {
    int e = E[i], x = f(U[e]), y = f(V[e]);
    tree[e][0] = root[x];
    tree[e][1] = root[y];
    dsu[x] = y;
    root[y] = e;
  }
  return E[n - 1];
}
void process_tree(int root, int tree[N][2], int DP[LOGN][N], int level[N]) {
  queue<int> Q;
  Q.push(root);
  for (int i = 0; i < LOGN; ++i) DP[i][root] = root;
  while (!Q.empty()) {
    auto x = Q.front();
    Q.pop();
    for (int c = 0; c < 2; ++c) {
      if (tree[x][c]) {
        int y = tree[x][c];
        level[y] = level[x] + 1;
        DP[0][y] = x;
        for (int i = 1; i < LOGN; i++) {
          DP[i][y] = DP[i - 1][DP[i - 1][y]];
        }
        Q.push(y);
      }
    }
  }
}
int lca(int x, int y, int level[N], int DP[LOGN][N]) {
  if (level[x] > level[y]) swap(x, y);
  int d = level[y] - level[x];
  for (int i = LOGN - 1; i >= 0; i--) {
    if ((1 << i) & d) {
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
  int n;
  scanf("%d", &n);
  for (int i = n + 1; i < 2 * n; i++) {
    scanf("%d %d %d", U + i, V + i, W + i);
    E[0][i - n] = E[1][i - n] = i;
  }
  sort(&E[0][1], &E[0][n], [](int e1, int e2) { return W[e1] > W[e2]; });
  sort(&E[1][1], &E[1][n], [](int e1, int e2) { return W[e1] < W[e2]; });
  for (int i = 0; i < 2; i++) {
    int tree_root = build_tree(n, E[i], dsu[i], root[i], tree[i]);
    process_tree(tree_root, tree[i], DP[i], level[i]);
  }
  int k;
  scanf("%d", &k);
  while (k--) {
    int x, y;
    scanf("%d %d", &x, &y);
    int e[2];
    for (int i = 0; i < 2; i++) {
      e[i] = lca(x, y, level[i], DP[i]);
    }
    printf("%d %d\n", W[e[0]], W[e[1]]);
  }
}