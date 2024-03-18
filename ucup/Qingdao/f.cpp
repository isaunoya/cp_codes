#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
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
  int n, m;
  cin >> n >> m;
  vc<vi> adj(n);
  rp(i, m) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    adj[x].pb(y);
    adj[y].pb(x);
  }
  vi p(n);
  iota(all(p), 0);
  sort(all(p), [&](auto x, auto y) { return sz(adj[x]) > sz(adj[y]); });
  vi vis(n);
  int cnt = 0;
  for (auto x : p) {
    int res = 0;
    for (auto y : adj[x]) {
      if (vis[y]) {
        res += 1;
      }
    }
    if (res == cnt) {
      cnt += 1;
      vis[x] = 1;
    }
  }
  int ans1 = 1;
  int ans2 = 1;
  rp(i, n) {
    if (!vis[i] && sz(adj[i]) == cnt - 1) {
      ans1 += 1;
    }
  }
  rp(i, n) {
    if (vis[i] && sz(adj[i]) == cnt - 1) {
      cnt--;
      vis[i] = 0;
    }
  }
  rp(i, n) {
    if (vis[i] && sz(adj[i]) == cnt) {
      ans2 += 1;
    }
  }
  cout << ans1 << " " << ans2 << "\n";
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