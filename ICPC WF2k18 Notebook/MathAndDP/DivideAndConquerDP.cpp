LL A[N],DP[K][N],cost[N][N];int k;
void solve(int l,int r,int L,int R){
  if(l>r)return;//assuming Best[i] is monotonic
  int mid = (l+r)/2,best = L;DP[k][mid]=INF;
  for(int i = min(R,mid-1);i>=L;i--)
    if(DP[k-1][i] + cost[i+1][mid] <= DP[k][mid])
      DP[k][mid] = DP[k-1][i] + cost[i+1][mid],best = i;
  solve(l,mid-1,L,best);solve(mid+1,r,best,R);
}/*in main*/for(int i=1;i<=n;i++)DP[1][i]=cost[1][i];
for(k=2;k<=kk;k++)solve(1,n,1,n);
