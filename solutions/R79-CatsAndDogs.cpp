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
 
 24:13-24:39 AC
 
 Tweets:
  - https://togetter.com/li/1226014?page=2
  - https://twitter.com/tempura_pp/status/994262725067878401
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2000;
int N,M;
int X1[MAX_N],Y1[MAX_N],X2[MAX_N],Y2[MAX_N];
int cnt[MAX_N];

LL dist(int i, int j) {
  LL x=1LL*X1[j]-X2[i],y=1LL*Y1[j]-Y2[i];
  dump4(i,j,x,y);
  return x*x+y*y;
}

void solve() {
  ZERO(cnt);
  REP(i,M) {
    int minj=N-1;
    for(int j=N-1; j>=0; --j) {
      dump3(dist(i,j),dist(i,minj),j);
      if(dist(i,j)<=dist(i,minj)) {
        minj=j;
      }
    }
    dump2(i,minj);
    cnt[minj]++;
  }
  
  int res=0;
  REP(i,N) res+=(cnt[i]==1);
  cout<<res<<endl;
}

int main() {
  cin>>N>>M;
  REP(i,N) cin>>X1[i]>>Y1[i];
  REP(i,M) cin>>X2[i]>>Y2[i];
  solve();
  return 0;
}

