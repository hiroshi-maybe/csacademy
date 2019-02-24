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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch SugarelsGarden | diff SugarelsGarden.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SugarelsGarden.cpp && ./a.out

/*
 
 2/20/2019
 
 9:24-10:05 give up
 
 I couldn't reduce runtime from O(N^4) to count # of points inside a triangle..
 
 2/23/2019
 
 12:20-16:00 read editorials, implement and got WA
 
 2/24/2019
 
 10:50-12:03 read editorials and got AC
 
 http://kmjp.hatenablog.jp/entry/2019/02/23/0930
 http://drken1215.hatenablog.com/entry/2019/02/21/225700
 
 I had an idea to divide points by segment with cross product.
 However I didn't come up with doing it by filtering x coordinate.
 
 */

struct Point {
public:
  int x, y;
  Point(): x(0), y(0) {}
  Point(int x, int y): x(x), y(y) {}
  Point(pair<int,int> p): x(p.first), y(p.second) {}
  Point(pair<int,int> p, pair<int,int> org): Point(p.first-org.first, p.second-org.second) {}
  Point(Point p, Point org): Point(p.x-org.x, p.y-org.y) {}
  
  explicit operator bool() const { return x!=0||y!=0; }
  Point operator-() const { return Point(0,0)-*this; }
  Point &operator+=(Point that) { x+=that.x,y+=that.y; return *this; }
  Point &operator-=(Point that) { x-=that.x,y-=that.y; return *this; }
  Point operator+(Point that) const { return Point(*this)+=that; }
  Point operator-(Point that) const { return Point(*this)-=that; }
  bool operator==(Point that) const { return x==that.x&&y==that.y; }
  bool operator!=(Point that) const { return !(Point(*this)==that); }
  bool operator<(Point that) const { return pair<int,int>(x,y)<pair<int,int>(that.x,that.y); }
  bool operator>(Point that) const { return pair<int,int>(x,y)>pair<int,int>(that.x,that.y); }
  bool operator<=(Point that) const { return Point(*this)==that||Point(*this)<that; }
  bool operator>=(Point that) const { return Point(*this)==that||Point(*this)>that; }
  friend std::ostream& operator<<(std::ostream& _os, const Point& _p) { return _os<<"{"<<_p.x<<','<<_p.y<<"}"; }
  
  long long distance() {
    return x*x + y*y;
  }
};
long long det(Point u, Point v) {
  return (LL)u.x*v.y - (LL)u.y*v.x;
}
long long det(Point origin, Point p1, Point p2) {
  return det(p1-origin, p2-origin);
}
long long area(Point p1, Point p2, Point origin) {
  return abs(det(origin,p1,p2));
}

const int MAX_N=301+1;
LL X[MAX_N],Y[MAX_N];
LL A[2][MAX_N];
int cnt[MAX_N][MAX_N];
int N,M;

const LL Inf=1e17;

vector<Point> ps;
int f(int a, int b, int c) {
  if(a>b) swap(a,b);
  if(b>c) swap(b,c);
  if(a>b) swap(a,b);
  assert(a<b&&b<c);
  assert(a<SZ(ps)&&b<SZ(ps)&&c<SZ(ps));
  int res;
  if(det(ps[a],ps[c],ps[b])>0) {
    res=cnt[a][b]+cnt[b][c]-cnt[a][c];
  } else {
    res=cnt[a][c]-cnt[a][b]-cnt[b][c]-1;
  }
  return res;
}

void solve() {
  REP(i,N) ps.emplace_back(X[i],Y[i]);
  sort(ALL(ps),[](Point &a, Point &b) {
    if(a.x==b.x) return a.y>b.y;
    return a.x<b.x;
  });
  ZERO(cnt);
  REP(j,N)REP(i,j) {
    Point p1=ps[i],p2=ps[j];
    FOR(k,i+1,j) {
      assert(p1.x<=ps[k].x&&ps[k].x<=p2.x);
      if(det(p1,p2,ps[k])<0) cnt[i][j]++;
    }
  }
  
  LL res=Inf;
  REP(j,N)REP(i,j) {
    REP(p,2)REP(k,MAX_N) A[p][k]=Inf;
    Point p1=ps[i],p2=ps[j];
    
    REP(k,N) if(k!=i&&k!=j) {
      Point p3=ps[k];
      SMIN(A[det(p1,p2,p3)>0][f(i,j,k)],area(p1,p2,p3));
    }
    REPE(x,M) {
      int y=M-x;
      LL a1=A[0][x],a2=A[1][y];
      SMIN(res,a1+a2);
    }
  }

  cout<<res*0.5<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(1)<<fixed;
  
  cin>>N>>M;
  REP(i,N) cin>>X[i]>>Y[i];
  solve();
  
  return 0;
}
