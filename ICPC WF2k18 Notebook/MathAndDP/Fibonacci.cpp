//using f(a+b)=f(a+1)f(b)+f(b-1)f(a);
LL fib(LL n,LL mod){
  LL i,h,j,k,t;i=h=1;j=k=0;
  while(n>0){if(n%2==1){t=(j*h)%mod;
    j=(i*h + j*k +t)%mod;i=(i*k + t)%mod;}
    t=(h*h)%mod;h=(2*k*h + t)%mod;
    k=(k*k + t)%mod;n=n/2;}return j;
}LL pisano(int mod){ LL period=1,i;
  for(i=2;i*i<=mod;i++){if(mod%i==0){
    if(i==2) period*=3;else if(i==5) 
    period*=20;else period*=(i-1)*(i+1); 
    mod/=i;while(mod%i==0){period*=i,mod/=i;}
  }if(mod>1){i=mod;if(i==2)period*=3; 
  else if(i==5)period*=20;
  else period*=(i-1)*(i+1);}return period;}}
