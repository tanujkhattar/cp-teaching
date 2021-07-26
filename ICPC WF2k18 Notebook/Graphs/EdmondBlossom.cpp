//- graph stored in adj : 0-based. O(n^3) per call
//- match[i] stores vertex matched to i. -1 if unmatched
vector<int> adj[MAXN];
int p[MAXN], base[MAXN], match[MAXN];
int lca(int nodes, int u, int v){
  vector<bool> used(nodes);
  for (;;) {u = base[u];used[u] = true;
    if (match[u] == -1) {break;}
    u = p[match[u]];}
  for (;;) {v = base[v];if (used[v]) {return v;}
    v = p[match[v]];}}
void mark_path(vector<bool> &blossom,int u,int b,int child){
  for (; base[u] != b; u = p[match[u]]) {
    blossom[base[u]] = true;
    blossom[base[match[u]]] = true;
    p[u] = child;child = match[u];}}
int find_path(int nodes, int root) {
  vector<bool> used(nodes);
  for (int i = 0; i < nodes; ++i){p[i] = -1;base[i] = i;}
  used[root] = true;queue<int> q;q.push(root);
  while (!q.empty()) { int u = q.front();q.pop();
    for (int j = 0; j < SZ(adj[u]); j++) {int v = adj[u][j];
      if (base[u] == base[v] || match[u] == v) {continue;}
      if (v == root || (match[v] != -1 && p[match[v]] != -1)) {
        int curr_base = lca(nodes, u, v);
        vector<bool> blossom(nodes);
        mark_path(blossom, u, curr_base, v);
        mark_path(blossom, v, curr_base, u);
        for (int i = 0; i < nodes; i++) {
          if (blossom[base[i]]) {base[i] = curr_base;
            if (!used[i]) {used[i] = true;q.push(i);}}}
      } else if (p[v] == -1) {p[v] = u;
        if (match[v] == -1) {return v;}
          v = match[v];used[v] = true;q.push(v);
      }}}return -1;}
int edmonds(int nodes) {
  for (int i = 0; i < nodes; i++) {match[i] = -1;}
  for (int i = 0; i < nodes; i++) {
    if (match[i] == -1) { int u, pu, ppu;
      for (u = find_path(nodes, i); u != -1; u = ppu) {
        pu = p[u]; ppu = match[pu];match[u] = pu; 
        match[pu] = u;}}}int matches = 0;
  for (int i = 0; i < nodes; i++) {
    if (match[i] != -1) {matches++;
    }}return matches/2;}
