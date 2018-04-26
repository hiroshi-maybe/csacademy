#include <iostream>
#include <iomanip>
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
 
 4/25/2018
 
 24:34-25:18 ACC
 
 Editorials:
  - https://csacademy.com/contest/round-78/task/banned-digits/solution/
  - https://twitter.com/satanic0258/status/989189194449731585
 
 Solution without dp:
  - https://csacademy.com/submission/1535175/
 
 Summary:
  - this is very typical digit dp
  - It took more time than expected to figure out how to handle leading zero 👎
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
int NG[10];
LL memo[20][2][2];
string S;
int N;
LL f(int p, bool any, bool init) {
  LL &res=memo[p][any][init];
  if(res>=0) return res;
  if(p==N) return 1LL;
  res=0;
  int D=S[p]-'0';
  int st=init?1:0;
  FOR(d,st,10) if(!NG[d]) {
    if(D<d) {
      if(!any) continue;
      res+=f(p+1,true,false);
    } else if(D==d) {
      res+=f(p+1,any,false);
    } else {
      // D>d
      res+=f(p+1,true,false);
    }
  }
  return res;
}

int main() {
  REP(i,10) cin>>NG[i];
  LL SS;
  cin>>SS;
  --SS;
  S=to_string(SS);
  N=SZ(S);
  MINUS(memo);
  LL res=0;
  REP(i,N) res+=f(i,i>0,true);
  cout<<res+(NG[0]?0:1)<<endl;
  return 0;
}
