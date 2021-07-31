// Accepted solution for
// https://ioi2018.jp/wp-content/tasks/contest1/werewolf.pdf
// Submitted at https://contest.yandex.com/ioi/contest/8916/standings/ 
#include <assert.h>

#include <algorithm>
#include <functional>
#include <iostream>
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

const int N = 6e5 + 10;
const int LOGN = 22;

namespace DS {
// Given two permutations A and B, of [1..N], answer range queries of the form:
// [L1, R1], [L2, R2]:  Is there a common vertex between A[L1...R1] and
// B[L2...R2]? 
// Let pos[i] = position of A[i] in array B. The query reduces to 
// L1 R1 L2 R2: Tell number of i s.t. L1 <= i <= R1 and L2 <= pos[i] <= R2.
#define lc (x << 1)
#define rc (x << 1) | 1
#define all(x) x.begin(), x.end()
int pos[N], n;
vector<int> ST[4 * N];
void build_pos(int A[], int B[]) {
  vector<int> temp_pos(n + 1, 0);
  for (int i = 1; i <= n; i++) temp_pos[B[i]] = i;
  for (int i = 1; i <= n; i++) pos[i] = temp_pos[A[i]];
}
void build_st(int l = 1, int r = n + 1, int x = 1) {
  if (l == r - 1) return void(ST[x].push_back(pos[l]));
  int m = (l + r) >> 1;
  build_st(l, m, lc);
  build_st(m, r, rc);
  ST[x].resize(r - l);
  merge(all(ST[lc]), all(ST[rc]), ST[x].begin());
}
void build(int n, int A[], int B[]) {
  DS::n = n;
  build_pos(A, B);
  build_st();
}
int query(int L, int R, int D, int U, int l = 1, int r = n + 1, int x = 1) {
  if (r <= L || l >= R) return 0;
  if (l >= L && r <= R) {
    return upper_bound(all(ST[x]), U) - lower_bound(all(ST[x]), D);
  }
  int m = (l + r) >> 1;
  return query(L, R, D, U, l, m, lc) + query(L, R, D, U, m, r, rc);
}
}  // namespace DS

int U[N], V[N], W[2][N];
int dsu[N], root[N], E[N], tree[2][N][2];
int DP[2][LOGN][N], T[2], st[2][N], en[2][N], ett[2][N];
int build_tree(int t, int n, int m) {
  // sort edges based on tree type.
  sort(&E[1], &E[m + 1],
       [t](int e1, int e2) { return t ^ (W[t][e1] < W[t][e2]); });
  function<int(int)> f = [&](int x) {
    return dsu[x] = (x == dsu[x] ? x : f(dsu[x]));
  };
  // Assumes nodes are numbered from 1..n and edges from n+1..n+m+1
  for (int i = 1; i <= n; i++) {
    dsu[i] = root[i] = i;
  }
  int tree_root = 0;
  // Builds the tree bottom-up.
  for (int i = 1; i <= m; i++) {
    int e = E[i], x = f(U[e]), y = f(V[e]);
    if (x == y) continue;
    // Attach root[x], root[y] as left & right children of e.
    tree[t][e][0] = root[x];
    tree[t][e][1] = root[y];
    // Merge components of x & y and make e the new root.
    dsu[x] = y;
    root[y] = e;
    tree_root = e;
  }
  return tree_root;
}

void dfs(int t, int x, int p) {
  DP[t][0][x] = p;
  for (int i = 1; i < LOGN; i++) DP[t][i][x] = DP[t][i - 1][DP[t][i - 1][x]];
  st[t][x] = T[t];
  for (int c = 0; c < 2; c++) {
    if (tree[t][x][c]) {
      auto y = tree[t][x][c];
      dfs(t, y, x);
    }
  }
  if (!tree[t][x][0]) ett[t][++T[t]] = x;
  en[t][x] = T[t];
}

int query(int s, int e, int l, int r) {
  // Find the farthest ancestors for s & e satisfying weight constraints
  // For s, we want to find subtree in T2 ignoring 0...l-1
  // For e, we want to find subtree in T1 ignoring r+1..n
  for (int i = LOGN - 1; i >= 0; i--) {
    if (W[1][DP[1][i][s]] >= l) s = DP[1][i][s];
    if (W[0][DP[0][i][e]] <= r) e = DP[0][i][e];
  }
  // Query for all leaf nodes in the subtree of this ancestor.
  return DS::query(st[0][e] + 1, en[0][e] + 1, st[1][s] + 1, en[1][s]) > 0;
}

std::vector<int> check_validity(int n, std::vector<int> cX, std::vector<int> cY,
                                std::vector<int> cS, std::vector<int> cE,
                                std::vector<int> cL, std::vector<int> cR) {
  int m = cX.size();
  for (int i = n + 1; i <= n + m; i++) {
    U[i] = ++cX[i - n - 1];
    V[i] = ++cY[i - n - 1];
    if (U[i] > V[i]) swap(U[i], V[i]);
    W[0][i] = V[i];
    W[1][i] = U[i];
    E[i - n] = i;
  }
  for (int t = 0; t < 2; t++) {
    int tree_root = build_tree(t, n, m);
    dfs(t, tree_root, tree_root);
    assert(T[t] == n);
  }
  DS::build(n, ett[0], ett[1]);
  int q = cS.size();
  std::vector<int> A(q);
  for (int i = 0; i < q; ++i) {
    A[i] = query(++cS[i], ++cE[i], ++cL[i], ++cR[i]);
  }
  return A;
}