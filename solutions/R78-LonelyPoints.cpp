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
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 4/25/2018
 
 24:10-24:33 ACC
 
 Summary:
  - analysis was straighforward. However I had implementation bug in copy&paste of X 😞
 
 Editorials:
  - https://csacademy.com/contest/round-78/task/lonely-points/solution/
  - https://twitter.com/satanic0258/status/989189194449731585
 
 Simple implementation:
  - https://csacademy.com/submission/1532309/
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
LL C[100001];
int main() {
  int N; string S;
  cin>>N;
  REP(i,N) cin>>C[i];
  
  LL res=1e9+10;
  
  vector<LL> X;
  FOR(i,1,N-1) X.push_back(abs(C[i]-C[i+1]));
  sort(X.begin(),X.end());
  LL x=X.back(); X.pop_back();
  X.push_back(x/2); X.push_back(x-x/2);
  
  res=min(res,*max_element(X.begin(),X.end()));

  vector<LL> Y;
  REP(i,N-2) Y.push_back(abs(C[i]-C[i+1]));
  sort(Y.begin(),Y.end());
  
  LL y=Y.back(); Y.pop_back();
  Y.push_back(y/2); Y.push_back(y-y/2);
  
  res=min(res,*max_element(Y.begin(),Y.end()));
  
  cout<<res<<endl;
  return 0;
}

