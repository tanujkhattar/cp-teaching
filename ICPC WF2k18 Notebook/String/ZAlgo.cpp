int L=0,R=0;//compute Z array s.t. Z[i] stores length of the
for(int i=1;i<n;i++){
  if(i>R){
    L=R=i;//longest substring starting
    while(R<n&&s[R-L]==s[R])R++;//from S[i] which is also a
    z[i]=R-L;R--;//prefix of S.
  }else{
    int k=i-L;if(z[k]<R-i+1)z[i]=z[k];
    else{
      L=i;while(R<n&&s[R-L]==s[R])R++;
      z[i]=R-L;R--;}}}
int maxz=0,res=0;//usage
for(int i=1;i<n;i++){
  if(z[i]==n-i&&maxz>=n-i){res=n-i;break;}
  maxz=max(maxz,z[i]);}
