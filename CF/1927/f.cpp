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
    // debug(u);
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
    // LG = __lg(n) + 1;
    LG = 20;
    f.resize(LG);
    Index = 0;
    rep(i, n) if (dfn[i] == -1) dfs(i);
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

int mn[200005][21];

void solve() {
  int n, m;
  cin >> n >> m;
  // debug(n,m);
  vc<vi> g(n);
  vc<vc<pii>> e(n);

  unionfind f(n);
  vc<tuple<int, int, int>> edge;
  rep(i, m) {
    int x, y, z;
    cin >> x >> y >> z;
    --x;
    --y;
    if (!f.same(x, y)) {
      f.unite(x, y);
      // debug(x,y);
      e[x].pb(y, z);
      e[y].pb(x, z);
      g[x].pb(y);
      g[y].pb(x);
    } else {
      edge.pb(x, y, z);
    }
  }

  // debug(edge);
  rep(i, n) rep(j, 20) mn[i][j] = inf;
  vi vis(n);
  auto dfs = [&](auto &dfs, int u, int p) -> void {
    // debug(u, p);
    vis[u] = 1;
    for (auto [v, w] : e[u])
      if (v != p) {
        mn[v][0] = w;
        dfs(dfs, v, u);
      }
  };
  rep(i, n) if (!vis[i]) dfs(dfs, i, -1);
  lowest_common_ancestor lca(g);
  rep(j, 1, 20) {
    // debug(j);
    rep(i, n) {
      // debug(i);
      if (lca.f[j - 1][i] != -1) {
        cmin(mn[i][j], mn[i][j - 1]);
        cmin(mn[i][j], mn[lca.f[j - 1][i]][j - 1]);
      }
    }
  }

  // debug("ok");
  tuple<int, int, int> res = {inf, inf, inf};
  for (auto [x, y, z] : edge) {
    // debug(x,y,z);
    int t = lca(x, y);
    int d1 = lca.dep[x] - lca.dep[t];
    int d2 = lca.dep[y] - lca.dep[t];
    // debug(d1,d2);
    int X = x, Y = y, Z = z;
    for (int k = 19; k >= 0; k--) {
      if (d1 >> k & 1) {
        // debug(x);
        cmin(Z, mn[x][k]);
        x = lca.f[k][x];
      }
    }
    for (int k = 19; k >= 0; k--) {
      if (d2 >> k & 1) {
        cmin(Z, mn[y][k]);
        y = lca.f[k][y];
      }
    }
    cmin(res, make_tuple(Z, X, Y));
  }

  // debug(res);
  int ans = get<0>(res);
  int x = get<1>(res), y = get<2>(res);
  int L = lca(get<1>(res), get<2>(res));
  // debug(x,y,L);
  // rep(i, n) {
  //   debug(i, lca.f[0][i]);
  // }
  vi t;
  while (x != L) {
    t.pb(x);
    // debug(x);
    x = lca.fa[x];
  }
  t.pb(L);
  reverse(all(t));
  while (y != L) {
    t.pb(y);
    y = lca.fa[y];
  }
  cout << ans << " " << sz(t) << "\n";
  for (int i : t) {
    cout << i + 1 << " ";
  }
  cout << "\n";
}

/*
1
6 6
1 2 10
2 3 8
3 1 5
4 5 100
5 6 40
6 4 3
*/

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