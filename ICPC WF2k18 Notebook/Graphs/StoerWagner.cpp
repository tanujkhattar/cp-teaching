// OUTPUT:(min cut value, nodes in half of min cut)
pair<int,VI> GetMinCut(VVI &weights){//O(|V|^3)
   int N=SZ(weights),best_weight=-1;VI used(N),cut,best_cut;
  for(int phase=N-1;phase>=0;phase--){
    VI w=weights[0];VI added=used;int prev,last=0;
    REP(i,phase){prev=last;last=-1;for(int j=1;j<N;j++)
        if(!added[j]&&(last==-1||w[j]>w[last]))last=j;
      if(i==phase-1){REP(j,N)weights[prev][j]+=weights[last][j];
        REP(j,N)weights[j][prev]=weights[prev][j];
        used[last]=true;cut.push_back(last);
        if(best_weight==-1||w[last]<best_weight)
          best_cut=cut,best_weight=w[last];
      }else{REP(j,N)w[j]+=weights[last][j];added[last]=true;
      }}}return MP(best_weight,best_cut);}
