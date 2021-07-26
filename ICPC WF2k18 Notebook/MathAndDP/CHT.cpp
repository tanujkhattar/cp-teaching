vector<LL> M,B;int ptr;// convex hull, minimum
bool bad(int a,int b,int c){//make sure LL is enough
  return (B[c]-B[a])*(M[a]-M[b])<(B[b]-B[a])*(M[a]-M[c]);
}// insert with non-increasing m
void insert(LL m, LL b){M.PB(m);B.PB(b);
  while(SZ(M) >= 3 && bad(SZ(M)-3, SZ(M)-2, SZ(M)-1)){
    M.erase(M.end()-2);B.erase(B.end()-2);
  }}LL get(int i, LL x){return M[i]*x + B[i];}
LL query(LL x){ptr=min(SZ(M)-1,ptr);
  while(ptr<SZ(M)-1 && get(ptr+1,x)<get(ptr,x))ptr++;
  return get(ptr,x);}//query with non-decreasing x
