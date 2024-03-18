#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
using namespace std;
template <typename T, typename T2> void cmin(T &x, const T2 &y) {
  if (x > y)
    x = y;
}
template <typename T, typename T2> void cmax(T &x, const T2 &y) {
  if (x < y)
    x = y;
}
using ll = long long;
mt19937 rng(time(NULL));
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)

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
  vector<int> a(n);
  rep(i, 0, n) cin >> a[i];
  vector<vector<int>> e(n);
  rep(i, 0, m) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    e[x].emplace_back(y);
  }
  kosaraju scc(e);
  int c = scc.c;
  vector<int> sum(c), deg(c);
  for (int i = 0; i < n; i++) {
    sum[scc[i]] += a[i];
  }
  vector<vector<int>> ne(c);
  rep(u, 0, n) {
    for (auto v : e[u]) {
      if (scc[u] != scc[v]) {
        ne[scc[u]].emplace_back(scc[v]);
        deg[scc[v]] += 1;
      }
    }
  }
  vector<int> dp(c);
  queue<int> q;
  rep(i, 0, c) {
    if (deg[i] == 0) {
      dp[i] = sum[i];
      q.emplace(i);
    }
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : ne[u]) {
      cmax(dp[v], dp[u] + sum[v]);
      if (--deg[v] == 0) {
        q.emplace(v);
      }
    }
  }
  cout << *max_element(all(dp));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  while (t--) {
    solve();
  }
  return 0;
}
