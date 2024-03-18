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
const int P = 998244353;
void md(ll &x) {
  if (x >= P)
    x -= P;
}
void solve() {
  int N, K;
  cin >> N >> K;
  int M = N / K;
  ll f[K + 2][M + 1];
  ll g[K + 2][M + 2];
  ll s[K + 2][M + 2];
  memset(f, 0, sizeof f);
  memset(g, 0, sizeof g);
  memset(s, 0, sizeof s);
  f[1][0] = K;
  rep(i, 1, N) {
    rp(j, K + 1) rp(k, M + 1) g[j][k] = s[j][k] = 0;
    rep(j, 1, K + 1) rep(k, 0, M + 1) if (f[j][k]) {
      if (j == K)
        md(g[1][k + 1] += f[j][k] * K % P);
      if (j < K)
        md(g[j + 1][k] += f[j][k] * (K - j) % P);
      if (j != K)
        md(s[1][k] += f[j][k]), md(s[j + 1][k] += P - f[j][k]);
    }
    rp(k, M + 1) rep(j, 1, K + 1) md(s[j][k] += s[j - 1][k]);
    rp(j, K + 1) rp(k, M + 1) md(f[j][k] = g[j][k] + s[j][k]);
  }
  ll ans = 0;
  rep(j, 1, K + 1) rep(k, 0, M + 1) {
    int w = k;
    if (j == K)
      w++;
    md(ans += f[j][k] * w % P);
  }
  cout << ans << "\n";
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