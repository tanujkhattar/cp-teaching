int ST[4*N],lazy[4*N],A[N];
#define lc (x<<1)
#define rc (x<<1)|1
void push(int x,int l,int r){
  ST[x]+=lazy[x]; //Operation of lazy
  if(l==r-1)lazy[x]=0;
  if(!lazy[x])return;
  lazy[lc]+=lazy[x];
  lazy[rc]+=lazy[x];
  lazy[x]=0;//Propagate Lazy
}void up(int x){//Operation of Segtree
  ST[x] = min(ST[lc],ST[rc]);
}void build(int l=0,int r=N,int x=1){
  lazy[x]=0;//clear lazy
  if(l==r-1)return void(ST[x]=A[l]);
  int m = (l+r)/2;
  build(l,m,lc);
  build(m,r,rc);up(x);
}void update(int L,int R,int add,int l=0,int r=N,int x=1){
  push(x,l,r);int m = (l+r)/2;
  if(l>=R || r<=L)return;
  if(l>=L && r<=R){
    lazy[x]+=add;//operation of lazy update
    return push(x,l,r);
  }update(L,R,add,l,m,lc);
  update(L,R,add,m,r,rc);up(x);
}int query(int L,int R,int l=0,int r=N,int x=1){
  push(x,l,r);int m = (l+r)/2;
  if(l>=R||r<=L)return INF;//nothing here
  if(l>=L && r<=R)return ST[x];
  int la = query(L,R,l,m,lc);
  int ra = query(L,R,m,r,rc);
  return min(la,ra);//operation of segtree
}
