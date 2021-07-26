void BellmanFord(int s){
  REP(i, n)d[i] = INF;d[s] = 0;
  REP(step, n + 1)REP(i, m){
    int from = U[i], to = V[i], wt = W[i];
    if(d[from] + wt < d[to]){
      if(step == n){
        return void(puts("Negative Cycle Found"));
      }d[to] = d[from] + wt;
    }//To solve differential constraints problem using BF,
  }//For each constraint X_i - X_j <= C_i, add an edge from
}//X_j -> X_i of wt C_i. Connect a source s to all vertices
//X_i and run BF. -ve cycle -> Not Possible, else d[i] forms
//a valid assignment. BF also minimizes max{X_i} - min{X_i}
//This works coz finally,d[i]<=d[j]+C_i for all constraints.
