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
#define all(x) begin(x), end(x)
#define fi first
#define se second

void solve() {
  int q;
  cin >> q;
  vc<vi> g(1);
  vc<vi> qq(q);
  vc<vc<pii>> ad(q);
  rep(i, q) {
    int o;
    cin >> o;
    if (o == 1) {
      int v;
      cin >> v;
      --v;
      int n = g.size();
      g[v].pb(n);
      g.pb();
      qq[i].pb(n);
    } else {
      int v, x;
      cin >> v >> x;
      --v;
      ad[i].pb(v, x);
    }
  }
  
  int n = (int)g.size();

  vi dfn(n);
  vi sz(n);
  int c = 0;
  auto dfs = [&](auto &self, int u) -> void {
    // debug(u, g[u]);
    sz[u] = 1;
    dfn[u] = c++;
    for (auto v : g[u]) {
      self(self, v);
      sz[u] += sz[v];
    }
  };
  dfs(dfs, 0);

  vc<ll> t(n * 2);
  auto add = [&](int x, int v) {
    if (x == n) {
      return;
    }
    x += n;
    while (x) {
      t[x] += v;
      x >>= 1;
    }
  };
  auto query = [&](int l, int r) {
    ll res = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) {
        res += t[l++];
      }
      if (r & 1) {
        res += t[--r];
      }
    }
    return res;
  };

  vc<ll> ans(n);
  for (int i = q - 1; i >= 0; i--) {
    for (auto [v, x] : ad[i]) {
      add(dfn[v], x);
      add(dfn[v] + sz[v], -x);
    }
    for (auto v : qq[i]) {
      ans[v] = query(0, dfn[v] + 1);
    }
  }

  ans[0] = query(0, 1);
  for (int i = 0; i < n; i++) {
    cout << ans[i] << " \n"[i + 1 == n];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}