#include <bits/stdc++.h>
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

void solve() {
  int n, m;
  cin >> n >> m;
  vc<pii> e(m);
  vi deg(n);
  rep(i,m){
    int u,v;
    cin>>u>>v;
    deg[u]++;
    deg[v]++;
    e[i]=pii(u,v);
  }
  vc<vi> g(n);
  for(auto[u,v]:e){
    if(u>v)swap(u,v);
    if(deg[u]<=deg[v]){
      g[u].pb(v);
    }else{
      g[v].pb(u);
    }
  }
  // debug(g);
  vi cnt(n);
  // int ans=0;
  vi ans(n);
  rep(u,n){
    for(auto v:g[u])cnt[v]=1;
    for(auto v:g[u])for(auto w:g[v]){
      if(cnt[w]){
        ans[u]++;
        ans[v]++;
        ans[w]++;
        // ans+=1;
      }
    }
    for(auto v:g[u])cnt[v]=0;
  }
  long long res = 0;

  rep(u,n){
    for(auto v:g[u]){
      for(auto w:g[v]){
        
      }
    }
  }
  // debug(ans);
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