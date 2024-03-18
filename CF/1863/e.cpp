#include <algorithm>
#include <bits/stdc++.h>

#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define rp(i, n) rep(i, 0, n)
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
void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vc<ll> h(n), d(n, 0);
  rp(i, n) cin >> h[i];
  vc<vc<pair<ll, ll>>> g(n);
  vi deg(n), out(n);
  rp(i, m) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    ll cost = h[y] - h[x];
    if (cost < 0)
      cost += k;
    g[y].pb(x, cost);
    out[y]++;
    deg[x]++;
  }
  queue<int> q;
  rp(i, n) if (deg[i] == 0) q.emplace(i);
  while (sz(q)) {
    int u = q.front();
    q.pop();
    // debug(u);
    for (auto [v, w] : g[u]) {
      // debug(v,w);
      cmax(d[v], d[u] + w);
      if (--deg[v] == 0) {
        q.emplace(v);
      }
    }
  }
  // debug(d);
  vc<pair<ll, ll>> t;
  rp(i, n) if (out[i] == 0) t.pb(h[i], h[i] + d[i]);
  // debug(t);
  sort(all(t));
  ll R = 0;
  for (auto [x, y] : t)
    cmax(R, y);
  ll ans = lnf;
  for (auto [x, y] : t) {
    cmin(ans, R - x);
    cmax(R, y + k);
  }
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