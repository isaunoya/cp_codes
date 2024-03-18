#include <bits/stdc++.h>

#define int long long
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
void solve() {
  int n, a, b, C;
  cin >> n >> a >> b >> C;
  vc<vi> d(n, vi(n));
  rep(i, n) rep(j, n) cin >> d[i][j];
  vc<vi> ans(n, vi(2, lnf));
  ans[0][0] = 0;
  vc<vi> vis(n, vi(2, 0));
  rep(r, n * 2) {
    int c = lnf, t = -1, v = -1;
    rep(i, n) rep(j, 2) if (ans[i][j] < c && !vis[i][j]) {
      c = ans[i][j];
      t = i;
      v = j;
    }
    if (t == -1)
      break;
    vis[t][v] = 1;
    debug(c, t, v);
    if (v == 0) {
      rep(x, n) cmin(ans[x][v], c + a * d[t][x]);
      cmin(ans[t][1], ans[t][0]);
    } else {
      rep(x, n) cmin(ans[x][v], c + b * d[t][x] + C);
    }
  }
  cout << ans[n - 1][1] << "\n";
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}