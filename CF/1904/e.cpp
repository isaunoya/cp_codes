#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
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

struct HLD {
  HLD() {}
  vector<vector<int>> G;
  int n;
  vector<int> dfn, sz, son, top, d, fa;
  int idx;
  void dfs(int u, int p) {
    sz[u] = 1;
    for (auto v : G[u])
      if (v != p) {
        fa[v] = u;
        d[v] = d[u] + 1;
        dfs(v, u), sz[u] += sz[v];
        if (son[u] == -1 || sz[v] > sz[son[u]])
          son[u] = v;
      }
  }
  void dfs2(int u, int t) {
    top[u] = t, dfn[u] = idx++;
    if (son[u] != -1)
      dfs2(son[u], t);
    for (auto v : G[u])
      if (top[v] == -1)
        dfs2(v, v);
  }
  HLD(const vector<vector<int>> &g, const int &root = 0) {
    n = g.size();
    G = g;
    sz.resize(n);
    dfn.resize(n);
    son.resize(n, -1);
    top.resize(n, -1);
    d.resize(n);
    fa.resize(n);
    dfs(root, -1), idx = 0, dfs2(root, root);
  }
  int lca(int x, int y) {
    while (top[x] != top[y]) {
      if (d[top[x]] < d[top[y]])
        swap(x, y);
      x = fa[top[x]];
    }
    return d[x] < d[y] ? x : y;
  }
  vector<pair<int, int>> chain(int x, int y) {
    assert(0 <= x && x < n);
    assert(0 <= y && y < n);
    vector<pair<int, int>> L, R;
    while (top[x] != top[y]) {
      assert(0 <= x && x < n);
      assert(0 <= y && y < n);
      if (d[top[x]] > d[top[y]]) {
        L.emplace_back(dfn[x], dfn[top[x]]);
        x = fa[top[x]];
      } else {
        R.emplace_back(dfn[top[y]], dfn[y]);
        y = fa[top[y]];
      }
    }
    L.emplace_back(dfn[x], dfn[y]);
    reverse(R.begin(), R.end());
    L.insert(L.end(), R.begin(), R.end());
    return L;
  }

  int distance(int x, int y) {
    return d[x] + d[y] - 2 * d[lca(x, y)];
  }
};

void solve() {
  int n, q;
  cin >> n >> q;
  vc<vi> g(n);
  rep(i, n - 1) {
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    g[x].pb(y);
    g[y].pb(x);
  }
  HLD f(g);
  using diam = array<int, 3>;

  auto merge = [&](diam a, diam b) {
    auto c = max(a, b);
    rep(i, 1, 3) rep(j, 1, 3) {
      cmax(c, diam{f.distance(a[i], b[j]), a[i], b[j]});
    }
    return c;
  };

  vi dfn(n), rev(n);
  vc<vi> pt(n), son(n);
  vi s(n);
  int idx = 0;
  auto dfs = [&](auto &dfs, int u, int p) -> void {
    dfn[u] = idx++;
    rev[dfn[u]] = u;
    s[u] = 1;
    for (auto v : g[u])
      if (v != p) {
        dfs(dfs, v, u), s[u] += s[v];
        son[u].pb(v);
        pt[u].pb(dfn[v]);
      }
  };
  dfs(dfs, 0, -1);

  vc<diam> t(n * 2);
  rep(i, n) t[i + n] = diam{0, rev[i], rev[i]};
  for (int i = n - 1; i >= 0; i--)
    t[i] = merge(t[i * 2], t[i * 2 + 1]);

  auto query = [&](int l, int r, int x) {
    diam res = diam{0, x, x};
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1)
        res = merge(res, t[l++]);
      if (r & 1)
        res = merge(res, t[--r]);
    }
    return res;
  };

  while (q--) {
    int x, k;
    cin >> x >> k;
    --x;

    vc<pii> avail;
    if (k == 0)
      avail.pb(0, n);
    else {
      vi a(k);
      rep(i, k) cin >> a[i], --a[i];
      vc<pii> ban;
      for (int i : a) {
        if (lca.inside(x, i)) { // x in i
          int p = --upper_bound(all(pt[i]), dfn[x]) - pt[i].begin();
          int y = son[i][p];
          ban.pb(0, dfn[y]), ban.pb(dfn[y] + s[y], n);
        } else {
          ban.pb(dfn[i], dfn[i] + s[i]);
        }
      }
      sort(all(ban), [&](auto x, auto y) {
        if (x.fi == y.fi) {
          return x.se > y.se;
        }
        return x.fi < y.fi;
      });
      vc<pii> ban2;
      int mx = 0;
      rep(i, sz(ban)) {
        if (ban[i].fi >= mx)
          ban2.pb(ban[i]);
        cmax(mx, ban[i].se);
      }
      ban.swap(ban2);

      avail.pb(0, ban[0].fi);
      rep(i, sz(ban) - 1) avail.pb(ban[i].se, ban[i + 1].fi);
      avail.pb(ban.back().se, n);
    }

    diam res = {0, x, x};
    for (auto [l, r] : avail) {
      res = merge(res, query(l, r, x));
    }
    cout << max(lca.distance(x, res[1]), lca.distance(x, res[2])) << "\n";
  }
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