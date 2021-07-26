int L[N*LOGN],R[N*LOGN],ST[N*LOGN],blen,root[N],A[N];
//sparse persistent-segtree. range sum, initially 0
int update(int pos,int add,int l,int r,int id){
  if(l>pos || r<=pos)return id;
  int ID = ++blen, m=l+(r-l)/2;
  if(l==r-1)return (ST[ID]=ST[id]+add,ID);
  L[ID]=update(pos,add,l,m,L[id]);
  R[ID]=update(pos,add,m,r,R[id]);
  return (ST[ID]=ST[L[ID]]+ST[R[ID]],ID);
}root[0]=++blen;
for(int i=1;i<=n;i++)
  root[i]=update(A[i],1,0,MX,root[i-1]);
