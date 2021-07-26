// Max flow of directed weighted graph from source to sink.
// init(n)-->AddEdge(x,y,c1,c2)-->run(src,sink).
// AddEdge(x,y,c1,c2)adds x->y of cap c1 and y->x of cap c2
namespace Dinic{// MAXE = 2*(# calls to AddEdge);
  const int MAXV=int(1e5)+10,MAXE=int(2e5)+10;
  const LL INF=1e18;LL cap[MAXE];int V,E,last[MAXV];
  int dist[MAXV],curr[MAXV],next[MAXE],adj[MAXE];
  void init(int n){V=n;E=0;REP(i,V)last[i]=-1;}
  void AddEdge(int x,int y,LL c1,LL c2){
    adj[E]=y;cap[E]=c1;next[E]=last[x];last[x]=E++;
    adj[E]=x;cap[E]=c2;next[E]=last[y];last[y]=E++;
  }LL push(int x,int sink,LL flow){
    if(x==sink)return flow;
    for(int &e=curr[x];e!=-1;e=next[e]){
      int y=adj[e];
      if(cap[e]&&dist[x]+1==dist[y])
        if(LL f=push(y,sink,min(flow,cap[e])))
          return cap[e]-=f,cap[e^1]+=f,f;
    }return 0;
  }LL run(int src,int sink){LL ret=0;
    while(1){
      REP(i,V)curr[i]=last[i],dist[i]=-1;
      queue<int> Q;Q.push(src),dist[src]=0;
      while(!Q.empty()){
        int x=Q.front();Q.pop();
        for(int e=last[x];e!=-1;e=next[e]){
          int y=adj[e];
          if(cap[e]&&dist[y]==-1)
            Q.push(y),dist[y]=dist[x]+1;
        }}if(dist[sink]==-1)break;
      while(LL f=push(src,sink,INF))ret+=f;
    }return ret;}}
