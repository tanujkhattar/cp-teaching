int U[N],V[N],W[N],baseArray[N],DP[LOGN][N],level[N],sub[N];
int chainParent[N],chainHead[N],blen,chainNo[N],pos[N],nchain;
void HLD(int u,int ee){//edge list graph.graph is 1-based.
  baseArray[blen]=W[ee];pos[u]=blen;blen++;chainNo[u]=nchain;
  int sc=-1,mx=0;
  for(auto e : g[u]){
    if(e==ee)continue;
    int w = adj(u,e);
    if(sub[w]>mx)sc = e,mx = sub[w];
  }if(sc==-1)return;
  HLD(adj(u,sc),sc);
  for(auto e : g[u]){
    if(e==ee||e==sc)continue;
    int w = adj(u,e);nchain++;
    chainParent[nchain]=u;chainHead[nchain]=w;
    HLD(w,e);}}
void dfs(int u,int ee){sub[u]=1;
  for(auto e : g[u]){if(e==ee)continue;
    int w=adj(u,e);level[w]=level[u]+1;
    DP[0][w]=u;dfs(w,e);sub[u]+=sub[w];
  }}void preprocess(){DP[0][1]=1;dfs(1,0);
  chainHead[nchain]=chainParent[nchain]=1;HLD(1,0);}
