tuple<LL,LL,LL> extended_euclid(LL a,LL b){
  LL s=0,ss=1,t=1,tt=0,r=b,rr=a,tmp;while(r){tmp=ss-(rr/r)*s;
    ss=s;s=tmp;tmp=tt-(rr/r)*t;tt=t;t=tmp;tmp=rr%r;rr=r;r=tmp;
  }if(a<0){ss=-ss;tt=-tt;rr=-rr;}//ss*a+tt*b=rr=gcd(a,g)
  return make_tuple(ss,tt,rr);
}LL mod(LL a,LL N){a%=N;return a<0?a+N:a;}
LL modmul(LL a,LL b,LL N){a=mod(a,N);b=mod(b,N);if(a<b)swap(a,b);
LL res=0;for(int i=63-__builtin_clzll(b);i>=0;--i){
res=(res+res)%N;if((b>>i)&1)res=(res+a)%N;}return res;}
LL modpow(LL b,LL e,LL N){LL res=1;
for(int i=63-__builtin_clzll(e);i>=0;--i){res=modmul(res,res,N);
    if((e>>i)&1)res=modmul(res,b,N);}return res;
}LL mod_inverse(LL a,LL n){LL b,k,g;//ba+kn=gcd(a, n)
  tie(b,k,g)=extended_euclid(a,n);return (g!=1?-1:mod(b,n));
}//crt for n tems can be found by iterating over n terms.
pair<LL,LL> chinese_remainder_theorem(LL x,LL a,LL y,LL b){
  //finds z (mod M) so z=a (mod x) and z=b (mod y),lcm
  LL s,t,d;tie(s,t,d)=extended_euclid(x,y);
  if(a%d!=b%d)return make_pair(0,-1);LL M=x*y;
  LL z=(modmul(modmul(s,b,M),x,M)+modmul(modmul(t,a,M),y,M))%M;
  return make_pair(z/d,M/d);}//returns x,y such that c=ax+by
pair<LL,LL> linear_diophantine(LL a,LL b,LL c){
  LL d=__gcd(a,b);if(c%d!=0)return make_pair(-1,-1);
  return make_pair((c/d)*mod_inverse(a/d,b/d),(c-a*x)/b);
}//returns all solutions to ax=b mod n
vector<int> modular_linear_equation_solver(int a,int b,int n){
  LL x,y,d;tie(x,y,d)=extended_euclid(a,n);vector<int> ans;
  if(b%d==0){b/=d;n/=d;x=mod(x*b,n);for(LL i=0;i<d;++i)
    ans.push_back(mod(x+i*n,n));}return ans;
}bool miller_rabin_primality(LL N){
  //deterministic for all<=2 ^ 64
  static const int p[12]={2,3,5,7,11,13,17,19,23,29,31,37};
  if(N<=1)return false;for(int i=0;i<12;++i){
    if(p[i]==N)return true;if(N%p[i]==0)return false;
  }LL c=N-1,g=0;while(!(c&1))c>>=1,++g;
  for(int i=0;i<12;++i){LL k=modpow(p[i],c,N);
    for(int j=0;j<g;++j){LL kk=modmul(k,k,N);
      if(kk==1&&k!=1&&k!=N-1)return false;k=kk;}
    if(k!=1)return false;}return true;
}mt19937 gen(time(0));//gives a factor of N
LL pollard_rho(LL N){if(N%2==0)return 2;
  LL xx=uniform_int_distribution<LL>()(gen)%N,x=xx;
  LL c=uniform_int_distribution<LL>()(gen)%N,d=1;
  for(int iters=0;iters<2000;++iters){
    x=(modmul(x,x,N)+c)%N;xx=(modmul(xx,xx,N)+c)%N;
    xx=(modmul(xx,xx,N)+c)%N;d=__gcd(abs(x-xx),N);
    if(d!=1&&d!=N)break;}return d;}
#define M(x) x%p//solves a^2=x(mod p),return -1 if x not exist
LL root_of_x(LL x,LL p){LL r=0,s=p-1,n,m,x,b,g,coff,t;
  if(power(a,((p-1)>>1),p)==p-1)return -1;
  //calcute (a^((p-1)/2))%p;
  while((s&1)==0){s=(s>>1);r++;}for(LL i=2;i<p;i++)
    if(power(i,((p-1)>>1),p)==p-1){n=i;break;}
  b=power(a,s,p);g=power(n,s,p);x=power(a,((s+1)>>1),p);
  while(r>0){t=b;for(m=0;m<r;m++){if(M(t)==1)break;t=M(t*t);}
    if(m>0){coff=power(g,(1<<(r-(m+1))),p);x=M(x*coff);
      g=M(coff*coff);b=M(b*g);}r=m;}return x;}
//To factorize in N^(1/3),do normal+miller_rabin+pollard_rho
//to get the remaining prime x s.t. x * x or x and n / x. 
