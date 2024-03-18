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
  vi p(n, -1);
  rep(i, 1, n) { cin >> p[i], --p[i]; }
  rep(i, 1, n) g[p[i]].pb(i);
  vi s(n);
  auto dfs = [&](auto &dfs, int u) -> void {
    s[u] = 1;
    for (auto v : g[u]) {
      dfs(dfs, v);
      s[u] += s[v];
    }
  };
  dfs(dfs, 0);
  auto dfs2 = [&](auto &dfs2, int u, int lim) -> int {
    int mx = 0, mxv = -1;
    for (auto v : g[u]) if (s[v] > mx) {
      mx = s[v], mxv = v;
    }
    if (s[u] - 1 >= 2 * mx) {
      return min(lim, (s[u] - 1) / 2 * 2);
    } else {
      int nlim = mx - (s[u] - 1 - mx);
      int res = dfs2(dfs2, mxv, nlim);
      return min(lim, res + (s[u] - 1 - mx) * 2);
    }
  };
  cout << dfs2(dfs2, 0, n) / 2 << "\n";
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