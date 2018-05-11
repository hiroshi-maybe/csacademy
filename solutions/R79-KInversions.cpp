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
 
 5/9/2018 R79 div2 only
 
 24:40-25:50 1WA for #12
 
 5/11/2018
 
 12:15-12:45 fix overflow bug and got ACC
 
 Tweets:
  - https://togetter.com/li/1226014?page=2
  - https://twitter.com/ei1333/status/994262105434963968
  - https://twitter.com/tempura_pp/status/994262725067878401
  - https://twitter.com/iwashi31/status/994262965221130240
  - https://twitter.com/ei1333/status/994264096580104193
  - https://twitter.com/tempura_pp/status/994264480484810753
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
LL N,K;
LL ch2(LL n) {
  if(n==0) return 0;
  return n*(n-1)/2;
}

VI solve() {
  vector<int> res(N);
  int l=0,r=N-1,n=1;
  while(n<=N) {
    LL x=ch2(r-l);
    if(K>x) {
      res[r]=n;
      --r;
      K-=N-n;
    } else {
      res[l]=n;
      ++l;
    }

    ++n;
  }
  
//  set<int> X(res.begin(),res.end());
//  dump4(l,r,n,SZ(X));
//  dumpAR(res);
  return res;
}

int genRandNum(int lb, int ub) {
  // Helper to generate random integer in range [lb, ub)
  int x = rand() % (int)(ub - lb);
  return x + lb;
}

int main() {
  cin>>N>>K;
  int KK=K;
  VI res=solve();

  REP(i,N-1) cout<<res[i]<<" ";
  cout<<res.back()<<endl;
/*
  while(true) {
    N=genRandNum(2,1e5+1);
    int KK=genRandNum(0,N*(N-1)/2+1);
    K=KK;
  
    res=solve();
    int x=0;
    REP(i,N) FOR(j,i+1,N) x+=res[i]>res[j];
    if(x!=KK) dump3(N,KK,x);
    assert(x==KK);
  }*/
  
  return 0;
}

