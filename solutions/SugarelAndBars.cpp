#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// stdout
#define println(args...) fprintf(stdout, ##args),putchar('\n');
// debug cerr
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch SugarelAndBars | diff SugarelAndBars.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SugarelAndBars.cpp && ./a.out

/*
 
 2/20/2019
 
 8:19-8:34 WA on test #16
 8:46 give up
 
 10:20 found algorithm bug from https://twitter.com/a3VtYQo/status/1098284553372762113
 
 https://csacademy.com/contest/fii-code-2019-round-1/task/sugarel-and-bars/solution/
 
 */

const int MAX_N=1e6+1;
VI G[MAX_N];
int N,M,X,Y;

void dfs(int u, SETI &viz) {
  if(viz.count(u)) return;
  viz.emplace(u);
  FORR(v,G[u]) dfs(v,viz);
}
void solve() {
  SETI vizx,vizy;
  dfs(X,vizx),dfs(Y,vizy);
  
  bool both=false;
  FORR(a,vizx) both|=vizy.count(a);
  
  REP(i,N) {
    int res=0;
    if(!vizx.count(i)&&!vizy.count(i)) {
      if(vizx.count(Y)||vizy.count(X)) res=1;
      else res=both?1:2;//res=2;
    } else if(!vizx.count(i)) res=1;
    else if(!vizy.count(i)) res=1;
    printf("%d ", res);
  }
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M>>X>>Y;
  --X,--Y;
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[v].push_back(u);
  }
  solve();
  
  return 0;
}
