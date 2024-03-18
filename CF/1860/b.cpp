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

void solve() {
  int m, k, a1, ak;
  cin >> m >> k >> a1 >> ak;

  int ned = m / k;
  cmin(ned, ak);
  m -= ned * k;

  if (a1 >= m) {
    cout << 0 << "\n";
    return;
  }
  int ans = inf;
  cmin(ans, m - a1);
  int l = m - a1, r = m;
  int b = l / k;
  cmin(ans, l - b * k + b);
  b += 1;
  if (l <= b * k && b * k <= r) {
    cmin(ans, b);
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
