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

// $ cp-batch ConfusedRobot | diff ConfusedRobot.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ConfusedRobot.cpp && ./a.out

/*
 
 3/13/2020
 
 9:49-11:05 give up
 
 3/15/2020
 
 15:30-17:35 read editorials and got AC
 
 https://csacademy.com/submission/2702937/
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.55bm5c376k8h
 
 */

const int MAX_N=500+1;
string A[MAX_N];
int N,M,L,Q,X,Y,Z;
string S;

II moves[26];
int J[MAX_N*MAX_N][101];
int nxt[MAX_N*MAX_N][40];

int pos(int i, int j) { return i*M+j; }

void sim(int si, int sj) {
  int i=si,j=sj;
  J[pos(si,sj)][0]=pos(i,j);
  REP(p,SZ(S)) {
    II move=moves[S[p]-'A'];
    int ii=i+move.first,jj=j+move.second;
    if(ii>=0&&ii<N&&jj>=0&&jj<M&&A[ii][jj]!='#') i=ii,j=jj;
    J[pos(si,sj)][p+1]=pos(i,j);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  moves['R'-'A']={0,1};
  moves['D'-'A']={1,0};
  moves['L'-'A']={0,-1};
  moves['U'-'A']={-1,0};

  cin>>N>>M>>Q;
  REP(i,N) cin>>A[i];
  cin>>S;
  
  L=SZ(S);
  REP(i,N)REP(j,M)REP(l,L) J[pos(i,j)][l]=pos(i,j);
  REP(i,N)REP(j,M)if(A[i][j]=='.') sim(i,j);
  REP(i,N)REP(j,M)nxt[pos(i,j)][0]=J[pos(i,j)][L];
  FOR(k,1,32)REP(i,N)REP(j,M) {
    int p=nxt[pos(i,j)][k-1];
    nxt[pos(i,j)][k]=nxt[p][k-1];
  }

  REP(i,Q) {
    cin>>X>>Y>>Z;
    --X,--Y;
    int p=pos(X,Y);
    int d=Z/L,r=Z%L;
//    dump(d,r);
    for(int k=31; k>=0; --k) {
      if((d>>k)&1) {
        p=nxt[p][k];
//        dump(k,p/M,p%M);
      }
    }
//    int x=J[pos(X,Y)][L];
//    int y=nxt[pos(X,Y)][0];
//    dump(x/M,x%M,y/M,y%M);
//    dump(p/M,p%M);
    
    int res=J[p][r];
    println("%d %d", res/M+1, res%M+1);
  }
  
  return 0;
}
