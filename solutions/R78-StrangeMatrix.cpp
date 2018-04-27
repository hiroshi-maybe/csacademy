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
 
 4/25/2018
 
 25:19-25:51 give up
 
 4/26/2018
 
 12:10-12:45, 14:00-15:00 read editorials
  - https://csacademy.com/contest/round-78/task/strange-matrix/solution/
  - https://twitter.com/satanic0258/status/989189194449731585
 
 Simple implementations:
  - https://csacademy.com/submission/1526877/ by writer
  - https://csacademy.com/submission/1533402/ by @Um_nik
  - https://csacademy.com/submission/1532317/ by @nuip
  - https://csacademy.com/submission/1533753/ by @kmjp
 
 16:45-18:58,21:10-21:40 add solution
 
 4/27/2018
 
 Add performance optimization.
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 25:51 give up

const int MAX_M=2e4+1, MAX_Q=2e4+1;
int A[5][MAX_M];
int R[MAX_Q],C[MAX_Q],T[MAX_Q];
int N, M, Q;

// ⚠️ Customize node of segment tree
struct Node {
  int dist[5][5];
  Node() {
    REP(i,N)REP(j,N) dist[i][j]=i==j?0:-1e9;
  }
  void setup(int j) {
    REP(i,N) this->dist[i][i]=A[i][j];
  }
  static Node IDE; // Identity element in monoid
};
// Merge operation should be associative A`op`(B`op`C) == (A`op`B)`op`C
Node Node::IDE=Node();
Node merge(const Node &a, const Node &b) {
  Node res=Node();
  REP(i1,N)REP(i2,N) {
    /*
    REP(x1,N) REP(x2,N) if(abs(x1-x2)<=1) {
      SMAX(res.dist[i1][i2],a.dist[i1][x1]+b.dist[x2][i2]);
    }*/
    REP(x,N) FORE(o,-1,1) if(0<=x+o&&x+o<N) SMAX(res.dist[i1][i2],a.dist[i1][x]+b.dist[x+o][i2]);
  }
  return res;
}
// ⚠️ Customize node of segment tree

struct SegmentTree {
public:
  int N__;
  // Put tree array outside the struct to avoid seg fault due to memory allocation of large size array
  Node Tree[4*MAX_M]; // Tree[1..2*N__-1] has values (Node[1]: left half, Node[2]: right half, ..)
  SegmentTree(int N) {
    int n=1;
    // Init by power of 2
    while(n<N) n<<=1;
    for(int i=0; i<2*n-1; ++i) Tree[i]=Node::IDE;
    this->N__=n;
  }
  
  // Initialize tree with `ns`
  void build(const vector<Node> &ns) {
    buildTree(ns,0,0,N__);
  }
  
  // Update k-th (0-indexed) value
  void update(int i, const Node &x) {
    updateTree(i,x,0,0,N__);
  }
  
  // query in range [L,R)
  Node query(int L, int R) {
    return queryTree(L,R,0,0,N__);
  }
private:
  void buildTree(const vector<Node> &ns, int i, int l, int r) {
    if (l==r-1) { Tree[i]=ns[l]; return; }
    
    int mid=l+(r-l)/2;
    buildTree(ns,2*i+1,  l,mid); // left child
    buildTree(ns,2*i+2,mid,  r); // right child
    
    Tree[i]=merge(Tree[2*i+1],Tree[2*i+2]);
  }
  
  void updateTree(int p, const Node &x, int i, int l, int r) {
    if (l==r-1) { Tree[i]=x; return; }
    
    int mid=l+(r-l)/2;
    if(p<mid) updateTree(p,x,2*i+1,  l,mid);
    else      updateTree(p,x,2*i+2,mid,  r);
    
    Tree[i]=merge(Tree[2*i+1],Tree[2*i+2]);
  }
  
  Node queryTree(int L, int R, int i, int l, int r) {
    // out of range
    if (r<=L||R<=l) return Node::IDE;
    
    // all covered
    if (L<=l&&r<=R) return Tree[i];
    
    // partially covered
    int mid=l+(r-l)/2;
    Node a=queryTree(L,R,2*i+1,  l,mid);
    Node b=queryTree(L,R,2*i+2,mid,  r);
    Node res=merge(a,b);
    return res;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M>>Q;
  REP(i,N) REP(j,M) cin>>A[i][j];
  
  SegmentTree ST(M);
  vector<Node> X;
  REP(j,M) {
    Node x=Node();
    x.setup(j);
    X.push_back(x);
  }
  ST.build(X);
  
  REP(i,Q) {
    int r,c,val;
    cin>>r>>c>>val;
    --r,--c;
    
    A[r][c]=val;
    Node x=Node();
    x.setup(c);
    
    ST.update(c,x);
    // Node y=ST.query(0,M);
    Node y=ST.Tree[0];
    int res=0;
    REP(i,N)REP(j,N) {
      SMAX(res,y.dist[i][j]);
    }
    cout<<res<<endl;
  }
  
  return 0;
}


