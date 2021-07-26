VI g[N];int sub[N],nn,U[N],V[N],done[N];
void dfs1(int u,int p){
  sub[u]=1;nn++;
  for(auto e:g[u]){
    int w = adj(u,e);
    if(w!=p && !done[e])
      dfs1(w,u),sub[u]+=sub[w];}}
int dfs2(int u,int p){
  for(auto e:g[u]){
    if(done[e])continue;
    int w = adj(u,e);
    if(w!=p && sub[w]>nn/2)
      return dfs2(w,u);
  }return u;}
void decompose(int root,int p){
  nn=0;dfs1(root,root);root=dfs2(root,root);
  if(p==-1)p=root;//fuck centroid :)
  for(auto e:g[root]){
    if(done[e])continue;
    done[e]=1;int w = adj(root,e);
    decompose(w,root);}}
