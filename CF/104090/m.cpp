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

int n, k;
void solve() {
  cin >> n >> k;
  vi c(k);
  rep(i, k) cin >> c[i], --c[i];
  vc<vc<pii>> e(n);
  rep(i, n - 1) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    int w;
    cin >> w;
    e[u].pb(v, w);
    e[v].pb(u, w);
  }
  vi d(n);
  auto dfs = [&](auto &dfs, int u, int p) -> void {
    for (auto [v, w] : e[u]) {
      if (v == p)
        continue;
      d[v] = d[u] + w;
      dfs(dfs, v, u);
    }
  };
  dfs(dfs, 0, -1);
  // int s=0,g=0;
  // rep(i,k)s+=d[c[i]],g=gcd(g,d[c[i]]);
  // debug(s/g*2);
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