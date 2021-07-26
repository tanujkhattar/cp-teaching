// Accepted solution for https://www.codechef.com/problems/TULIPS
#include <assert.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>

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

const int N = 2e5 + 10;
const int LOGN = 20;
int U[N], V[N], W[N];
int dsu[N], root[N], E[N], tree[N][2];
int DP[LOGN][N], T, st[N], en[N];

namespace DS {
const int SQRT = 500;
map<int, int> mp[N / SQRT];
int val[N], bl[N];
int st[N / SQRT], en[N / SQRT], block_val[N / SQRT];
void build(int n) {
  for (int i = 1; i <= n; i++) {
    bl[i] = i / SQRT;
    if (i == 1 || bl[i] != bl[i - 1]) {
      st[bl[i]] = i;
    }
    en[bl[i]] = i;
    mp[bl[i]][1]++;
    val[i] = block_val[bl[i]] = 1;
  }
}
int query_ind(int L, int R, int d, int x) {
  int ret = 0;
  int b = bl[L];
  for (int i = L; i <= R; i++) {
    int curr_val = max(block_val[b], val[i]);
    val[i] = d + x;
    ret += curr_val <= d;
    mp[b][curr_val]--;
    mp[b][val[i]]++;
  }
  return ret;
}
int query_blocks(int bl, int br, int d, int x) {
  int ret = 0;
  for (int b = bl; b <= br; b++) {
    for (auto& it : mp[b]) {
      if (it.first <= d) {
        ret += it.second;
      } else
        break;
    }
    mp[b].clear();
    mp[b][d + x] = en[b] - st[b] + 1;
    block_val[b] = d + x;
  }
  return ret;
}
int query(int L, int R, int d, int x) {
  if (bl[L] == bl[R]) {
    return query_ind(L, R, d, x);
  } else {
    return query_ind(L, en[bl[L]], d, x) +
           query_blocks(bl[L] + 1, bl[R] - 1, d, x) +
           query_ind(st[bl[R]], R, d, x);
  }
}

}  // namespace DS

int build_tree(int n) {
  // sort edges in increasing order for max tree.
  sort(&E[1], &E[n], [](int e1, int e2) { return W[e1] < W[e2]; });
  function<int(int)> f = [&](int x) {
    return dsu[x] = (x == dsu[x] ? x : f(dsu[x]));
  };
  // Assumes nodes are numbered from 1..n and edges from n+1..2n-1
  for (int i = 1; i <= n; i++) { dsu[i] = root[i] = i;}
  // Builds the tree bottom-up.
  for (int i = 1; i < n; i++) {
    int e = E[i], x = f(U[e]), y = f(V[e]);
    // Attach root[x], root[y] as left & right children of e.
    tree[e][0] = root[x]; tree[e][1] = root[y];
    // Merge components of x & y and make e the new root.
    dsu[x] = y; root[y] = e;
  }
  return E[n - 1];
}
void dfs(int x, int p) {
  DP[0][x] = p;
  for (int i = 1; i < LOGN; i++) DP[i][x] = DP[i - 1][DP[i - 1][x]];
  bool is_leaf = !tree[x][0];
  st[x] = T;
  for (int c = 0; c < 2; c++) {
    if (tree[x][c]) {
      auto y = tree[x][c];
      dfs(y, x);
    }
  }
  en[x] = is_leaf ? ++T : T;
}

int query(int d, int u, int k, int x) {
  // Find the farthest ancestor with edge weight <= k.
  for (int i = LOGN - 1; i >= 0; i--)
    if (W[DP[i][u]] <= k) u = DP[i][u];
  // Query for all leaf nodes in the subtree of this ancestor.
  return DS::query(st[u] + 1, en[u], d, x);
}
void reset(int n) {
  T = 0;
  for (int i = 1; i < 2 * n; i++) {
    tree[i][0] = tree[i][1] = 0;
  }
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n; scanf("%d", &n);
    for (int i = n + 1; i < 2 * n; i++) {
      scanf("%d %d %d", U + i, V + i, W + i);
      E[i - n] = i;
    }
    int tree_root = build_tree(n);
    dfs(tree_root, tree_root);
    assert(T == n);
    DS::build(n);
    int q, x;
    scanf("%d %d", &q, &x);
    while (q--) {
      int d, u, k;
      scanf("%d %d %d", &d, &u, &k);
      printf("%d\n", query(d, u, k, x));
    }
    reset(n);
  }
}