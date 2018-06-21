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
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 6/21/2018
 
 14:15-15:15 1WA
 15:15-15:30 give up
 15:45-16:10 read tweets and got AC
 
 Maximum number can be computed by maintaining used numbers in K-window.
 I thought that max{B[i]}! is the result. However that's just a part of the result...
 
 Suppose we have interval [i,i+K). Now we are interested in new interval [i+1,i+K+1).
 If A[i+K] is new number in the latter interval, we can choose arbitrary number out of max{B[i]} - (SZ(M)-1).
 Thus we keep multiplying in every new interval if it's a new number.
 This gives more sequences than max{B[i]}! because max{B[i]}! is fixing the number in a new interval.
 
 Tweets:
  - https://togetter.com/li/1239289
  - https://twitter.com/_TTJR_/status/1009482420788187136
  - https://twitter.com/my316g/status/1009482774166663170
  - https://twitter.com/drken1215/status/1009482987493253121
 
 @kmjp's simple code: https://csacademy.com/submission/1622383/
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int A[MAX_N];
int N,K;
const LL MOD=1e9+7;
void solve() {
  MAPII M;
  REP(i,K) M[A[i]]++;
  int maxs=SZ(M);
  FOR(i,K,N) {
    int a=A[i-K],b=A[i];
    M[a]--;
    if(M[a]==0) M.erase(a);
    M[b]++;
    SMAX(maxs,SZ(M));
  }
  
//  dump(maxs);

  M.clear();
  LL res=1LL;
  REP(i,K) M[A[i]]++;
  REP(i,SZ(M)) res*=(maxs-i),res%=MOD;
  FOR(i,K,N) {
    int a=A[i-K],b=A[i];
    M[a]--;
    if(M[a]==0) M.erase(a);
    M[b]++;
    if(M[b]==1) res*=maxs-(SZ(M)-1),res%=MOD;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
