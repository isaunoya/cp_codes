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
  int n;
  cin >> n;
  vi a(n), deg(n), vis(n), ban(n), ok(n);
  rep(i, n) cin >> a[i], --a[i];
  queue<int> q;
  vc<vi> g(n);
  rep(i, n) g[i].pb(a[i]), deg[a[i]] += 1;
  rep(i, n) if (deg[i] == 0) { q.emplace(i); }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (vis[u]) {
      continue;
    }
    vis[u] = 1;
    int v = a[u];
    {
      debug(u, v);
      if (!ban[u]) {
        ok[u] = ban[v] = 1;
        q.emplace(v);
      }
      if (--deg[v] == 0) {
        q.emplace(v);
      }
    }
  }
  bool ok2 = true;
  rep(i, n) {
    if (!vis[i]) {
      int cnt = 1;
      for (int j = a[i]; j != i; j = a[j]) {
        cnt += 1;
      }
      if (cnt % 2 == 0) {
        int c = 1;
        vis[i] = 0;
        for (int j = a[i]; j != i; j = a[j]) {
          if (c) {
            ok[j] = 1;
          }
          vis[j] = 1;
          c ^= 1;
        }
      } else {
        ok2 = false;
        break;
      }
    }
  }
  if (!ok2) {
    cout << -1 << "\n";
    return;
  }
  int cnt = 0;
  rep(i, n) if (ok[i]) cnt += 1;
  cout << cnt << "\n";
  rep(i, n) if (ok[i]) { cout << a[i] + 1 << " \n"[i + 1 == n]; }
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