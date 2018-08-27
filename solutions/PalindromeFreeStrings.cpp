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
 
 8/28/2018 R86 div2
 
 8:55-9:25, 9:45-10:05 give up
 
 I knew that if "aa" or "aba" does not exist, it's palindrome free.
 However I didn't know how to find minimal number of changes to achieve it.
 I tried to solve by greedy. However it didn't work. Counter example: "ababa" => 2 ("abxya")
 
 8/26/2018
 
 24:00-25:00 read editorials and add solution
 
 Editorials:
  - http://naoyat.hatenablog.jp/entry/CSAcademyRound86Div2
  - https://twitter.com/kroton_pc/status/1033404578962661376
 
 Tweets:
  - https://togetter.com/li/1259297
  - https://twitter.com/satanic0258/status/1032314744244293632
  - https://twitter.com/hogeover30/status/1032313630404923393
  - https://twitter.com/gzlcp/status/1032313064865988608
  - https://twitter.com/gzlcp/status/1032314472386330626
 
 Greedy solutions:
  - https://csacademy.com/submission/1727743/ by @Benq
  - https://csacademy.com/submission/1729362/ by @kmjp
  - https://csacademy.com/submission/1729560/ by @TangentDay
 
 dp solutions:
  - https://csacademy.com/submission/1729886/ by @natsugiri
  - https://csacademy.com/submission/1729651/ by @fanache99
  - https://csacademy.com/submission/1729527/ by @uwi
 
 DP solutions are brute-forcing all the tuples of characters in three consecutive elements.
 Looking at neighbouring two characters is sufficient to avoid "aa" or "aba".
 If S[i-2] changes from original one, cost is `1`. Same for S[i-1] as well.
 dp[i][a][b] is showing cost when S[i-2]='a'+a and S[i-1]='a'+b.
 We are putting `c` in range of [a,z] at S[i].
 If it collides to 'a'+a or 'a'+b, it's not allowed. Thus dp[i+1][b][c] is Inf.
 Otherwise, dp[i+1][b][c] = dp[i][a][b] + cost to change S[i], which is 1 if S[i]!='a'+c.
 
 Summary:
  - Just remembering all ths patterns in relevant positions is typical dp idea. I should have come up with it...
 
 */

// 9:22 1WA
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=3e2+1;
string S;
int ng[26]={};
void solve_wrong() {
  int res=0;
  int N=SZ(S);
  REP(i,N) {
    int l=max(0,i-2),r=min(N,i+3);
    ZERO(ng);
    FOR(j,l,r) if(i!=j) {
      ng[S[j]-'a']++;
    }
    if(ng[S[i]-'a']) REP(j,26) if(!ng[j]) {
      S[i]='a'+j;
      ++res;
      break;
    }
  }
  dump2(res,S);
  cout<<res<<endl;
}

int memo[MAX_N][MAX_N];

int f(int l, int r) {
  if(r<=l) return 0;
  int &res=memo[l][r];
  if(res>=0) return res;
  
  res=r-l+1;
  FORE(i,l,r-1) {
    if(S[i]==S[i+1]) {
      SMIN(res,1+f(l,i-1)+f(l+2,r));
    } else if(i>l&&S[i-1]==S[i+1]) {
      SMIN(res,1+f(l,i-2)+f(l+2,r));
    } else {
      SMIN(res,f(l,i-1)+f(i+1,r));
    }
  }
  return res;
}

void solve_wrong2() {
  MINUS(memo);
  int N=SZ(S);
  cout<<f(0,N-1)<<endl;
}

int dp[MAX_N][26][26]={};
void solve() {
  int N=SZ(S);
  const int Inf=1e5;
  REPE(i,N)REP(j,26)REP(k,26) dp[i][j][k]=Inf;
  REP(a,26)REP(b,26)dp[2][a][b]=(S[0]!='a'+a)+(S[1]!='a'+b);
  FOR(i,2,N)REP(a,26)REP(b,26)REP(c,26) {
    if(a==b) continue;
    if(b==c) continue;
    if(c==a) continue;
    SMIN(dp[i+1][b][c],dp[i][a][b]+(S[i]!='a'+c));
  }
  int res=Inf;
  REP(a,26)REP(b,26)SMIN(res,dp[N][a][b]);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>S;
  solve();
  return 0;
}
