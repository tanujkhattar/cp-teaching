struct SA{//u & w are endpos equiv iff u is found in s only
  VVI to;VI dp,link,len,val;//as a suffix of string w.
  int last,sz;//if len(u) <= len(w), then either enpos(w) is a  
  SA(){//subset of endpos(u) or they both are disjoint sets.
    to.clear();dp.clear();link.clear();len.clear();val.clear();
    last = sz = 0;//len[i] : length of the longest substring 
  }//belonging to the equivalence class of state/node i.
  SA(int n){//link[i]:suffix link from state i leading to state 
    to = VVI(n,VI(sigma,0)); dp = link = len = val = VI(n,0);
    last = sz = 0;//corresponding to a suffix of longest(i)
  }//of length minlen(i)-1. Therefore minlen(i)=len[link[i]]+1
  SA(string &s){//suffix links form a tree in which endpos of 
    int n=2*SZ(s)+10;to=VVI(n,VI(sigma,0));//child is subset
    dp=link=len=val=VI(n,0);last=sz=0;//of endpos of its
    for(auto c:s)add_letter(c-'a');go();//parent in the tree.
  }//Substrings of length [minlen(i),len(i)] ending in index
  void add_letter(int c){//pos(i):first index in the string s
    int p = last;//at which substrings belonging to state i end
    last = ++sz;//last:state of s.Create state for string sc.
    len[last]=len[p]+1;//also set pos[last] = currindex here.
    for(;!to[p][c];p=link[p])to[p][c]=last;
    //check if it's the first occurence of c in the string
    if(to[p][c]==last)return void(link[last]=0);//if yes,
    int q = to[p][c];//return. else check if a solid transition
    if(len[q] == len[p] + 1)return void(link[last]=q);
    int x = ++sz;//we need to produce a clone of the state q.
    to[x] = to[q];//also copy pos[x]=pos[q]. x is a clone node.
    link[x]=link[q];len[x]=len[p]+1;//update len for x.
    link[last]=link[q]=x;//update suffix links of q and last.
    for(;to[p][c]==q;p=link[p])to[p][c]=x;//update transitions
  }//dp to compute no. of terminal nodes reachable from node x.
  void f(int x){//Assuming val[x]:represents whether x is a 
    if(dp[x])return;//terminal node or not. Usual dag dp.
    dp[x] = val[x];//Other DAG algo's can also be applied acc
    for(int i=0;i<sigma;i++)//to the problem. Like number of 
      if(to[x][i])//vertex/edge disjoint paths from source to
        f(to[x][i]),dp[x]+=dp[to[x][i]];//sink etc.
  }//mark the terminal nodes and compute the dp. To mark the 
  void go(){//terminal nodes go over all the suffix links of 
    for(int x=last;x;x=link[x])val[x]+=1;//the last node coz
    f(0);//last corresponds to state repesenting whole string
  }//run the query string through the automation.
  int get(string &s){//Also tree formed by suffix links is same
    int x = 0;//as the suffix tree of the reverse of string s. 
    for(auto cc:s){//to report all occurences of P in S, build
      int c = cc-'a';//SA of S and run P. If it ends at state x
      if(!to[x][c])return 0;//Do a dfs from x in the rev graph
      else x = to[x][c];//of suffix links i.e. if link[x]=y,
    }return dp[x];//then g[y].PB(x).For each visited state,add
  }};//pos[i] to ans. To avoid repitition if node i is a
//cloned node,ignore it else add pos[i] to ans. O(|P|+|output|)
