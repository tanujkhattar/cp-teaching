LL invert_mod(LL k,LL m){
  if(m==0)return(k==1||k==-1)?k:0;if(m<0)m=-m;k%=m;
  if(k<0)k+=m;int neg=1;LL p1=1,p2=0,k1=k,m1=m,q,r,temp;
  while(k1>0){q=m1/k1;r=m1%k1;temp=q*p1+p2;p2=p1;p1=temp;
    m1=k1;k1=r;neg=!neg;}return neg?m-p2:p2;
}// Preconditions:0<=k<=n;p>1 prime
LL choose_mod_one(LL n,LL k,LL p){
  if(k<p)return choose_mod_two(n,k,p);
  LL q_n,r_n,q_k,r_k,choose;
  q_n=n/p;r_n=n%p;q_k=k/p;r_k=k%p;
  choose=choose_mod_two(r_n,r_k,p);
  choose*=choose_mod_one(q_n,q_k,p);
  return choose%p;
}// Preconditions:0<=k<=min(n,p-1);p>1 prime
LL choose_mod_two(LL n,LL k,LL p){
  n%=p;if(n<k)return 0;if(k==0||k==n)return 1;
  if(k>n/2)k=n-k;LL num=n,den=1;
  for(n=n-1;k>1;--n,--k)num=(num*n)%p,den=(den*k)%p;
  den=invert_mod(den,p);return (num*den)%p;
}LL fact_exp(LL n, LL p){LL ex=0;do{n/=p;ex+=n;
  }while(n>0);return ex;
}//returns nCk % p in O(p).n and k can be large.
LL choose_mod(LL n, LL k, LL p){
  if(k<0||n<k)return 0;if(k==0||k==n)return 1;
  if(fact_exp(n)>fact_exp(k)+fact_exp(n-k))return 0;
  return choose_mod_one(n,k,p);}
