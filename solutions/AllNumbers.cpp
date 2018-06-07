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
 
 6/7/2018 R81 div2 A
 
 24:55-26:02 AC
 
 Editorial:
  - https://csacademy.com/contest/round-81/analysis/
 
 Summary:
  - I solved by myself though, I didn't know permutations of multiset
  - https://en.wikipedia.org/wiki/Permutation#Permutations_of_multisets
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 24:55-26:02 AC
const int MAX_N=51;
vector<vector<int>> C(MAX_N,VI(MAX_N,0));
int D[MAX_N];
int cnt[10]={};
int N;
const LL MOD=1e9+7;
vector<LL> P10(51,0);
void choose(LL N, vector<vector<int>> &C) {
  for(int i=0; i<=N; ++i) {
    C[i][0]=1;
    for(int j=1; j<=i; ++j) {
      // i chooses j
      C[i][j] = C[i-1][j]+C[i-1][j-1], C[i][j]%=MOD;
    }
  }
}
LL powmod(LL a, LL b) {
  assert(0<=a && a<MOD);
  assert(0<=b);
  
  LL res=1;
  for(LL mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a, res%=MOD;
    a*=a; a%=MOD;
  }
  return res;
}
LL modinv(LL a, LL p=MOD) {
  return powmod(a, p-2);
}
LL f() {
  LL res=0;
  
  int rem=N;
  LL co=1;
  REP(d,10) if(cnt[d]) {
    co=co*C[rem][cnt[d]]%MOD;
    rem-=cnt[d];
  }
  
  REP(i,N) REP(d,10) {
    dump4(i,d,cnt[d],P10[i]);
    LL a=(d*cnt[d])%MOD;
    a=a*P10[i]%MOD;
    a=a*co%MOD;
    a=a*modinv(N)%MOD;
    dump3(i,d,a);
    res+=a,res%=MOD;
  }
  return res;
}

void solve() {
  LL res=f();
  
  if(cnt[0]>0) {
    cnt[0]--;
    --N;
    res=res+MOD-f();
    res%=MOD;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>D[i];
  P10[0]=1;
  REP(i,50) P10[i+1]=P10[i]*10LL%MOD;
  ZERO(cnt);
  REP(i,N) cnt[D[i]]++;
  choose(N,C);
  dumpAR(cnt);
  solve();
  
  return 0;
}
