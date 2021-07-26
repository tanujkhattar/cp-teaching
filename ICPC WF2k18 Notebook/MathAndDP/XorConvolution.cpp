void convolve(LL P[], int N, bool inverse){
  for(int i = 2 ; i <= N ; i <<= 1){
    int m = i >> 1;
    int u , v , x , y;
    for(int j = 0 ; j < N ; j += i){
      for(int k = 0 ; k < m ; ++k){
        u = P[j + k];
        v = P[j + k + m];
        if(!inverse){
          P[j + k] = c0 * u + c1 * v;
          P[j + k + m] = c2 * u + c3 * v;
        }else {
          P[j + k] = d0 * u + d1 * v;
          P[j + k + m] = d2 * u + d3 * v;
        } }}}
}//For XOR, divide inverse by n finally.
//XOR: C = [+1, +1, +1, -1], D = [+1, +1, +1, -1]
//AND: C = [+0, +1, +1, +1], D = [-1, +1, +1, +0]
//OR : C = [+1, +1, +1, +0], D = [+0, +1, +1, -1]
