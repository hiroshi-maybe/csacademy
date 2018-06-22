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
 
 24:27-25:17 AC
 
 Editorial:
  - https://csacademy.com/contest/round-82/task/printer/solution/
 
 Tweets:
  - https://togetter.com/li/1239289
  - https://twitter.com/_TTJR_/status/1009482335253774337
   - binary search
  - https://twitter.com/satanic0258/status/1009485309065609216
   - binary search
  - https://twitter.com/drken1215/status/1009482987493253121
   - greedy
  - https://twitter.com/satanic0258/status/1009485309065609216
   - greedy
  - https://twitter.com/my316g/status/1009489144907587584
   - ternary search
 
 Suppose `x` bundles are bought. In the case, there are four intervals for total price:
 
 i1: [0, N1), y=p1*x+q1
 i2: [N1,N2), y=p2*x+q2
 i3: [N2,N3), y=p3*x+q3
 i4: [N3,N4), y=p4*x+q4
 
 Each interval forms a straight line. That means the smallest price should stay at one of endpoints of the intervals.
 => greedy algorithm works
 
 Summary:
  - I had no proof of trinary search (downward convex)
  - Greedy idea was hard for me to come up with. Making formula helps
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
//int A[MAX_N];
// 25:17 ACC
int N1,N2,N3,N4;
int P1,P2,P3,P4;
int P;

LL f(LL x) {
  return P*x+max(1LL*N1-x,0LL)*P1+max(1LL*N2-x,0LL)*P2+max(1LL*N3-x,0LL)*P3+max(1LL*N4-x,0LL)*P4;
}
void solve_ternarysearch() {
  LL l=0,r=1e9+10;
  while(abs(r-l)>2) {
    LL ll=l+(r-l)/3;
    LL rr=r-(r-l)/3;
    LL p1=f(ll),p2=f(rr);
    if(p1<p2) r=rr;
    else l=ll;
//    dump2(l,r);
  }
  cout<<min({f(l),f(l+1),f(r)})<<endl;
}

LL N[4],PP[4];
LL ff(LL x) {
  LL res=P*x;
  REP(i,4) res+=PP[i]*max(N[i]-x,0LL);
  return res;
}
void solve() {
  N[0]=N1,N[1]=N2,N[2]=N3,N[3]=N4;
  PP[0]=P1,PP[1]=P2,PP[2]=P3,PP[3]=P4;
  LL res=ff(0);
  REP(i,4) SMIN(res,ff(N[i]));
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N1>>N2>>N3>>N4;
  cin>>P1>>P2>>P3>>P4;
  cin>>P;
  solve();
  
  return 0;
}
