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
 
 8/1/2018 R85
 
 8:34-9:25 ACC (1WA due to wrong inequality in sort comparator)
 
 Editorials:
  - https://csacademy.com/contest/round-85/analysis/
  - https://twitter.com/satanic0258/status/1024703847837589505
 
 */

// 1WA on #18
// 9:25 AC

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=50+1;
LL X[MAX_N];
int N;
LL A,B;

tuple<int,int,LL,LL> AA,BB;
vector<tuple<int,int,LL,LL>> XX;

tuple<int,int,LL,LL> norm(LL x) {
  LL y=x;
  int x2=0,x3=0;
  while(x%2==0) x/=2,x2++;
  while(x%3==0) x/=3,x3++;
  return {x2,x3,x,y};
}
LL rest(tuple<int,int,LL,LL> x) {
  return get<3>(x);
}

void solve() {
  AA=norm(A),BB=norm(B);
  XX.resize(N);
  REP(i,N) XX[i]=norm(X[i]);
  unordered_set<LL> S;
  S.emplace(get<2>(AA)),S.emplace(get<2>(BB));
  REP(i,N)S.emplace(get<2>(XX[i]));
  if(SZ(S)!=1) {
    cout<<-1<<endl;
    return;
  }
  sort(XX.begin(),XX.end(),[&](tuple<int,int,LL,LL> a, tuple<int,int,LL,LL> b) {
    if(get<0>(a)!=get<0>(b)) return get<0>(a)>get<0>(b);
    return get<1>(a)<get<1>(b);
  });
  XX.push_back(BB);
  
  int p=get<0>(AA),q=get<1>(AA);
  vector<LL> res={rest(AA)};
  REP(i,SZ(XX)) {
    int pp=get<0>(XX[i]),qq=get<1>(XX[i]);
    LL rem=get<2>(XX[i]);
    if(p>=pp&&q<=qq) {
      while(p>pp) res.push_back(rest({--p,q,rem,res.back()/2LL}));
      while(q<qq) res.push_back(rest({p,++q,rem,res.back()*3LL}));
      assert(p==pp&&q==qq);
    } else {
      cout<<-1<<endl;
      return;
    }
  }
  REP(i,SZ(res)) cout<<res[i]<<(i==SZ(res)-1?'\n':' ');
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>A>>B;
  REP(i,N) cin>>X[i];
  solve();
  
  return 0;
}

