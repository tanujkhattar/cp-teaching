#define T double // Simpson rule. integration of f from a to b
T f(T x){return x*x;}const T eps=1e-12;
T simps(T a,T b,T fa,T fm,T fb){return (fa+4*fm+fb)*(b-a)/6;}
T integr(T a,T b,T fa,T fm,T fb){T m=(a+b)/2;T fam=f((a+m)/2),
  fmb=f((m+b)/2);T l=simps(a,m,fa,fam,fm),r=simps(m,b,fm,fmb,
  fb),tot=simps(a,b,fa,fm,fb);if(fabs(l+r-tot)<eps)return tot;
  return integr(a,m,fa,fam,fm) + integr(m,b,fm,fmb,fb);}
T integrate(T a, T b){return integr(a,b,f(a),f((a+b)/2),f(b));}
