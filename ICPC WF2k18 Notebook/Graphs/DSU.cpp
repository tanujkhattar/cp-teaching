int F(int x){//dsu maintaing 2-coloring
  if(x==dsu[x])return x;//of each tree
  int p = F(dsu[x]);//in the forest
  C[x] ^= C[dsu[x]];return dsu[x]=p;
}bool Union(int a,int b){
  int x=F(a),y=F(b);if(x==y)return 0;
  if(sz[x]>sz[y])swap(x,y),swap(a,b);
  int p = (C[a]==C[b]);C[x] ^= p;
  sz[y] += sz[x];dsu[x] = y;
  F(a);F(b);return true;}
