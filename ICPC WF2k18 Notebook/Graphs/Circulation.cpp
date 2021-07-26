// Configure: MAXE (at least 2 * calls_to_edge)
// - init(n) --> AddEdge(x,y,c,w) --> run();
// - AddEdge(x, y, c, w) edge x->y with capacity c and cost w
namespace Circu {const int MAXV = 1000100, MAXE = 1000100;
  int how[MAXV],good[MAXV],bio[MAXV],cookie=1,to[MAXE];
  int from[MAXE],V,E;LL cap[MAXE],cost[MAXE],dist[MAXV];
  void init(int n){V=n;E=0;}
  void AddEdge(int x,int y,LL c, LL w) {
    from[E]=x;to[E]=y;cap[E]=c;cost[E]=+w;++E;
    from[E]=y;to[E]=x;cap[E]=0;cost[E]=-w;++E;
  }void reset(){REP(i, V) dist[i]=0,how[i]=-1;}
  bool relax(){bool ret = false;
    REP(e, E)if(cap[e]){ int x=from[e],y=to[e];
      if(dist[x]+cost[e]<dist[y]){
        dist[y]=dist[x]+cost[e];
        how[y]=e;ret=true;
      }}return ret;
  }LL cycle(int s,bool flip = false){
    int x=s;LL c=cap[how[x]],sum = 0;
    do{int e=how[x];c = min(c,cap[e]);x = from[e];
    }while (x!=s);
    do{int e = how[x];
      if(flip){cap[e]-=c;cap[e^1]+=c;
      }sum += cost[e]*c;x=from[e];
    }while(x!=s);
    return sum;
  }LL push(int x){
    for(++cookie; bio[x]!=cookie; x=from[how[x]]){
      if(!good[x]||how[x]==-1||cap[how[x]]==0)return 0;
      bio[x]=cookie;good[x]=false;
    }return cycle(x) >= 0 ? 0 : cycle(x, true);
  }LL run(){
    reset();LL ret = 0;
    REP(step,2*V){if(step==V)reset();if(!relax())continue;
      REP(i, V) good[i] = true;
      REP(i, V) if(LL w=push(i))ret+=w,step=0;
    }return ret;}}
