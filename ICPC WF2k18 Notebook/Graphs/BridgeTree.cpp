VI tree[N],g[N];bool isbridge[M];
int U[M],V[M],vis[N],arr[N],T,dsu[N];
int f(int x){return dsu[x]=(dsu[x]==x?x:f(dsu[x]));}
void merge(int a,int b){dsu[f(a)]=f(b);}
int dfs0(int u,int edge){ //mark bridges
  vis[u]=1;arr[u]=T++;int dbe=arr[u];
  for(auto e : g[u]){int w = adj(u,e);
    if(!vis[w])dbe = min(dbe,dfs0(w,e));
    else if(e!=edge)dbe = min(dbe,arr[w]);
  }if(dbe==arr[u]&&edge!=-1)isbridge[edge]=true;
  else if(edge!=-1)merge(U[edge],V[edge]);
  return dbe;
}void buildBridgeTree(int n,int m){
  for(int i=1;i<=n;i++)dsu[i]=i;int x,y;
  for(int i=1;i<=n;i++)if(!vis[i])dfs0(i,-1);
  for(int i=1;i<=m;i++)if((x=f(U[i]))!=(y=f(V[i])))
      tree[x].PB(y),tree[y].PB(x);}
