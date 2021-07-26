const LL is_query=-(1LL<<62);
struct Line{
  LL m,b;//compare two lines by increasing slope
  mutable function<const Line*()> succ;
  bool operator<(const Line& rhs)const{
    if(rhs.b!=is_query)return m<rhs.m;//> for min
    const Line* s=succ();
    if(!s)return 0;
    return b-s->b<(s->m-m)*rhs.m;}};//> for min
struct HullDynamic:public multiset<Line>{
  bool bad(iterator y){//maintains upper hull for max
    auto z=next(y);
    if(y==begin()){
      if(z==end())return 0;
      return y->m == z->m && y->b <= z->b;//>= for min
    }auto x=prev(y);
    if(z==end())
      return y->m==x->m && y->b<=x->b; // >= for min
    return (x->b-y->b)*(z->m-y->m)>=(y->b-z->b)*(y->m-x->m);
  }//Note: M * B should NOT Overflow!
  void insert_line(LL m,LL b){
    auto y=insert({ m,b});
    y->succ=[=]{return next(y)==end()?0:&*next(y);};
    if(bad(y)){erase(y);return;}
    while(next(y)!=end() && bad(next(y)))erase(next(y));
    while(y!=begin() && bad(prev(y)))erase(prev(y));
  }LL eval(LL x){
    auto l=*lower_bound((Line){x,is_query});
    return l.m*x +l.b;}};
