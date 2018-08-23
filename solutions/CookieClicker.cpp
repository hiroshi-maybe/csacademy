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
 
 8/22/2018 R86 div2 B
 
 8:20-8:52 1WA
 9:20-9:45 give up
 
 Simple implementation by @kmjp: https://csacademy.com/submission/1728608/
 
 Summary:
  - implementation mistake 😡
  - step-by-step simulation is better if it fits in constraint. See @kmjp's solution
 
 */

// 8:52 1WA
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=5+1;
int N,C,S;
int A[MAX_N],B[MAX_N];
void solve() {
  int res=(C+S-1)/S;
  FOR(mask,1,1<<N) {
    VI P;
    REP(i,N) if((mask>>i)&1) P.push_back(i);
    do {
//      dumpAR(P);
      int t=0,cur=0,s=S;
      REP(i,SZ(P)) {
        int a=B[P[i]],b=A[P[i]];
        int dur=(b-cur+s-1)/s;
        // this mistake messed up 😡😡😡😡😡
        //cur=s*dur-b;
        assert(dur>=0);
        cur+=s*dur-b;
        assert(cur>=0);
        t+=dur;
        s+=a;
      }
      if(cur>=C) SMIN(res,t);
      else {
        int dur=(C-cur+s-1)/s;
        t+=dur;
        SMIN(res,t);
      }
    } while(next_permutation(P.begin(),P.end()));
  }
  cout<<res<<endl;
}

/*
void solve() {
  int res=1e7;
  
  VI P;
  REP(i,N) P.push_back(i);
  do {
    dumpAR(P);
    int t=0,cur=0,s=S;
    REP(i,SZ(P)) {
      int a=B[P[i]],b=A[P[i]];
      int dur=(b-cur+s-1)/s;
      
      if(cur+s*dur>=C) break;
      
      cur=s*dur-b;
      t+=dur;
      dump4(i,dur,s,t);
      s+=a;
    }
    if(cur>=C) SMIN(res,t);
    else {
      int dur=(C-cur+s-1)/s;
      t+=dur;
      SMIN(res,t);
    }
    dump4(mask,s,t,cur);
    
  } while(next_permutation(P.begin(),P.end()));

  cout<<res<<endl;
}*/

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>C>>S;
  REP(i,N) cin>>A[i]>>B[i];
  solve();
  return 0;
}
