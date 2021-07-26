// Solves systems of linear modular equations.mat[i][C]=b[i];
// Build a matrix of coefficients and call run(mat, R, C, mod).
// If no solution,returns -1, else returns # of free variables.
// If i-th variable free,row[i]=-1,else it's value = ans[i].
// Time complexity: O(R * C^2) - MAXC is the number of columns
namespace Gauss{const int MAXC=1001;int row[MAXC];LL ans[MAXC];
  LL inv(LL x,LL mod){return power(x,mod-2,mod);}
  int run(LL mat[][MAXC],int R,int C,LL mod){REP(i,C)row[i]=-1;
    int r=0;REP(c,C){int k=r;while(k<R && mat[k][c]==0)++k;
      if(k==R)continue;REP(j,C+1)swap(mat[r][j],mat[k][j]);
      LL div=inv(mat[r][c],mod);REP(i,R)if(i!=r){
        LL w = mat[i][c]*(mod-div)%mod;
        REP(j,C+1) mat[i][j]=(mat[i][j]+mat[r][j]*w)%mod;
      }row[c] = r++;}REP(i,C){int r = row[i];
        ans[i]=(r==-1?0:mat[r][C])*inv(mat[r][i],mod)%mod;
      }FOR(i, r, R)if(mat[i][C])return -1;return C - r;}}
namespace GaussMod2{//Every x in basis has leftmost bit 1 s.t
  void add(int x){//every y!=x has that bit=0.Rank=SZ(basis)
    for(auto &y : basis)if((y ^ x) < x)x ^= y;
    for(auto &y : basis)if((y ^ x) < y)y ^= x;
    if(x)basis.PB(x), sort(ALL(basis));
  }int query(int k){k--;//kth smallest xor.1 based.
    int ret=0;REP(i,SZ(basis))if((1<<i)&k)ret ^= basis[i];
    return ret;}}
