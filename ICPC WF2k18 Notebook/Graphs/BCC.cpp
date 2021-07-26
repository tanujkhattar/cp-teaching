VI g[N],tree[N],st;bool isArtic[N];int U[M],V[M],low[N];
int ord[N],depth[N],col[N],C,T,compNo[N],extra[N];
//For all [1,n+C] whose extra[i]=0 is part of Block-Tree.
//1-Based.Everything from [1,C] : type B & [C,n+C] : type C.
void dfs(int i){//Doesn’t work for multi-edges.Remove them
  low[i]=ord[i]=T++;for(int j=0;j<SZ(g[i]);j++){
    int ei=g[i][j],to = adj(i,ei);
    if(ord[to]==-1){
      depth[to]=depth[i]+1;st.PB(ei);dfs(to);
      low[i] = min(low[i],low[to]);
      if(ord[i]==0||low[to]>=ord[i]){
        if(ord[i]!=0||j>=1)isArtic[i] = true;
        ++C;
        while(!st.empty()){
          int fi=st.back();st.pop_back();col[fi]=C;
          if(fi==ei)break;
        }
      }
    }else if(depth[to]<depth[i]-1){
      low[i] = min(low[i],ord[to]);st.PB(ei);}}}
void run(int n){
  SET(low,-1);SET(depth,-1);
  SET(ord,-1);SET(col,-1);SET(isArtic,0);st.clear();C=0;
  for(int i=1;i<=n;++i)
    if(ord[i]==-1)
      T = 0,dfs(i);
}void buildTree(int n){
  run(n);SET(compNo,-1);VI tmpv;SET(extra,-1);
  for(int i=1;i<=n;i++){
    tmpv.clear();for(auto e:g[i])tmpv.PB(col[e]);
    sort(ALL(tmpv));tmpv.erase(unique(ALL(tmpv)),tmpv.end());
    //handle isolated vertics
    if(tmpv.empty()){compNo[i]=C+i;extra[C+i]=0;continue;}
    if(SZ(tmpv)==1){//completely in 1 comp.
      compNo[i] = tmpv[0];extra[tmpv[0]]=0;
    }else{ //it’s an articulation vertex.
      compNo[i]=C+i;extra[C+i]=0;
      for(auto j:tmpv){
        extra[j]=0;tree[C+i].PB(j);tree[j].PB(C+i);
      }}}}
