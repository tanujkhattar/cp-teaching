int nfa[N];//preprocess pattern & search in any text in O(|T|)
  void build_NFA(string &P){
    nfa[0]=0;int x=0,n=SZ(P);
    for(int i=1;i<=n;i++){
      nfa[i]=x;
      while(i!=n){
        if(P[x]==P[i]){x++;break;}
        if(!x)break;x=nfa[x];}}}
int kmp_search(int start,string& P,string& T){
  for(int i=start,x=0;i<SZ(T);){
    if(T[i]==P[x])x++,i++;
    else if(!x)i++;
    else x = nfa[x];
    if(x==SZ(P))return i-SZ(P);
  }return -1;
}//ans=kmp_search(ans),ans+=(SZ(P)-nfa[SZ(p)])
