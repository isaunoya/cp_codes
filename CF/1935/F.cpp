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

struct bound {
  int l, r;
  bound() { l = INF, r = 0; }
  bound(int x) { l = r = x; }
  bound(int L, int R) { l = L, r = R; }
  bound operator+(const bound &z) { return bound(min(l, z.l), max(r, z.r)); }
};

template <class Info> struct rolling_dsu {
  vi p, sz, st;
  vc<Info> info, info_st;

  rolling_dsu(int n) {
    p.resize(n);
    iota(all(p), 0);
    sz.resize(n, 1);
    info.resize(n);
  }

  int root(int x) {
    if (x == p[x]) {
      return x;
    } else {
      return root(p[x]);
    }
  }

  void unite(int x, int y) {
    x = root(x);
    y = root(y);
    if (x == y) {
      return;
    }
    if (sz[x] < sz[y]) {
      swap(x, y);
    }
    p[y] = x;
    sz[x] += sz[y];
    st.pb(y);
    info_st.pb(info[x]);
    info[x] = info[x] + info[y];
  }

  int size() { return st.size(); }

  void roll_back(int last_size) {
    while ((int)st.size() != last_size) {
      int y = st.back();
      int x = p[y];
      Info z = info_st.back();
      sz[x] -= sz[y];
      p[y] = y;
      info[x] = z;
      st.pop_back();
      info_st.pop_back();
    }
  }

  Info &get(int x) { return info[root(x)]; }
};

void solve() {
  int n;
  cin >> n;
  vc<vi> g(n);
  rep(i, n - 1) {
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    g[x].pb(y);
    g[y].pb(x);
  }

  auto dsu = rolling_dsu<bound>(n);
  rep(i, n) { dsu.get(i) = bound(i, i); }
  // rep(i, n) {
  //   debug(dsu.get(i).l, dsu.get(i).r);
  // }
  vi vis(n);
  auto dfs = [&](auto &dfs, int l, int r) -> void {
    if (r - l == 1) {
      // debug(dsu.sz[dsu.root(0)], n);
      int lst = dsu.size();
      vc<pii> op;
      int u = l;
      for (auto v : g[u]) {
        int fv = dsu.root(v);
        auto cur = dsu.get(fv);
        int L = cur.l;
        int R = cur.r;
        // debug(L, R);
        if (L - 1 >= 0 && L - 1 != u && dsu.root(L) != dsu.root(L - 1)) {
          op.pb(L - 1, L);
          dsu.unite(L - 1, L);
        }
        if (R + 1 < n && R + 1 != u && dsu.root(R) != dsu.root(R + 1)) {
          op.pb(R, R + 1);
          dsu.unite(R, R + 1);
        }
      }
      if (0 < l && l + 1 < n) {
        int x = dsu.root(l - 1);
        int y = dsu.root(l + 1);
        if (x != y) {
          op.pb(l - 1, l + 1);
          dsu.unite(l - 1, l + 1);
        }
      }
      int ans = 0;
      for (auto [x, y] : op) {
        ans += y - x;
      }
      // debug(dsu.sz[dsu.root(0)], n);
      cout << ans << " " << (int)op.size() << "\n";
      for (auto [x, y] : op) {
        cout << x + 1 << " " << y + 1 << "\n";
      }
      cout << "\n";
      dsu.roll_back(lst);
    } else {
      int m = (l + r) / 2;
      int lst = dsu.size();
      rep(u, m, r) {
        vis[u] = 1;
        for (auto v : g[u]) {
          if (vis[v])
            dsu.unite(u, v);
        }
      }
      dfs(dfs, l, m);
      rep(u, m, r) { vis[u] = 0; }
      dsu.roll_back(lst);
      rep(u, l, m) {
        vis[u] = 1;
        for (auto v : g[u]) {
          if (vis[v])
            dsu.unite(u, v);
        }
      }
      dfs(dfs, m, r);
      rep(u, l, m) { vis[u] = 0; }
      dsu.roll_back(lst);
    }
  };

  dfs(dfs, 0, n);
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