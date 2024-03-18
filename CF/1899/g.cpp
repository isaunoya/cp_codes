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
  int n, q;
  cin >> n >> q;

  vc<vi> g(n);
  rep(i, n - 1) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    g[u].pb(v);
    g[v].pb(u);
  }

  vi dfn(n);
  int c = 0;
  vi s(n);
  auto dfs = [&](auto &self, int u, int p) -> void {
    dfn[u] = c++;
    s[u] = 1;
    for (auto v : g[u]) {
      if (v == p)
        continue;
      self(self, v, u);
      s[u] += s[v];
    }
  };

  dfs(dfs, 0, -1);
  // debug(dfn,s);
  vi p(n);
  rep(i, n) {
    cin >> p[i];
    --p[i];
  }
  vc<vc<array<int, 2>>> querys(n);
  rep(i, q) {
    int l, r, x;
    cin >> l >> r >> x;
    --l;
    --r;
    --x;
    if (l > 0)
      querys[l - 1].pb(array<int, 2>{x, ~i});
    querys[r].pb(array<int, 2>{x, i});
  }

  vi t(n * 2);

  auto upd = [&](int x, int v) {
    x += n;
    while (x) {
      t[x] += v;
      x >>= 1;
    }
  };

  auto query = [&](int l, int r) {
    int res = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1)
        res += t[l++];
      if (r & 1)
        res += t[--r];
    }
    return res;
  };

  vi ans(q);
  rep(i, n) {
    upd(dfn[p[i]], 1);
    for (auto [x, j] : querys[i]) {
      if (j < 0)
        ans[~j] -= query(dfn[x], dfn[x] + s[x]);
      else
        ans[j] += query(dfn[x], dfn[x] + s[x]);
    }
  }

  rep(i, q) {
    if (ans[i]) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
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