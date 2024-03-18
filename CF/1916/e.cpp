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

int n;
const int N = 3e5 + 5;
vi g[N];
int dfn[N], idx;
int sz[N];
void dfs(int u) {
  dfn[u] = idx++;
  sz[u] = 1;
  for (auto v : g[u]) {
    dfs(v);
    sz[u] += sz[v];
  }
}

int f[N * 4], tag[N * 4];
void up(int x) { f[x] = max(f[x * 2], f[x * 2 + 1]); }

void push(int p, int v) {
  tag[p] += v;
  f[p] += v;
}
void down(int p) {
  if (!tag[p])
    return;
  push(p * 2, tag[p]);
  push(p * 2 + 1, tag[p]);
  tag[p] = 0;
}

void build(int l, int r, int p) {
  f[p] = tag[p] = 0;
  if (l == r)
    return;
  int m = (l + r) / 2;
  build(l, m, p * 2);
  build(m + 1, r, p * 2 + 1);
}

void upd(int ql, int qr, int l, int r, int p, int v) {
  if (ql <= l && r <= qr) {
    push(p, v);
    return;
  }
  down(p);
  int m = (l + r) / 2;
  if (ql <= m) {
    upd(ql, qr, l, m, p * 2, v);
  }
  if (qr > m) {
    upd(ql, qr, m + 1, r, p * 2 + 1, v);
  }
  up(p);
}

int query(int ql, int qr, int l, int r, int p) {
  if (ql > qr)
    return 0;
  if (ql <= l && r <= qr) {
    return f[p];
  }
  down(p);
  int m = (l + r) / 2;
  int res = 0;
  if (ql <= m) {
    cmax(res, query(ql, qr, l, m, p * 2));
  }
  if (qr > m) {
    cmax(res, query(ql, qr, m + 1, r, p * 2 + 1));
  }
  return res;
}

set<pii> del[N];
int a[N];

void solve() {
  cin >> n;
  rep(i, n) dfn[i] = 0;
  idx = 0;
  for (int i = 0; i < n; i++)
    g[i].clear();
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    --p;
    g[p].pb(i);
  }
  rep(i, n) cin >> a[i], --a[i];
  dfs(0);
  build(0, n - 1, 1);
  rep(i, n) del[i].clear();
  ll ans = 0;
  auto dfs = [&](auto &dfs, int u) -> void {
    for (auto v : g[u]) {
      dfs(dfs, v);
      if (del[u].size() < del[v].size()) {
        swap(del[u], del[v]);
      }
      for (auto t : del[v]) {
        del[u].emplace(t);
      }
    }
    auto it = del[u].lower_bound(make_pair(a[u], 0));
    for (; it != del[u].end() && it->first == a[u];) {
      int t = it->second;
      upd(dfn[t], dfn[t] + sz[t] - 1, 0, n - 1, 1, -1);
      auto w = it++;
      del[u].erase(w);
    }
    // debug(u,del[u]);
    upd(dfn[u], dfn[u] + sz[u] - 1, 0, n - 1, 1, 1);
    del[u].emplace(a[u], u);
    int L = dfn[u], R = dfn[u] + sz[u] - 1;
    for (auto v : g[u]) {
      int ql = dfn[v], qr = dfn[v] + sz[v] - 1;
      ll val1 = query(ql, qr, 0, n - 1, 1);
      ll val2 = query(L, ql - 1, 0, n - 1, 1);
      ll val3 = query(qr + 1, R, 0, n - 1, 1);
      // debug(ql,qr,L,R);
      // debug(val1,val2,val3);
      cmax(ans, val1 * max(val2, val3));
    }
    cmax(ans, query(L, R, 0, n - 1, 1));
  };
  dfs(dfs, 0);

  cout << ans << "\n";
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