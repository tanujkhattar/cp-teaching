const int N = int(1e5)+10;
struct node{
  int nxt[26];//edge u-x->v: v = xux where x : character. 
  int len;//length of palindrome stored at this node.
  int sufflink;//u-s->v,v:longest proper palindromic suff of u.
  int s,e;//start,end indices of palindrome in string
  int num;//No of reachable suffix links by the current node.
  node(){SET(nxt,0);len=sufflink=s=e=0;}
}tree[N];//all nodes of tree. Buffer.blen : buffer length
int blen;//node 1:root with len -1,2:root with len 0
int suff;//Maximum suffix palindrome at any point of time.
bool addLetter(string & s,int pos){//true=new node is created
  int cur=suff,curlen=0,idx=s[pos]-'a';
  while(1){//Find L.S. A s.t. xAx is new LS Palindrom
    curlen = tree[cur].len;//start with cur.
    if(pos-1-curlen>=0&&s[pos-1-curlen]==s[pos])break;
    cur=tree[cur].sufflink;//LS : Longest Suffix
  }//If node for xAx already exists
  if(tree[cur].nxt[idx]){//set new suff = index of already...
    suff=tree[cur].nxt[idx];return false;//...existing node xAx
  }suff = ++blen;//add new node for xAx and update suff
  tree[blen].len=tree[cur].len+2;//length of xAx.starting & ...
  tree[blen].s=pos-1-curlen;tree[blen].e=pos;//ending indices..
  tree[cur].nxt[idx]=blen;//of xAx.on adding x to A,we get xAx.
  //Now we need to search for the suffix link of newly formed..
  if(tree[blen].len==1){//...node blen i.e. xAx
    tree[blen].sufflink=2;tree[blen].num=1;//if xAx == x, 
    return true;//set suffix link equal to empty string(node 2)
  }//else search for the suffix link
  while(1){//Initially cur-->A. Find LS B of A s.t. xBx
    cur=tree[cur].sufflink;curlen=tree[cur].len;
    if(pos-1-curlen>=0 && s[pos-1-curlen]==s[pos]){
      //Found B.Could be -1 s.t. sufflink to node 1
      tree[blen].sufflink=tree[cur].nxt[idx];
      break;//Set the sufflink and we are done.
    }//O(N) coz finding new suff can move left pointer to one 
  }//unit left and following suffix links always moves it to 
  tree[blen].num=tree[tree[blen].sufflink].num+1;//right. So,
  return true;//it can travel at most O(2*N) times to right.
}void initTree(){//Initialize the tree.
  blen=2;suff=2;//Longest suffix initially is the empty string. 
  tree[1].len=-1;tree[1].sufflink=1;//Node 1-->root with len -1
  tree[2].len=0;tree[2].sufflink=1};//Node 2-->root with len 0
