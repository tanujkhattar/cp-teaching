// INPUT:    a[][] = an nxm matrix. (rref : reduced row echelon)
// OUTPUT:   rref[][] = an nxm matAix(stored in a[][]),
const double EPS =1e-10;// returns rank of a[][]
typedef double T;typedef vector<T> VT;typedef vector<VT> VVT;
int rref(VVT &a){
  int n=a.size(),m=a[0].size(),r=0;
  for (int c=0;c<m&&r<n;c++){int j=r;
    for(int i=r+1;i<n;i++)if(fabs(a[i][c])>fabs(a[j][c]))j=i;
    if(fabs(a[j][c])<EPS)continue;swap(a[j],a[r]);
    T s=1.0/a[r][c];for(int j=0;j<m;j++)a[r][j]*=s;
    for(int i=0;i<n;i++)if(i!=r){T t=a[i][c];
      for(int j=0;j<m;j++)a[i][j]-=t*a[r][j];
    }r++;}return r;}
