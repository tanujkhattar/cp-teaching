namespace AhoCorasick{
  const int MAXN = int(1e5)+10;//pnode out[MAXN];
  map<char,int> to[MAXN];int f[MAXN],blen;bool end[MAXN];
  void add_str(int idx,string &s){int x = 0;
    for(auto c : s){if(!to[x][c])to[x][c] = ++blen;
      x = to[x][c];}/*insert(out[x],idx);*/end[x] = true;
  }int next(int state,char c){
    while(state && !to[state].count(c))state = f[state];
    return to[state][c];
  }void build_SL(){queue<int> Q;
    for(auto it : to[0])if(it.S)Q.push(it.S);
    while(!Q.empty()){int x = Q.front();Q.pop();
      for(auto it : to[x]){int y = it.S, c = it.F;
        f[y] = next(f[x],c);Q.push(y);}
      /*merge(out[x],out[f[x]]);*/end[x] |= end[f[x]];
    }}VII findAllOccurences(string &s){int x = 0;VII ret;
    for(int i=0;i<SZ(s);i++){char c = s[i]; x = next(x,c);
      for(pnode it = out[x]; it != NULL; it = it->nxt)
        ret.PB({i,it->val});}return ret;}}
