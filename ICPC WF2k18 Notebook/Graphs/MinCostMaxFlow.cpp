// Min-cost max-flow (uses SPFA. Replace by Dijkstra if needed)
// init(n)->AddEdge(x,y,cap,cost)->run(src,sink)->{flow,cost}
namespace MCMF{//MAXE = 2*calls to AddEdge
  const int MAXV = int(1e5)+10,MAXE = int(2e5)+10;
  const LL INF = 1e18;int V,E,last[MAXV],how[MAXV],adj[MAXE];
  int next[MAXE],from[MAXE];
  LL cap[MAXE],cost[MAXE],pi[MAXV],dist[MAXV];
  void init(int n){V=n;E=0;REP(i,V)last[i]=-1,pi[i]=0;}
  void AddEdge(int x, int y, LL c, LL w){
    from[E]=x;adj[E]=y;cap[E]=c;cost[E]=+w;
    next[E]=last[x];last[x]=E++;
    from[E]=y;adj[E]=x;cap[E]=0;cost[E]=-w;
    next[E]=last[y];last[y]=E++;
  }int cnt_q[MAXV],Q[MAXV],qlen;bool in_q[MAXV];
  bool SPFA(int s,int t){//replace by Dijkstra if all costs +ve
    REP(i,V)dist[i]=INF,cnt_q[i]=in_q[i]=0;
    qlen=0;Q[qlen++]=s;dist[s]=0;cnt_q[s]=1;in_q[s]=1;
    while(qlen){
      int u = Q[--qlen];in_q[u]=0;
      for(int e=last[u];e>=0;e=next[e]){
        if(cap[e]==0)continue;
        //compare dist by val in dijkstra also. rest is same
        int w=adj[e];
        LL val = dist[u]+pi[u]+cost[e]-pi[w];
        if(val>=dist[w])continue;
        dist[w]=val;how[w]=e;
        if(in_q[w])continue;
        in_q[w]=1;cnt_q[w]++;Q[qlen++]=w;
        //if(cnt_q[w]>=V)return false;
      }}return dist[t] < INF/2;}
  pair<LL, LL> run(int src, int sink){
    LL total = 0,flow = 0;
    while(SPFA(src,sink)){
      LL aug = cap[how[sink]];
      for(int i=sink;i!=src;i=from[how[i]])
        aug = min(aug,cap[how[i]]);
      for(int i=sink;i!=src;i=from[how[i]]){
        cap[how[i]]-=aug;
        cap[how[i]^1] += aug;total += cost[how[i]] * aug;
      }flow += aug;
      REP(i,V)pi[i]=min(pi[i]+dist[i],INF);
    }return make_pair(flow, total);}}
