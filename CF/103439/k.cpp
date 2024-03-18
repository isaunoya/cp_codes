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

void solve() {
  int n;
  cin >> n;
  vc<vi> g(n);
  rep(i, n - 1) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    g[u].pb(v);
    g[v].pb(u);
  }

  int rt = -1;
  rep(i, n) if (sz(g[i]) == 1) {
    rt = i;
    break;
  }

  vi mn(n, inf);
  auto dfs = [&](auto &dfs, int u, int p) -> void {
    int cnt = 0;
    for (auto v : g[u])
      if (v != p) {
        cnt += 1;
        dfs(dfs, v, u);
        cmin(mn[u], mn[v]);
      }
    if (!cnt)
      mn[u] = u;
  };

  dfs(dfs, rt, -1);
  int u = rt, lst = -1;
  while (true) {
    vc<pii> tmp;
    for (auto v : g[u])
      if (v != lst) {
        tmp.pb(mn[v], v);
      }
    if (tmp.empty())
      break;
    sort(all(tmp), greater());
    if (u < tmp[0].fi) {
      lst = u;
      u = tmp[0].se;
    } else {
      break;
    }
  }

  rep(i, n) mn[i] = inf;
  dfs(dfs, u, -1);
  vi ans;
  auto dfs2 = [&](auto &dfs2, int u, int p) -> void {
    sort(all(g[u]), [&](int x, int y) { return mn[x] < mn[y]; });
    for (auto v : g[u])
      if (v != p)
        dfs2(dfs2, v, u);
    ans.pb(u);
  };
  dfs2(dfs2, u, -1);
  for (int x : ans)
    cout << x + 1 << " ";
  cout << "\n";
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