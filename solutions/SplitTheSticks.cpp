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
 
 24:35-25:05 AC
 
 Editorial:
  - https://csacademy.com/contest/round-84/task/split-the-sticks/solution/
  - http://drken1215.hatenablog.com/entry/2018/07/20/123100
 
 Summary:
  - Analysis is straightforward though, implementation is a bit nasty
 
 */

// 25:05 AC
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
LL A[MAX_N];
int N;

void solve() {
  LL sum=accumulate(A,A+N,0LL);
  if(sum%2==1) {
    cout<<-1<<endl;
    return;
  }
  
  vector<II> res;
  map<int,int> M;
  REP(i,N) M[A[i]]++;
  
  //FORR(kvp,M) dump2(kvp.first,kvp.second);
  
  while(SZ(M)>1) {
    auto hit=prev(M.end()),lit=M.begin();
    int l=lit->first,h=hit->first;
    res.emplace_back(h,l);
//    dump4(l,M[l],h,M[h]);
    M[l]--; if(M[l]==0) M.erase(l);
    M[h]--; if(M[h]==0) M.erase(h);
    M[h-l]++;
  }
  if(SZ(M)==1) {
    auto it=M.begin();
    int k=it->first,cnt=it->second;
    assert(k%2==0);
    if(cnt%2==1) res.emplace_back(k,k/2);
  }
  assert(SZ(res)<=N);
  cout<<SZ(res)<<endl;
  REP(i,SZ(res)) cout<<res[i].first<<' '<<res[i].second<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
