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

// $ cp-batch SugarelInLove | diff SugarelInLove.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SugarelInLove.cpp && ./a.out

/*
 
 2/20/2019
 
 8:47-9:23 AC
 
 http://drken1215.hatenablog.com/entry/2019/02/21/033300
  - dp in tree dp
 https://ferin-tech.hatenablog.com/entry/2019/02/21/FII_Code_Round_%231_Sugarel_in_Love
  - greedy in tree dp
 https://csacademy.com/contest/fii-code-2019-round-1/task/Sugarel-in-Love/solution/
 
 */

const int MAX_N=1e6+1;
vector<pair<LL,int>> G[MAX_N];
int N;

LL dp[MAX_N][2];
void dfs(int u, int pre) {
  vector<pair<LL,int>> X;
  LL pw=0;
  REP(i,SZ(G[u])) {
    int v=G[u][i].second;
    if(v==pre) pw=G[u][i].first;
    else {
      X.emplace_back(G[u][i]);
      dfs(v,u);
    }
  }
  int M=SZ(X);
  VV<LL> dp2(M+1,vector<LL>(3,0));
  REP(i,M)REP(j,3) {
    int v=X[i].second;
    if(j<2) SMAX(dp2[i+1][j+1],dp2[i][j]+dp[v][1]);
    SMAX(dp2[i+1][j],dp2[i][j]+dp[v][0]);
  }
  dp[u][0]=dp2[M][2];
  dp[u][1]=pw+dp2[M][1];
//  dump(u,dp[u][0],dp[u][1]);
}

void solve() {
  dfs(0,-1);
  cout<<dp[0][0]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N-1) {
    int u,v; LL w; cin>>u>>v>>w;
    --u,--v;
    G[u].emplace_back(w,v);
    G[v].emplace_back(w,u);
  }
  solve();
  
  return 0;
}
