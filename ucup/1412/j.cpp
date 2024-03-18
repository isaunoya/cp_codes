#include <bits/stdc++.h>
#include <codecvt>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep1(a) for (int i = 0; i < a; i++)
#define rep2(i, a) for (int i = 0; i < a; i++)
#define rep3(i, a, b) for (int i = a; i < b; i++)
#define rep4(i, a, b, c) for (int i = a; i < b; i += c)
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)

#define pb emplace_back
using namespace std;
template <typename T, typename T2> void cmin(T &x, const T2 &y) {
  x = x < y ? x : y;
}
template <typename T, typename T2> void cmax(T &x, const T2 &y) {
  x = x > y ? x : y;
}
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
template <class T> using vc = vector<T>;
template <class T> using pq = priority_queue<T>;
template <class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
mt19937 rng(time(NULL));
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define fi first
#define se second

struct unionfind {
  vector<int> p;
  unionfind(int N) { p = vector<int>(N, -1); }
  int root(int x) { return p[x] < 0 ? x : p[x] = root(p[x]); }
  bool same(int x, int y) { return root(x) == root(y); }
  void unite(int x, int y) {
    x = root(x);
    y = root(y);
    if (x != y) {
      if (p[x] < p[y]) {
        swap(x, y);
      }
      p[y] += p[x];
      p[x] = y;
    }
  }
  int size(int x) { return -p[root(x)]; }
};

void solve() {
  int n,m;
  cin >> n >> m;
  vc<vi> g(n);
  unionfind f(n);
  vc<pii> e(m);
  rep(i,m){
    int x,y;
    cin>>x>>y;
    --x;
    --y;
    e[i]={x,y};
    g[x].pb(y);
    g[y].pb(x);
    f.unite(x,y);
  }

  int ans=0;
  rep(i,n){
    if(f.root(i)==i){
      if(f.size(i)%2==0){
        ans^=2;
      }else{
        ans^=1;
      }
    }
  }

  int r=-1;
  vi rt(n,-1);
  vi s(n);
  auto dfs=[&](auto &self,int u,int p)->void{
    s[u]=1;
    rt[u]=r;
    for(auto v:g[u]){
      if(v==p)continue;
      self(self,v,u);
      s[u]+=s[v];
    }

  };

  rep(i,n)if(rt[i]==-1){
    r=i;
    dfs(dfs,i,-1);
  }

  int cnt=0;
  for(auto [x,y]:e){
    int sz1=min(s[x],s[y]);
    int sz2=s[rt[x]]-sz1;
    int res=ans;
    if(s[rt[x]]%2==0)res^=2;
    else res^=1;
    if(sz1%2==0)res^=2;
    else res^=1;
    if(sz2%2==0)res^=2;
    else res^=1;
    if(!res)cnt+=1;
  }

  rep(i,n){
    int res=ans;
    r=rt[i];
    int ss=s[r];
    if(ss%2==0)res^=2;
    else res^=1;
    // debug(i,ss);
    for(auto j:g[i]){
      if(s[j]>s[i]){
        int sz=ss-s[i];
        // debug(sz);
        if(sz%2==0)res^=2;
        else res^=1;
      }else{
        int sz=s[j];
        // debug(sz);
        if(sz%2==0)res^=2;
        else res^=1;
      }
    }
    // debug(res);
    if(!res)cnt+=1;
  }
  cout<<cnt<<"\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}