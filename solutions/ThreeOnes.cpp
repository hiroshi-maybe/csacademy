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
 
 7/18/2018 CSA #84
 
 24:17-24:34 AC
 
 7/24/2018
 
 15:00-15:42 read editorial code and add the solution
 
 Editorial:
  - https://csacademy.com/contest/round-84/task/three-ones/solution/
   - deque to keep positions of dividors
  - http://drken1215.hatenablog.com/entry/2018/07/20/123000
   - two pointers
 
 Editorial's solution is using property of possible maximal intervals as below:
 
 1. (1),0,..,1,..,1,..,1
 2. 1,..,1,..,1,..,0,(1)
 3. (1),1,..,1,..,1,(1)
 
 Note that (1),0,..,1,..,1,..,1,..,0,(1) cannot be maximal interval because pattern #1 or #2 is more optimal.
 This shows that we can keep tracking position of `1`s to find relevant intervals.
 Corner case is edge of the string. We can put -1 and N as sentinels.
 
 Summary:
  - solved by two pointers
 
 */

// 24:34 AC
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=5e5+1;
int N;
string S;

void solve_org() {
  int cnt=0,L=N-1;
  for(; L>=0&&cnt<3; --L) cnt+=S[L]=='1';
  int res=N-L-1;
  int r=0; cnt=0;
//  dump2(S,L);
  REPE(i,L) {
    while(r<N&&cnt<3) cnt+=S[r++]=='1';
//    dump3(i,r,cnt);
    assert(cnt==3);
    SMAX(res,r-i);
    cnt-=S[i]=='1';
  }
  cout<<res<<endl;
}

void solve() {
  VI P; P.push_back(-1);
  REP(i,N) if(S[i]=='1') P.push_back(i);
  P.push_back(N);
  int res=-1;
  FOR(i,3,SZ(P)) SMAX(res,P[i]-P[i-3]);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>S;
  solve();
  
  return 0;
}
