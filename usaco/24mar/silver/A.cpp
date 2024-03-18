#if defined(LOCAL)
#include <D:/cp/templates/my_template_compiled.hpp>
#else
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
#include <bits/stdc++.h>
#define debug(...) 42
#define rep1(a) for (auto i = 0; i < a; i++)
#define rep2(i, a) for (auto i = 0; i < a; i++)
#define rep3(i, a, b) for (auto i = a; i < b; i++)
#define rep4(i, a, b, c) for (auto i = a; i < b; i += c)
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
template <typename T> using vc = vector<T>;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
mt19937 rng(time(NULL));
const int INF = 1000000000;
const ll LNF = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define fi first
#define se second
#endif

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
  int N, K;
  cin >> N >> K;
  vi p(N);
  rep(i, N) cin >> p[i];
  map<ll, vl> g, id;
  vl lst(K, 0LL);
  priority_queue<pll, vc<pll>, greater<>> q;
  rep(i, K) q.emplace(0, i);
  rep(j, N) {
    auto [d, i] = q.top();
    q.pop();
    g[d + p[j]].emplace_back(d);
    id[d + p[j]].emplace_back(i);
    q.emplace(lst[i] = d + p[j], i);
  }
  unionfind f(K);
  int mn = 0;
  rep(i, K) {
    if (lst[i] < lst[mn]) {
      mn = i;
    }
  }
  set<ll> w;
  auto dfs = [&](auto &dfs, ll t) ->void {
    if (t == 0) {
      return;
    }
    if (w.count(t)) {
      return;
    }
    w.emplace(t);
    for (auto j : g[t]) {
      dfs(dfs, j);
    }
  };
  dfs(dfs, lst[mn]);
  for (auto [x, y] : id) {
    if (!w.count(x)) {
      continue;
    }
    int u = y[0];
    for (auto v : y) {
      f.unite(u, v);
    }
  }
  cout << lst[mn] << "\n";
  string ans = "";
  rep(i, K) {
    if (f.same(i, mn)) {
      ans += "1";
    } else {
      ans += "0";
    }
  }
  cout << ans << "\n";
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