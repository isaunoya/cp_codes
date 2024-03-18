#include <algorithm>
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
struct lowest_common_ancestor {
  vector<vector<int>> g;
  vector<int> dep;
  vector<int> dfn;
  vector<int> out;
  vector<int> fa;
  vector<vector<int>> f;
  int n;
  int Index;
  int LG;
  void dfs(int u) {
    dfn[u] = Index++;
    for (auto v : g[u]) {
      if (dfn[v] == -1) {
        fa[v] = u;
        dep[v] = dep[u] + 1;
        dfs(v);
      }
    }
    out[u] = Index;
  }
  bool inside(int u, int x) { return dfn[x] <= dfn[u] && dfn[u] < out[x]; }
  int lca(int x, int y) {
    if (inside(x, y)) {
      return y;
    } else if (inside(y, x)) {
      return x;
    } else {
      for (int i = LG - 1, t; i >= 0; i--) {
        if (f[i][x] != -1 && !inside(y, t = f[i][x])) {
          x = t;
        }
      }
      return f[0][x];
    }
  }
  int distance(int x, int y) { return dep[x] + dep[y] - 2 * dep[lca(x, y)]; }
  lowest_common_ancestor(const vector<vector<int>> &graph, int root = 0)
      : g(graph) {
    n = graph.size();
    dep.resize(n, 0);
    dfn.resize(n, -1);
    out.resize(n);
    fa.resize(n, -1);
    LG = __lg(n) + 1;
    f.resize(LG);
    Index = 0;
    dfs(root);
    f[0] = fa;
    for (int j = 1; j < LG; j++) {
      for (int i = 0; i < n; i++) {
        if (f[j - 1][i] == -1) {
          f[j].emplace_back(-1);
        } else {
          f[j].emplace_back(f[j - 1][f[j - 1][i]]);
        }
      }
    }
  }
  int operator()(int x, int y) { return lca(x, y); }
};
template <int B> struct basis {
  using ll = long long;
  ll p[B];
  int id[B];
  basis() {
    memset(p, 0, sizeof p);
    memset(id, -1, sizeof id);
  }
  void insert(ll x, int ii) {
    for (int i = B - 1; i >= 0; i--) {
      if (x >> i & 1) {
        if (id[i] < ii) {
          swap(p[i], x);
          swap(id[i], ii);
        }
        x ^= p[i];
      }
    }
  }
  void insert(ll x) {
    for (int i = B - 1; i >= 0; i--) {
      if (x >> i & 1) {
        if (!p[i]) {
          p[i] = x;
        }
        x ^= p[i];
      }
    }
  }
  ll get_max(ll x = 0) {
    for (int i = B - 1; i >= 0; i--) {
      x = max(x, x ^ p[i]);
    }
    return x;
  }
  ll get_min(ll x) {
    for (int i = B - 1; i >= 0; i--) {
      x = min(x, x ^ p[i]);
    }
    return x;
  }
};

void solve() {
  int n;
  cin >> n;
  vi a(n);
  rep(i, n) cin >> a[i];
  vc<basis<20>> b(n);
  vc<vi> g(n);
  rep(i, n - 1) {
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    g[x].pb(y);
    g[y].pb(x);
  }

  vi dep(n);
  auto dfs = [&](auto &dfs, int u, int p) -> void {
    b[u].insert(a[u], dep[u]);
    for (auto v : g[u]) {
      if (v != p) {
        b[v] = b[u];
        dep[v] = dep[u] + 1;
        dfs(dfs, v, u);
      }
    }
  };
  dfs(dfs, 0, -1);
  lowest_common_ancestor lca(g);
  int q;
  cin >> q;
  while (q--) {
    int x, y, k;
    cin >> x >> y >> k;
    x--, y--;
    int l = lca(x, y);
    basis<20> t;
    rep(i, 20) {
      if (b[x].id[i] >= dep[l]) {
        t.insert(b[x].p[i]);
      }
      if (b[y].id[i] >= dep[l]) {
        t.insert(b[y].p[i]);
      }
    }
    cout << (t.get_min(k) == 0 ? "YES" : "NO") << "\n";
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