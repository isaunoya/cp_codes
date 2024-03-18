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

struct kosaraju {
  int n, c;
  vector<vector<int>> e1, e2;
  vector<bool> vis;
  kosaraju(vector<vector<int>> &e) {
    n = (int)e.size();
    e1 = e, e2.resize(n);
    rep(u, 0, n) for (auto v : e[u]) e2[v].emplace_back(u);
    vis.resize(n);
    scc.resize(n, -1);
    rep(i, 0, n) if (!vis[i]) dfs1(i);
    c = 0;
    for (auto i : r | views::reverse)
      if (scc[i] == -1)
        dfs2(i), c++;
  }
  vector<int> r;
  void dfs1(int u) {
    vis[u] = true;
    for (auto v : e1[u])
      if (!vis[v])
        dfs1(v);
    r.emplace_back(u);
  }
  vector<int> scc;
  void dfs2(int u) {
    scc[u] = c;
    for (auto v : e2[u])
      if (scc[v] == -1)
        dfs2(v);
  }
  const int &operator[](const int &x) { return scc[x]; }
};
void solve() {
  int n, m;
  cin >> n >> m;
  vi a(n);
  rep(i, n) cin >> a[i];
  // vi f(n * 2);
  // iota(all(f), 0);
  // auto find = [&](int x) {
  //   while (x != f[x]) {
  //     x = f[x] = f[f[x]];
  //   }
  //   return x;
  // };
  // vc<ll> cnt(n * 2);
  // vc<ll> s(n * 2);
  // rep(i, n) cnt[i] = 1, s[i] = a[i];
  vc<pii> e(m);
  vc<vi> g(n);
  rep(i, m) {
    int x, y;
    cin >> x >> y;
    --x;
    --y;
    e[i] = pii(x, y);
    g[x].pb(y);
  }
  kosaraju k(g);
  int cc = k.c;
  // debug(cc);
  vi c(cc);
  vc<ll> sum(cc);
  rep(i, n) {
    int bl = k[i];
    c[bl] += 1;
    sum[bl] += a[i];
  }
  vc<vi> ng(cc);
  vi deg(cc);
  for (auto [xx, yy] : e) {
    int blx = k[xx];
    int bly = k[yy];
    if (blx != bly) {
      ng[blx].pb(bly);
      deg[bly] += 1;
    }
  }
  vc<pair<ll, ll>> p(cc);
  queue<int> q;
  rep(i, cc) {
    // debug(i, c[i], sum[i]);
    if (deg[i] == 0) {
      q.emplace(i);
      p[i] = {c[i], -sum[i]};
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : ng[u]) {
      cmax(p[v], make_pair(p[u].first + c[v], p[u].second - sum[v]));
      // debug(p[v], p[u]);
      if (--deg[v] == 0) {
        q.emplace(v);
      }
    }
  }
  auto pair = *max_element(all(p));
  cout << pair.first << " " << -pair.second << "\n";
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