// Min cost bipartite matching.solves 1000x1000 problems.
//cost[i][j] = cost for pairing left node i with right node j
//Lmate[i] = index of right node that left node i pairs with
//Rmate[j] = index of left node that right node j pairs with
//The values in cost[i][j] may be positive or negative.
typedef vector<double>VD;typedef vector<VD>VVD;
double MinCostMatching(const VVD &cost,VI &Lmate,VI &Rmate){
  int n=SZ(cost);VD u(n);VD v(n);REP(i,n){u[i]=cost[i][0];
    for(int j=1;j<n;j++)u[i]=min(u[i],cost[i][j]);
  }REP(j,n){v[j]=cost[0][j]-u[0];
    for(int i=1;i<n;i++)v[j]=min(v[j],cost[i][j]-u[i]);
  }Lmate= VI(n, -1);Rmate = VI(n,-1);int mated=0;
  REP(i,n){REP(j,n){if(Rmate[j]!=-1)continue;
      if(fabs(cost[i][j]-u[i]-v[j])<1e-10){
        Lmate[i]=j;Rmate[j]=i;mated++;break;
      }}}VD dist(n);VI dad(n),seen(n);
  while(mated<n){int s=0;while(Lmate[s]!=-1)s++;
    fill(ALL(dad),-1);fill(ALL(seen),0);
    REP(k,n)dist[k]=cost[s][k]-u[s]-v[k];int j=0;
    while(true){j=-1;//find closest
      REP(k,n){if(seen[k])continue;if(j==-1||dist[k]<dist[j])j=k;
      }seen[j]=1;if(Rmate[j]==-1)break;
      const int i=Rmate[j];for(int k=0;k<n;k++){
        if(seen[k])continue;
        const double new_dist=dist[j]+cost[i][k]-u[i]-v[k];
        if(dist[k]>new_dist)dist[k]=new_dist,dad[k]=j;
      }}REP(k,n){if(k==j||!seen[k])continue;
      const int i=Rmate[k];v[k]+=dist[k]-dist[j];
      u[i]-=dist[k]-dist[j];}u[s]+=dist[j];
    while(dad[j]>=0){const int d=dad[j];Rmate[j]=Rmate[d];
      Lmate[Rmate[j]]=j;j=d;}Rmate[j]=s;Lmate[s]=j;mated++;
  }double val=0;REP(i,n)val+=cost[i][Lmate[i]];return val;}
