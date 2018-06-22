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
 
 25:18-26:10 AC
 
 Tweets:
  - https://togetter.com/li/1239289
  - https://twitter.com/_TTJR_/status/1009482335253774337
  - https://twitter.com/drken1215/status/1009482987493253121
  - deque
   - https://twitter.com/satanic0258/status/1009485309065609216
   - https://twitter.com/satanic0258/status/1009487158808272896
 
 https://csacademy.com/submission/1620121/
  - yutaka1999's simple code
  - keeping pointer of left and right of only current position
  - accumulating cost of intermediate nodes
 
 Summary:
  - 5 mins late to solve this problem
   - circular cumulative sum was a bit tricky
   - maintenance of doubly linked list came from @tourist's code in different problem
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
LL D[MAX_N];
LL pre[MAX_N];
LL nex[MAX_N];
LL cum[MAX_N];
int N,S;

// 26:10 AC
LL dist(int i, int j, bool forw) {
  assert(i!=j);
  if (forw) {
    if(i<j) return cum[j]-cum[i];
    else return cum[j]+cum[N]-cum[i];
  } else {
    if(i>j) return cum[i]-cum[j];
    else return cum[N]-cum[j]+cum[i];
  }
}
void solve() {
  pre[0]=N-1,nex[N-1]=0;
  FOR(i,1,N) pre[i]=i-1;
  REP(i,N-1) nex[i]=i+1;
  cum[0]=0;
  REP(i,N) cum[i+1]=cum[i]+D[i];
  int cnt=0;
  LL res=0;
  int cur=S;
  while(cnt<N-1) {
//    dump4(cur,res,pre[cur],nex[cur]);
    LL d1=dist(cur,nex[cur],true),d2=dist(cur,pre[cur],false);
//    dump2(d1,d2);
    bool forw=true;
    if(d1==d2) {
      int cur2=min(nex[cur],pre[cur]);
      if(cur2==nex[cur]) forw=true;
      else forw=false;
    } else if(d1<d2) {
      forw=true;
    } else {
      forw=false;
    }
    if(forw) {
      res+=d1;
      int cur2=nex[cur];
      pre[cur2]=pre[cur];
      cur=cur2;
    } else {
      res+=d2;
      int cur2=pre[cur];
      nex[cur2]=nex[cur];
      cur=cur2;
    }
    ++cnt;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>S;
  --S;
  REP(i,N) cin>>D[i];
  solve();
  
  return 0;
}
