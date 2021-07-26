struct node{int prior,size,val,sum,lazy;node *l,*r;};
typedef node* pnode;//array value,segtree info,lazy update
int sz(pnode t){return t?t->size:0;}
void upd_sz(pnode t){if(t)t->size=sz(t->l)+1+sz(t->r);}
void lazy(pnode t){if(!t || !t->lazy)return;
  t->val+=t->lazy;/*operation of lazy*/t->sum+=t->lazy*sz(t);
  if(t->l)t->l->lazy+=t->lazy;//propagate lazy
  if(t->r)t->r->lazy+=t->lazy;t->lazy=0;
}void reset(pnode t){if(t)t->sum = t->val;//already propagated
}void combine(pnode& t,pnode l,pnode r){
  if(!l || !r)return void(t = l?l:r);//combine segtree ranges
  t->sum = l->sum + r->sum;
}void operation(pnode t){//operation of segtree
  if(!t)return;reset(t);//node == single element of array
  lazy(t->l);lazy(t->r);//imp:propagate lazy before combining
  combine(t,t->l,t);combine(t,t,t->r);
}void split(pnode t,pnode &l,pnode &r,int pos,int add=0){
  if(!t)return void(l=r=NULL);lazy(t);int cpos=add+sz(t->l);
  if(cpos<=pos)//element at pos goes to "l"
    split(t->r,t->r,r,pos,cpos+1),l=t;
  else split(t->l,l,t->l,pos,add),r=t;upd_sz(t);operation(t);
}void merge(pnode &t,pnode l,pnode r){//result/left/right array
  lazy(l);lazy(r);if(!l || !r) t = l?l:r;
  else if(l->prior>r->prior)merge(l->r,l->r,r),t=l;
  else merge(r->l,l,r->l),t=r;upd_sz(t);operation(t);
}pnode init(int val){pnode ret=(pnode)malloc(sizeof(node));
  ret->prior=rand();ret->size=1;ret->val=val;
  ret->sum=val;ret->lazy=0;return ret;
}int range_query(pnode t,int l,int r){//[l,r]
  pnode L,mid,R;split(t,L,mid,l-1);
  split(mid,t,R,r-l);/*note: r-l!*/int ans = t->sum;
  merge(mid,L,t);merge(t,mid,R);return ans;
}void range_update(pnode t,int l,int r,int val){//[l,r]
  pnode L,mid,R;split(t,L,mid,l-1);
  split(mid,t,R,r-l);/*note: r-l!*/t->lazy+=val; //lazy_update
  merge(mid,L,t);merge(t,mid,R);}
