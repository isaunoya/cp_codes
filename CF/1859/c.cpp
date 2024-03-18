#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define eb emplace_back
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
  int n;
  cin >> n;
  long long ans = 0;
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    long long res = 0;
    iota(v.begin(), v.end(), 0);
    reverse(v.begin() + i, v.end());
    rep(j, 0, n) res += 1ll * (v[j] + 1) * (j + 1);
    long long mx = 0;
    rep(j, 0, n) cmax(mx, 1ll * (v[j] + 1) * (j + 1));
    res -= mx;
    cmax(ans, res);
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