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
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out

/*
 
 4/25/2018
 
 17:48-18:22 "1 1 1000000" does not pass... output string and passed 🤔
 
 Ok, iostream's default precision is `6` which is not enough if integer part is large. Nice to learn.
 
 Editorial: https://csacademy.com/contest/virtual36719/task/rhombus/solution/
 Simple solution by @kmjp: https://csacademy.com/submission/1512359/
 
 23:12-23:24 add simpler solution
 
 */

int main() {
  int D1,D2,K; cin>>D1>>D2>>K;
  REP(_,K) {
    if(D1>D2) swap(D1,D2);
    ++D1;
  }
  cout<<setprecision(6)<<fixed<<(LL)D1*D2*0.5<<endl;
// precision is enough
// cout<<(LL)D1*D2*0.5<<endl;
}

string solve_org(int D1, int D2, int K) {
  string s="";
  double res=0;
  REPE(x,K) {
    LL a=(1LL*D1+x)*(1LL*D2+K-x);
    double b=a*0.5;
    if(res<b) {
      res=b;
      s=to_string(a/2);
      if(a%2) s+=".5";
    }
  }
  return s;
}

int main_org() {
  int D1,D2,K;
  cin>>D1>>D2>>K;
  cout<<solve_org(D1,D2,K)<<endl;
  return 0;
}
