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
 
 22:02-22:31 pause
 
 4/27/2018
 
 10:50-11:10 give up
 
 11:10-11:30 read editorial and add solution
 
 Editorials:
  - https://csacademy.com/contest/round-77/task/expected-lcp/solution/
  - http://kmjp.hatenablog.jp/entry/2018/04/19/1000
 
   res
 = ∑ E[pos,char] } // Linearity of expectation
 = C(m,2)/C(N,2)
 
 I figured out above formula though, I didn't have an idea to compute `m` efficiently.
 I imagined that there is a way to compute `E[pos,char]` without looking at previous characters to achieve linear algorithm.
 However we DO look at previous chars. It's possible because of Trie tree.
 
 Key:
  - Trie tree
  - Sort
   - Same idea as Trie
   - Scanning strings from head to tail and grouping
 
 Summary:
  - I sticked to an idea to ignore previous characters 👎
  - I should have come up with Trie from "prefix"
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e6+1;
string S[MAX_N];
int N;
double res=0.0;

class TrieNode {
public:
  bool hasWord = false;
  vector<TrieNode *> children;
  vector<int> cnt;
  // Initialize your data structure here.
  TrieNode() {
    this->children = vector < TrieNode * > (26, NULL);
    this->cnt=vector<int>(26,0);
  }
};

class Trie {
public:
  Trie() {
    root = new TrieNode();
  }
  
  // Inserts a word into the trie.
  void insert(string word) {
    TrieNode *n = root;
    for(int i=0; i<word.size(); i++) {
      int w = word[i]-'a';
      TrieNode *next = n->children[w];
      if (next==NULL) {
        next = new TrieNode();
        n->children[w] = next;
      }
      n->cnt[w]++;
      n = next;
    }
    n->hasWord = true;
  }
  
  // Returns if the word is in the trie.
  bool search(string word) {
    TrieNode *n = find(word);
    
    return n!=NULL ? n->hasWord : false;
  }
  
  // Returns if there is any word in the trie
  // that starts with the given prefix.
  bool startsWith(string prefix) {
    TrieNode *n = find(prefix);
    
    return n!=NULL;
  }
  
  TrieNode* find(string s) {
    TrieNode *n = root;
    for(int i=0; i<s.size(); i++) {
      int w = s[i]-'a';
      TrieNode *next = n->children[w];
      if (next==NULL) {
        return NULL;
      }
      n = next;
    }
    
    return n;
  }
  
  void dfs() { dfs(root); }
  
  void release() {
    releaseNode(root);
  }
private:
  TrieNode* root;
  void dfs(TrieNode* n) {
    if(n==nullptr) return;
    REP(i,26) {
      int x=n->cnt[i];
      if(x>1) res+=1.0*x*(x-1)/N/(N-1);
      
      dfs(n->children[i]);
    }
  }
  
  void releaseNode(TrieNode* n) {
    if (!n) return;
    for(auto &c : n->children) releaseNode(c);
    delete n;
  }
};

int main() {
  cin>>N;
  REP(i,N) cin>>S[i];
  
  Trie* t=new Trie();
  REP(i,N) t->insert(S[i]);
  t->dfs();
  t->release();
  
  cout<<setprecision(7)<<fixed<<res<<endl;
  
  return 0;
}
