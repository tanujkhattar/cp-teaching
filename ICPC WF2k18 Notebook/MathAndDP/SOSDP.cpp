//Given an array A of 2^N integers,calculate ∀ x, F(x) = Sum of
//all A[i] such that x & i = i, i.e., i is a subset of x.
//dp[mask][i]:subsets where first i bits of mask can differ
REP(mask,(1<<N)){dp[mask][-1] = A[mask];//handle base case
  REP(i,N)if(mask&(1<<i))
      dp[mask][i] = /*-1*/dp[mask][i-1]+dp[mask^(1<<i)][i-1];
    else dp[mask][i] = dp[mask][i-1];//for MU (invers) -1 will
  }F[mask] = dp[mask][N-1];//come there.
}//memory optimized, super easy to code.
REP(i,(1<<N))F[i] = A[i];REP(i,N)REP(mask,(1<<N))
  if(mask&(1<<i))F[mask]+=F[mask^(1<<i)];
//note : to iterate over submasks of a mask use this
for(int s=m; s; s=(s-1)&m) //process 0 separately
//Zeta = SOS, MU = (-1) ^ |S / S'|,  MU . Z = I,
//Sigma F(S) = (-1)^|S| F(S). MU F = Sigma . Z . Sigma F,
//F'(k, X) : Sum of all subsets of size k of X. Compute in 
//O(n^2 2 ^ n) for every k by setting remaining 0 coz ind.
//F * G : Subset Convolution = MU(F o G(K, X)).
//F o G(K, X) = SUM(j <= k) f'(j, X) x g'(k - j, X) : k^2 M
