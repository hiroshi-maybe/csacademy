#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cerr
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 4/25/2018
 
 18:25-18:50,20:00-20:40 ACC
 
 Editorials:
  - https://csacademy.com/contest/virtual36719/task/two-rows/solution/
  - https://csacademy.com/submission/1511754/
 
 Ok. Actually my solution has redundant states in dp table.
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
LL A[2][100001];
LL F[2][100001][2],G[2][100001][2];
LL solve(int M) {
  F[1][M-1][1]=F[1][M-1][0]=G[1][M-1][0]=G[1][M-1][0]=A[1][M-1];
  F[0][M-1][0]=G[0][M-1][0]=A[1][M-1]+A[0][M-1];
  for(int j=M-2; j>=0; --j)for(int c=1; c>=0; --c)REP(i,2) {
    if(c==1) {
      F[i][j][1]=A[i][j]+G[i][j+1][0];
      G[i][j][1]=A[i][j]+F[i][j+1][0];
      dump4(i,j,F[i][j][1],G[i][j][1]);
    } else {
      F[i][j][0]=A[i][j]+max({G[i^1][j][1],G[i][j+1][0]});
      G[i][j][0]=A[i][j]+min({F[i^1][j][1],F[i][j+1][0]});
      dump4(i,j,F[i][j][0],G[i][j][0]);
    }
  }
  return G[0][0][0];
}

int main() {
  int M;
  cin>>M;
  REP(i,M) cin>>A[0][i];
  REP(i,M) cin>>A[1][i];
  cout<<solve(M)<<endl;
  return 0;
}
