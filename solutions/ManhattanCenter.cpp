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
 
 25:10-25:50 time is up
 
 7/24/2018
 
 17:30-18:00 Read editorials
 
 7/25/2018
 
 10:45-13:15, 14:30-15:08 Read editorials and got AC
 
 Editorial:
  - https://csacademy.com/contest/round-84/task/manhattan-center/solution/
  - http://par.hateblo.jp/entry/2018/07/21/191248
   - great description of the solution 👏
  - http://omochan.hatenablog.com/entry/2018/07/20/233156
 
 Submit solutions:
  - https://csacademy.com/submission/1672287/
   - ternary search by @TAISA
  - https://csacademy.com/submission/1666408/
   - Fenwick tree by @izban
  - https://csacademy.com/submission/1669877/
   - Fenwick tree by @ainta
  - https://csacademy.com/submission/1666005/
   - ordered set by @LHiC
 
 Key:
  - optimal `x` is x coordinate of one of the given `N` points
  - maitain two groups `A` with optimal `K` points and `B` with others (sweep line)
   - from small `x` to large `x`, small values in `B` is getting better candidate
   - move better points from `B` to `A` with invariant |A| = K
   - once point moves to `B`, it never gets back to `A` (amortized O(N))
   - replace p_a∈A with p_b∈B if (y_a - x_a) + x > (y_b + x_b) - x
    - this is sufficient because we are moving x from small to large
    - Removed value should be left to `x`. Added value should be right to `x`
  - sum of y-coordinate is independent of `x`
  - sum of x-coordinate is |L|*x - sum{L} + |R|*-x + sum{R} where L={p.x<=x, p∈A}, R={p.x>x, p∈A}
 
  |---------------|
  |               |
  |     /\        |
  |    /A \   B   |
 ------------------------>
         ^x
 
 Summary:
  - I had an idea to have two queues. However I couldn't progress further
  - Deeper analysis is necessary. Two queues should come from an idea that comparison of (y_l - x_l) + x and (y_r + x_r) -x matters
  - Make formulas and figure out what data structure is necessary
  - The most difficult part is how to define two sets and
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
pair<LL,LL> P[MAX_N];

struct BIT {
public:
  int N;
  vector<int> T; // T[1..N] has values (1-based index)
  BIT(int N): N(N) {
    T.resize(N+1,0);
  }
  
  // query in [0,r] : ∑ { sum[i] : i=0..r }
  int query(int r) {
    ++r; // 0-based index to 1-based index
    int res=0;
    while(r>0) {
      res+=T[r];
      r-=lsone(r);
    }
    return res;
  }
  
  // query ∑ { sum[i] : i=l..r }
  int query(int l, int r) {
    assert(l<=r&&0<=l&&r<N);
    return query(r)-query(l-1);
  }
  
  // sum[i]+=x
  void add(int i, int x) {
    assert(0<=i&&i<=N);
    ++i; // 0-based index to 1-based index
    while(i<=N) {
      T[i]+=x;
      i+=lsone(i);
    }
  }
  
  // sum[i]=x
  void update(int i, int x) {
    int v1=query(i)-query(i-1);
    add(i,x-v1);
  }
  
  // compute total inversions
  int inversions(vector<int> ns) {
    int N=ns.size(),res=0;
    for(int i=N-1; i>=0; --i) {
      // Count elements which stays in right side and smaller
      res+=query(ns[i]-1);
      add(ns[i],1);
    }
    return res;
  }
private:
  int lsone(int i) { return i&-i; }
};

BIT cntA(MAX_N),sumA(MAX_N);

void solve(int N, int K) {
  set<LL> S;
  REP(i,N) S.emplace(P[i].first);
  vector<LL> X(S.begin(),S.end());
  auto xid = [&](int x) {
    return lower_bound(X.begin(),X.end(),x)-X.begin();
  };
  
  priority_queue<pair<LL,int>> QA;
  priority_queue<pair<LL,int>, vector<pair<LL,int>>, greater<pair<LL,int>>> QB;
  REP(i,N) QB.emplace(P[i].first+P[i].second,i);
  
  LL disty=0;
  auto addA = [&](int i) {
    QA.emplace(P[i].second-P[i].first,i);
    cntA.add(xid(P[i].first),1);
    sumA.add(xid(P[i].first),P[i].first);
//    dump3("add",xid(P[i].first),P[i].first);
    disty+=P[i].second;
  };
  auto remA = [&](int i) {
    assert(QA.top().second==i);
    QA.pop();
    cntA.add(xid(P[i].first),-1);
    sumA.add(xid(P[i].first),-P[i].first);
    disty-=P[i].second;
  };
  auto dist = [&](int id) {
    LL x=X[id];
    int cntl=cntA.query(id),cntr=cntA.query(id+1,SZ(X));
    LL suml=sumA.query(id),sumr=sumA.query(id+1,SZ(X));
    LL l=cntl*x-suml;
    LL r=cntr*(-x)+sumr;
//    dump3(id,cntl,cntr);
//    dump3(id,suml,sumr);
//    dump4(id,l,r,disty);

    return disty+l+r;
  };
  
  while(SZ(QA)<K) {
    int i=QB.top().second;
    QB.pop();
    addA(i);
  }
  
  LL res=1e16;
  REP(id,SZ(X)) {
    int x=X[id];
    while(SZ(QA)&&SZ(QB)&&QA.top().first+x>QB.top().first-x) {
      int i1=QB.top().second,i2=QA.top().second;
      remA(i2),addA(i1);
      QB.pop();
      assert(SZ(QA)==K);
    }
    LL d=dist(id);
    dump3(id,x,d);
    SMIN(res,d);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int N,K;
  cin>>N>>K;
  REP(i,N) {
    LL x,y;
    cin>>x>>y;
    P[i]={x,y};
  }
  solve(N,K);
  
  return 0;
}
