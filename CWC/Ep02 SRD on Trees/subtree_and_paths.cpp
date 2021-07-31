// Author: Tanuj Khattar
// Accepted soluion for https://www.hackerrank.com/challenges/subtrees-and-paths/problem
#include <iostream>
#include <vector>

using namespace std;

#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(std::string name, Arg1&& arg1) {
  std::cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(std::string names, Arg1&& arg1, Args&&... args) {
  auto comma = names.find(',');
  std::cerr << names.substr(0, comma) << " : " << arg1 << " | ";
  __f(names.substr(comma + 1), args...);
}
#else
#define trace(...)
#endif

// FILE *fin = freopen("in","r",stdin);
// FILE *fout = freopen("out","w",stdout);

const int N = int(1e5) + 10;
const int SQRT = 300;
vector<int> g[N];
vector<int> E[N / SQRT + 1];
int A[N], P[N], root[N], level[N], BLOCK[N], prefix_max[N], lazy[N / SQRT + 1];
int st[N], en[N], T;
int n, q;
void dfs(int x) {
  for (auto y : g[x]) {
    level[y] = level[x] + 1;
    prefix_max[y] = max(A[y], prefix_max[x]);
    root[y] = root[x];
    dfs(y);
  }
}
void process(int t) {
  // Process the forests.
  for (auto x : E[t])
    if (BLOCK[P[x]] != t || P[x] == x)
      level[x] = 0, root[x] = x, prefix_max[x] = A[x], dfs(x);
  // done :)
}
int query(int x, int y) {
  int ans = INT32_MIN;
  // Keep moving left in ETT array till both nodes are in the same tree.
  while (root[x] != root[y]) {
    if (st[x] > st[y]) {
      swap(x, y);
    }
    ans = max(ans, prefix_max[y] + lazy[BLOCK[y]]);
    y = P[root[y]];
  }
  // Iterate on x --> LCA and y --> LCA via brute force coz O(sqrt(N)) nodes.
  int b = BLOCK[x];
  if (level[x] > level[y]) swap(x, y);
  while (level[y] > level[x]) {
    ans = max(ans, A[y] + lazy[b]);
    y = P[y];
  }
  while (x != y) {
    ans = max(ans, max(A[x], A[y]) + lazy[b]);
    x = P[x];
    y = P[y];
  }
  return max(ans, A[x] + lazy[b]);
}
void update(int x, int val) {
  // Range update of val in ETT array from st[x] to en[x].
  // Update blocks of L & R by iterating over elements.
  int bL = st[x] / SQRT, bR = en[x] / SQRT;
  for (auto y : E[bL])
    if (st[y] >= st[x] && en[y] <= en[x]) A[y] += val;
  process(bL);
  if (bL == bR) return;
  for (auto y : E[bR])
    if (en[y] <= en[x]) A[y] += val;
  process(bR);
  // Lazy update on all blocks in between.
  for (int b = bL + 1; b < bR; b++) {
    lazy[b] += val;
  }
}
void dfs_ett(int x, int p) {
  st[x] = ++T;
  BLOCK[x] = st[x] / SQRT;
  E[BLOCK[x]].push_back(x);
  P[x] = p;
  for (auto y : g[x]) {
    if (y != p) {
      dfs_ett(y, x);
    }
  }
  en[x] = T;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  // Process the graph.
  dfs_ett(1, 1);
  // Make sure every node only has adjacent edges which lie in the same block.
  for (int x = 1; x <= n; x++) {
    g[x].clear();
  }
  for (int x = 2; x <= n; x++) {
    if (BLOCK[x] == BLOCK[P[x]]) {
      g[P[x]].push_back(x);
    }
  }
  // Square Root Decomposition
  for (int i = 0; i * SQRT <= n; i++) process(i);
  // Answer Queries.
  cin >> q;
  while (q--) {
    char s[5];
    scanf("%s ", s);
    if (s[0] == 'a') {
      int x, val;
      scanf("%d %d", &x, &val);
      update(x, val);
    } else if (s[0] == 'm') {
      int u, v;
      scanf("%d %d", &u, &v);
      printf("%d\n", query(u, v));
    }
  }
  return 0;
}