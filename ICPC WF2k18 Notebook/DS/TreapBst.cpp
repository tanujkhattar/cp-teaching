struct node{int val,prior,size;node *l,*r;};
typedef node* pnode;int sz(pnode t){return t?t->size:0;}
void upd_sz(pnode t){if(t)t->size = sz(t->l)+1+sz(t->r);}
void split(pnode t,pnode &l,pnode &r,int key){if(!t)l=r=NULL;
  else if(t->val<=key)split(t->r,t->r,r,key),l=t;//key in l
  else split(t->l,l,t->l,key),r=t;upd_sz(t);
}void merge(pnode &t,pnode l,pnode r){if(!l || !r)t=l?l:r;
  else if(l->prior> r->prior)merge(l->r,l->r,r),t=l;
  else merge(r->l,l,r->l),t=r;upd_sz(t);
}void insert(pnode &t,pnode it){if(!t) t=it;
  else if(it->prior>t->prior)split(t,it->l,it->r,it->val),t=it;
  else insert(t->val<it->val?t->r:t->l,it);upd_sz(t);
}void erase(pnode &t,int key){if(!t)return;
  else if(t->val==key){pnode x=t;merge(t,t->l,t->r);free(x);}
  else erase(t->val<key?t->r:t->l,key);upd_sz(t);
}void unite (pnode &t,pnode l, pnode r){
  if(!l||!r)return void(t=l?l:r);pnode lt,rt;
  if(l->prior<r->prior)swap(l,r);split(r,lt,rt,l->val);
  unite(l->l,l->l,lt);unite(l->r,l->r,rt);t=l;upd_sz(t);
}pnode init(int val){pnode ret = (pnode)malloc(sizeof(node));
  ret->val=val;ret->size=1;ret->prior=rand();ret->l=ret->r=NULL;
  return ret;}insert(init(x),head);
