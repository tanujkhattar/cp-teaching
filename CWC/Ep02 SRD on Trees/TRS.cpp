// Author: Tanuj Khattar
// Accepted soluion for https://www.codechef.com/problems/TRS
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(string name, Arg1&& arg1) {
  cerr << name << " : " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(string names, Arg1&& arg1, Args&&... args) {
  auto comma = names.find(',');
  cerr << names.substr(0, comma) << " : " << arg1 << " | ";
  __f(names.substr(comma + 1), args...);
}
#else
#define trace(...)
#endif

const int N = 1e5 + 10;
const int SQRT = 200;
const int LOGN = 17;
vector<int> g[N];
// For LCA.
int dp[LOGN + 1][N], st[N], en[N], T;
// For Supernode Tree.
int head[N], par[N], level[N], block[N];
bool is_spcl[N];
// For queries & updates.
int64_t val[N], block_add[2 * N / SQRT], blen;
multiset<int64_t> block_vals[2 * N / SQRT];
// Build Supernode Tree.
inline int dfs(int x, int p = 0) {
  par[x] = head[x] = dp[0][x] = p;
  for (int i = 1; i <= LOGN; i++) dp[i][x] = dp[i - 1][dp[i - 1][x]];
  level[x] = level[p] + 1; st[x] = ++T;
  bool seen_spcl = false, is_sqrt_node = (level[x] % SQRT) == 0;
  is_spcl[x] = !p;
  int ret = 0;
  for (auto y : g[x]) {
    if (y == p) continue;
    int w = dfs(y, x);
    if (!w) continue;
    is_spcl[x] |= is_sqrt_node || (seen_spcl && is_spcl[w]);
    seen_spcl |= is_spcl[w];
    ret = w;
  }
  if (is_spcl[x]) head[x] = x;
  en[x] = ++T;
  return (is_spcl[x] || is_sqrt_node) ? x : ret;
}
inline int f(int x) { return head[x] = (head[x] == x ? x : f(head[x])); }
inline void build_supernode_tree(int n, int root = 1) {
  level[0] = -1; T = 0; blen = 0;
  dfs(root);
  for (int x = 1; x <= n; x++) {
    head[x] = f(x);
    if (!is_spcl[x]) continue;
    block[x] = ++blen;
    block_add[blen] = 0;
    block_vals[blen].clear();
    for (int y = x; y && ((y == x) ^ !is_spcl[y]); y = par[y]) {
      block[y] = blen;
      block_vals[blen].insert(val[y]);
    }
  }
}
inline int anc(int p, int x) { return st[x] >= st[p] && en[x] <= en[p]; }
inline int lca(int x, int y) {
  if (anc(x, y)) return x;
  if (anc(y, x)) return y;
  for (int i = LOGN; i >= 0; i--)
    if (dp[i][x] && !anc(dp[i][x], y)) x = dp[i][x];
  return dp[0][x];
}
// Update
inline void update_up(int x, int p, int64_t add) {
  while (x != p) {
    int b = block[x];
    if (is_spcl[x] && level[head[par[x]]] >= level[p]) {
      block_add[b] += add;
      x = head[par[x]];
    } else {
      if (b) block_vals[b].erase(block_vals[b].find(val[x]));
      val[x] += add;
      if (b) block_vals[b].insert(val[x]);
      x = par[x];
    }
  }
}
inline void update(int x, int y, int64_t add) {
  int LCA = lca(x, y);
  update_up(x, LCA, add);
  update_up(y, par[LCA], add);
}
// Query
const int64_t INF = 1e18;
inline int64_t min_op(int64_t x, int64_t y, int64_t min_val = -INF) {
  return (y >= min_val && y < x) ? y : x;
}
inline int64_t query_up(int x, int p, int64_t min_val) {
  auto ans = INF;
  while (x != p) {
    int b = block[x];
    if (is_spcl[x] && level[head[par[x]]] >= level[p]) {
      auto it = block_vals[b].lower_bound(min_val - block_add[b]);
      if (it != block_vals[b].end()) ans = min(ans, *it + block_add[b]);
      x = head[par[x]];
    } else {
      ans = min_op(ans, val[x] + block_add[b], min_val);
      x = par[x];
    }
  }
  return ans;
}
inline int64_t query(int x, int y, int64_t min_val) {
  int LCA = lca(x, y);
  return min(query_up(x, LCA, min_val), query_up(y, par[LCA], min_val));
}
// done :)
inline void reset(int n) {
  for (int i = 0; i <= n; i++) {
    g[i].clear();
  }
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%lld", val + i);
    for (int i = 1; i < n; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      g[x].push_back(y);
      g[y].push_back(x);
    }
    build_supernode_tree(n);
    while (q--) {
      int tp, u, v;
      int64_t w;
      scanf("%d %d %d %lld", &tp, &u, &v, &w);
      if (tp == 1) update(u, v, w);
      else {
        auto ans = query(u, v, w);
        printf("%lld\n", ans == INF ? -1 : ans);
      }
    }
    reset(n);
  }
}