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
  int n, x, y, r;
  cin >> n >> x >> y >> r;
  vector<int> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  int s = accumulate(all(b), 0);
  vector<int> dp(s + 1, -inf);
  vector<bool> ok(101);
  ok[0] = 1;
  for (int i = 1; i <= 100; i++) {
    if (i >= x) {
      if (ok[i - x]) {
        ok[i] = 1;
      }
    }
    if (i >= y) {
      if (ok[i - y]) {
        ok[i] = 1;
      }
    }
  }
  dp[0] = 0;
  int ns = 0;
  for (int i = 0; i < n; i++) {
    ns += b[i];
    vector<int> ndp(s + 1, -inf);
    for (int j = 0; j <= b[i]; j++) {
      if (!ok[j]) {
        continue;
      }
      int c = b[i] - j;
      for (int k = 0; k + j <= ns; k++) {
        cmax(ndp[k + j], dp[k] + c * c);
      }
    }
    swap(dp, ndp);
  }
  int ans = -1;
  for (int i = r; i <= s; i++) {
    cmax(ans, dp[i]);
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
