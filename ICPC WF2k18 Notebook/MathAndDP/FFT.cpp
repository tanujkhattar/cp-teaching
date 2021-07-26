namespace FFT{
#define op operator
  typedef long double ld;
  struct base{
    typedef double T; T re, im;
    base() :re(0), im(0) {}
    base(T re) :re(re), im(0) {}
    base(T re, T im) :re(re), im(im) {}
    base op + (const base& o)const{return base(re + o.re, im + o.im); }
    base op - (const base& o)const{return base(re - o.re, im - o.im); }
    base op * (const base& o)const{return base(re * o.re - im * o.im, re * o.im + im * o.re); }
    base op * (ld k) const { return base(re * k, im * k) ;}
    base conj() const { return base(re, -im); }
  };const int N = 21;const int MAXN = (1<<N);
  const double PI = acos(-1);
  base w[MAXN];base f1[MAXN];int rev[MAXN];
  void build_rev(int k){
    static int rk = -1;
    if( k == rk )return ; rk = k;
    FOR(i,1,(1<<k)+1){
      int j = rev[i-1], t = k-1;
      while(t >= 0 && ((j>>t)&1) ) { j ^= 1 << t; --t; }
      if(t >= 0) { j ^= 1 << t; --t; }
      rev[i] = j;}}
  void fft(base *a, int k) {
    build_rev(k); int n = 1 << k;
    REP(i, n) if( rev[i] > i ) swap(a[i], a[rev[i]]);
    for(int l = 2, ll = 1; l <= n; l += l, ll += ll) {
      if( w[ll].re == 0 && w[ll].im == 0 ) {
        ld angle = PI / ll;
        base ww( cosl(angle), sinl(angle) );
        if( ll > 1 ) for(int j = 0; j < ll; ++j) {
          if( j & 1 ) w[ll + j] = w[(ll+j)/2] * ww;
          else w[ll + j] = w[(ll+j)/2];
        } else w[ll] = base(1, 0);
      }
      for(int i = 0; i < n; i += l) REP(j, ll) {
        base v = a[i + j], u = a[i + j + ll] * w[ll + j];
        a[i + j] = v + u; a[i + j + ll] = v - u; }}}
  void mult(LL *a,LL *b,LL *c,int len){
    int k = 1;while((1<<k) < (2*len)) ++k;int n = (1<<k);
    REP(i, n)f1[i] = base(0,0);
    REP(i, len)f1[i] = f1[i] + base(a[i], 0);
    REP(i, len)f1[i] = f1[i] + base(0, b[i]);
    fft(f1, k);
    REP(i, 1 + n/2) {
      base p = f1[i] + f1[(n-i)%n].conj();
      base _q = f1[(n-i)%n] - f1[i].conj();
      base q(_q.im, _q.re);
      f1[i] = (p * q) * 0.25;
      if( i > 0 ) f1[(n - i)] = f1[i].conj();
    }REP(i, n) f1[i] = f1[i].conj();
    fft(f1, k);
    REP(i, 2*len){
      c[i] = LL(f1[i].re / n + 0.5);
    }}/*slow mult. faster to code. ignore above part*/
  typedef complex<double> base;
  base omega[MAXN],a1[MAXN],a2[MAXN],z1[MAXN],z2[MAXN];
  void fft(base *a, base *z, int m = N){
    if (m==1)z[0] = a[0];
    else{int s=N/m; m /= 2;
      fft(a,z,m);fft(a+s,z+m,m);
      REP(i, m){base c = omega[s*i] * z[m+i];
        z[m+i] = z[i] - c;z[i] += c;}}}
  void mult(LL *a,LL *b,LL *c,int len){
    N = 2*len;while (N & (N-1)) ++N;assert(N <= MAX);    
    REP(i, N) a1[i] = 0;REP(i, N) a2[i] = 0;
    REP(i, len) a1[i] = a[i];REP(i, len) a2[i] = b[i];
    REP(i, N) omega[i] = polar(1.0, 2*PI/N*i);
    fft(a1, z1, N);fft(a2, z2, N);
    REP(i, N) omega[i] = base(1, 0) / omega[i];
    REP(i, N) a1[i] = z1[i] * z2[i] / base(N, 0);
    fft(a1, z1, N);
    REP(i, 2*len) c[i] = round(z1[i].real());}}
    void mul_mod(LL *a, LL *b, LL *c, int len, const int mod){
      static LL a0[MAXN],a1[MAXN],b0[MAXN],b1[MAXN];
      static LL c0[MAXN],c1[MAXN],c2[MAXN];
      REP(i, len) a0[i] = a[i] & 0xFFFF;
      REP(i, len) a1[i] = a[i] >> 16;
      REP(i, len) b0[i] = b[i] & 0xFFFF;
      REP(i, len) b1[i] = b[i] >> 16;
      mult(a0, b0, c0, len);mult(a1, b1, c2, len);
      REP(i, len) a0[i] += a1[i];
      REP(i, len) b0[i] += b1[i];
      mult(a0, b0, c1, len);
      REP(i, 2*len)c1[i] -= c0[i] + c2[i];
      REP(i, 2*len)c1[i] %= mod;
      REP(i, 2*len)c2[i] %= mod;
      REP(i, 2*len)c[i]=(c0[i]+(c1[i]<<16)+(c2[i]<<32))%mod;
    }}// end of FFT namespace
//For solving recurrences of the form F_i=sum(1 <=j<i)F_j*G_n-j
void convolve(int l1, int r1, int l2, int r2){
  A = F[l1 .. r1]; B = G[l2 ... r2];//0-based polynomials
  C = A * B;//multiplication of two polynomials.
  for(int i = 0; i < C.size(); ++i)
    F[l1 + l2 + i] += C[i];
}//in main function.
F[1] = 1;//some base case.
for(int i = 1;i <= n - 1; i++){
  //We have computed till F_i and want to add its contribution.
  F[i + 1] += F[i] * G[1]; F[i + 2] += F[i] * G[2];
  for(int pw = 2; i % pw == 0 && pw + 1 <= n; pw = pw * 2){
    //iterate over every power of 2 untill 2 ^ i divides i.
    convolve(i - pw, i - 1, pw + 1, min(2 * pw, n));}}
