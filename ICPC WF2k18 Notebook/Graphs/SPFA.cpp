//Shortest Path Faster Algorithm. Computes SSSP.Works 
//on graph with -ve edges.Returns false if -ve cycle.
//For -ve cycle, be careful about disconnected graphs
VII g[N];int n,cnt_q[N];bool in_q[N];
bool SPFA(int s,LL d[]){
  SET(cnt_q,0);SET(in_q,0);
  for(int i=1;i<=n;i++)d[i]=INF;
  d[s]=0;queue<int> Q;Q.push(s);
  cnt_q[s]=1;in_q[s]=1;
  while(!Q.empty()){
    int u = Q.front();Q.pop();in_q[u]=0;
    for(auto it : g[u]){
      int w=it.F,wt=it.S;
      if(d[u]+wt>=d[w])continue;
      d[w]=d[u]+wt;if(in_q[w])continue;
      in_q[w]=1;cnt_q[w]++;Q.push(w);
      if(cnt_q[w]>=n)return false;
    }}return true;}
