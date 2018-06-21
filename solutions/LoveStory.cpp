
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
 
 6/21/2018 CSA R82
 
 24:05-24:26 AC
 
 Editorial:
  - https://csacademy.com/contest/round-82/task/love-story/solution/
 
 Tweets:
  - https://togetter.com/li/1239289
  - https://twitter.com/_TTJR_/status/1009482335253774337
  - https://twitter.com/satanic0258/status/1009485309065609216
 
 Submit solutions:
  - https://csacademy.com/submission/1618787/ by @kmjp
  - https://csacademy.com/submission/1618525/ by @anta
 
 Summary:
  - I did coordinate expansion to avoid place of real number
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 24:26 ACC
const int MAX_M=1e2+1;
int A[MAX_M];
int N,M;

void solve() {
  int tot=2*accumulate(A,A+M,0);
  int sum=0;
  int res=-1;
  REP(i,M) {
    sum+=2*A[i];
    if(sum==tot/2) {
      cout<<-1<<endl;
      return;
    }
    if(sum>=tot/2) {
      res=i+1;
      break;
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  REP(i,M) cin>>A[i];
  solve();
  return 0;
}
