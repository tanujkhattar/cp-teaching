// Author: Tanuj Khattar
// Accepted soluion for https://www.hackerrank.com/contests/world-codesprint-13/challenges/dynamic-trees
#include <iostream>
#include <set>

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
set<int> g[N];
int A[N], P[N], root[N], level[N], BLOCK[N], ans[N];
int n, q;
void dfs(int u) {
  for (auto w : g[u]) {
    // P[w] = u & BLOCK[w] == BLOCK[u];
    level[w] = level[u] + 1;
    ans[w] = ans[u] + A[w];
    root[w] = root[u];
    dfs(w);
  }
}
void process(int t) {
  // Build forest for each square root block
  int st = max(1, t * SQRT), en = min(n + 1, (t + 1) * SQRT);
  for (int i = st; i < en; i++)
    if (BLOCK[P[i]] != t || P[i] == i)
      level[i] = 0, root[i] = i, ans[i] = A[i], dfs(i);
  // done :)
}
int queryUp(int u, int p, int k) {
  int s = 0;
  while (root[u] != root[p]) {
    s += ans[u];
    if (s >= k) {
      s -= ans[u];
      p = root[u];
      break;
    }
    u = P[root[u]];
  }
  k -= s;
  while (u > p) {
    k -= A[u];
    if (!k) return u;
    u = P[u];
  }
  return u;
}
int lca(int a, int b) {
  if (level[a] > level[b]) swap(a, b);
  while (level[b] > level[a]) b = P[b];
  while (a != b) a = P[a], b = P[b];
  return a;
}
int query(int a, int b, int k) {
  int u = a, v = b;
  int su = 0, sv = 0;
  while (root[u] != root[v]) {
    if (v > u) {
      sv += ans[v];
      v = P[root[v]];
    } else {
      su += ans[u];
      u = P[root[u]];
    }
  }
  int LCA = lca(u, v);
  su += ans[u] - ans[LCA] + A[LCA];
  sv += ans[v] - ans[LCA];
  if (su + sv < k)
    return -1;
  else if (su >= k)
    return queryUp(a, LCA, k);
  else
    return queryUp(b, LCA, sv - (k - su) + 1);
}
void update(int x) {
  ans[x] = ans[x] - A[x];
  A[x] ^= 1;
  ans[x] = ans[x] + A[x];
  dfs(x);
}
int main() {
  scanf("%d %d", &n, &q);
  // 0:white 1:black
  for (int i = 1; i <= n; i++) scanf("%d", A + i);
  for (int i = 1; i <= n; i++) BLOCK[i] = i / SQRT;
  for (int i = 2; i <= n; i++) {
    scanf("%d", P + i);
    if (BLOCK[P[i]] == BLOCK[i]) {
      g[P[i]].insert(i);
    }
  }
  P[1] = 1;
  for (int i = 0; i * SQRT <= n; i++) process(i);
  while (q--) {
    char s[2];
    scanf("%s ", s);
    if (s[0] == 'T') {
      int x;
      scanf("%d", &x);
      update(x);
    } else if (s[0] == 'C') {
      int u, v;
      scanf("%d %d", &u, &v);
      bool ok = true;
      if (BLOCK[u] == BLOCK[P[u]]) {
        g[P[u]].erase(u);
        ok = false;
      }
      if (BLOCK[u] == BLOCK[v]) {
        g[v].insert(u);
        ok = false;
      }
      P[u] = v;
      if (ok) continue;
      if (BLOCK[P[u]] != BLOCK[u]) {
        ans[u] = A[u];
        root[u] = u;
        level[u] = 0;
        dfs(u);
      } else {
        ans[u] = ans[P[u]] + A[u];
        level[u] = level[P[u]] + 1;
        root[u] = root[P[u]];
        dfs(u);
      }
    } else {
      int u, v, k;
      scanf("%d %d %d", &u, &v, &k);
      printf("%d\n", query(u, v, k));
    }
  }
  return 0;
}