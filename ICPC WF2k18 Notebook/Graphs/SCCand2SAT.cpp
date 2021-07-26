VI order,cmpNodes[N];int vis[N],comp[N],curr;
//g:graph,rg:reverse graph 
void dfs1(int u){
  vis[u]=1;
  for(auto w:g[u])
    if(!vis[w])dfs1(w);	
  order.PB(u);}
void dfs2(int u){
  vis[u]=1;comp[u]=curr;cmpNodes[curr].PB(u);
  for(auto w:rg[u])if(!vis[w])dfs2(w);}
void SCC(int n){
  SET(vis,0);order.clear();
  REP(i,n)if(!vis[i])dfs1(i);
  SET(vis,0);reverse(ALL(order));curr=0;
  //components are generated in topological order
  for(auto u:order)if(!vis[u])cmpNodes[++curr].clear(),dfs2(u);
}//2-SAT : N = 2*maxvars+10,M = N/2,0-based
int val[N];int var(int x){return x<<1;}
int NOT(int x){return x^1;}
bool solvable(int vars){
  SCC(2*vars);
  REP(i,vars)if(comp[var(i)]==comp[NOT(var(i))])return false;
  return true;
}void assign_vars(){
  SET(val,0);
  for(int i=1;i<=curr;i++)
    for(auto it : cmpNodes[i]){
      int u = it>>1;
      if(val[u])continue;
      val[u] = (it&1?+1:-1);}}
void add_edge(int v1,int v2){g[v1].PB(v2);rg[v2].PB(v1);}
void add_imp(int v1,int v2){add_edge(v1,v2);add_edge(1^v2,1^v1);}
void add_equiv(int v1,int v2){add_imp(v1,v2);add_imp(v2,v1);}
void add_or(int v1,int v2){add_edge(1^v1,v2);add_edge(1^v2,v1);}
void add_xor(int v1,int v2){add_or(v1, v2);add_or(1^v1,1^v2);}
void add_true(int v1){add_edge(1^v1, v1);}
void add_and(int v1,int v2){add_true(v1);add_true(v2);}
