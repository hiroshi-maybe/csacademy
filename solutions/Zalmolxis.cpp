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
 
 9:26-11:25 First submit. However system is not working..
 16:40-17:16 figured out rule of replacement. redesigned algorithm and got AC
 
 Editorials:
  - https://csacademy.com/contest/round-85/analysis/
  - https://twitter.com/satanic0258/status/1024703847837589505
 
 Implementation of editorial: https://csacademy.com/submission/1634952/
  - Insert in the middle of sequence => std::list() is used
  - Generation of new elements => Just keep adding children (remove parent + add childrenx2 = total node is increasing by 1 👏)
 
 Summary:
  - Idea to use stack was nice
  - Implementation was painful
 
 */

// 11:25 submit
// 16:40-17:16 figured out rule of replacement. redesigned algorithm and got AC
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e6+1;
int P[MAX_N];
int N,K;

void dfs(int x, int cnt, VI &res) {
  if(cnt==0) return;
  if(__builtin_popcount(cnt)==1) {
    int cnt2=cnt;
    while(cnt) cnt>>=1,--x;
    REP(_,cnt2) res.push_back(x+1);
  } else {
    int cnt2=cnt^(cnt&(cnt-1));
    dfs(x-1,cnt2,res);
    cnt-=cnt2;
    dfs(x-1,cnt,res);
  }
}

void solve() {
  int S[MAX_N]={};
  int p=0;
  
  auto add = [&](int x) {
    S[p++]=x;
    while(p>=2&&S[p-2]==S[p-1]) {
      int y=S[p-1]+1;
      p-=2;
      S[p++]=y;
    }
  };
  
  vector<pair<int,int>> A;
  REP(i,N) {
    if(p>0&&S[p-1]<P[i]) {
      A.emplace_back(S[p-1],1);
      add(S[p-1]);
    }
    A.emplace_back(P[i],0);
    add(P[i]);
  }
  while(p>1||(p==1&&S[p-1]!=30)) {
    //assert(S[p-2]!=S[p-1]);
    A.emplace_back(S[p-1],1);
    add(S[p-1]);
  }
//  REP(i,SZ(A)) dump3(i,A[i].first,A[i].second);
//  dump2(p,S[p-1]);
  assert(p==1&&S[p-1]==30);
  
  int M=0;
  REP(i,SZ(A)) M+=A[i].second;
  VI res;
  int done=0;
  REP(i,SZ(A)) {
    if(A[i].second==0) {
      res.push_back(A[i].first);
      continue;
    }
    int x=A[i].first;
    int cnt=min(1<<x,K-(M-done-1));
    assert(cnt>=1);
    ++done;
//    dump2(x,cnt);
    K-=cnt;
    dfs(x,cnt,res);
  }
  REP(i,SZ(res)) cout<<res[i]<<(i==SZ(res)-1?'\n':' ');
}

void solve_org() {
  map<int,int> M;
  REP(i,N) M[P[i]]++;
  VI S;
  REP(x,30) if(M.count(x)) {
    if(M[x]%2==1) S.emplace_back(x);
    M[x+1]+=(M[x]+1)/2;
  }
  dumpAR(S);
  VI res;
  REP(i,N) res.push_back(P[i]);
  int SN=SZ(S);
  assert(SN<=K);
  REP(i,SN) {
    int x=S[i];
    int cnt=min(1<<x,K-(SN-i-1));
    assert(cnt>=1);
    dump2(x,cnt);
    K-=cnt;
    dfs(x,cnt,res);
    /*
    int y=0;
    while(cnt) {
      int go=cnt%2;
      cnt/=2;
      if(go) {
        REP(_,1<<y) res.push_back(cnt?x-y-1:x-y);
      }
      ++y;
    }*/
  }
  REP(i,SZ(res)) cout<<res[i]<<(i==SZ(res)-1?'\n':' ');
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  REP(i,N) cin>>P[i];
  solve();
  
  return 0;
}
