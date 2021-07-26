//Q[]: array containing k nodes of auxillary tree
//arr[] : arrival time of nodes
//anc(p,u) : returns true if p is ancestor of u
//VI tree[N] : final auxillary tree with O(k) nodes
bool cmp(int u,int v){return arr[u]<arr[v];}
int create_tree(){//return root of tree
  set<int> S;//get distinct nodes 
  REP(i,k)S.insert(Q[i]);k=0;for(auto it : S)Q[k++]=it;
  sort(Q,Q+k,cmp);int kk = k;//distinct initial nodes
  //add lca of adjacent pairs
  for(int i=0;i<kk-1;i++){int x = lca(Q[i],Q[i+1]);
    if(S.count(x))continue;Q[k++]=x;S.insert(x);
  }sort(Q,Q+k,cmp);stack<int> s;s.push(Q[0]);
  for(int i=1;i<k;i++){
    while(!anc(s.top(),Q[i]))s.pop();
    tree[s.top()].PB(Q[i]);tree[Q[i]].PB(s.top());
    s.push(Q[i]);}return Q[0];}
