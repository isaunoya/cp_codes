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
  int n, k;
  cin >> n >> k;
  vector<long long> a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }

  vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, -lnf));
  dp[0][0] = 0;

  // auto get = [&](int l, int r) { return abs(a[l] - b[r]) + abs(a[r] - b[l]);
  // }; for (int i = 0; i < n; i++) {
  //   for (int j = 0; j <= k; j++) {
  //     cmax(dp[i + 1][j], dp[i][j]);
  //   }
  //   for (int j = 0; j <= k; j++) {
  //     for (int r = i; r < n && j + r - i + 1 <= k; r++) {
  //       int len = r - i + 1;
  //       cmax(dp[r + 1][j + len], dp[i][j] + get(i, r));
  //     }
  //   }
  // }
  // cout << dp[n][k] << "\n";

  vector<array<long long, 4>> F(n + 1);
  for (int i = 0; i <= n; i++)
    F[i][0] = F[i][1] = F[i][2] = F[i][3] = -lnf;
  for (int i = 0; i < n; i++) {
    dp[i + 1] = dp[i];
    for (int j = 0; j <= k && j <= i; j++) {
      for (int l = 0; l < 4; l++) {
        int r = 0;
        if (l & 1) {
          r += a[i];
        } else {
          r -= a[i];
        }
        if (l & 2) {
          r += b[i];
        } else {
          r -= b[i];
        }
        cmax(F[i - j][l], dp[i][j] + r);
      }
    }
    for (int j = 0; j <= k && j <= i + 1; j++) {
      for (int l = 0; l < 4; l++) {
        int r = 0;
        if (l & 1) {
          r += b[i];
        } else {
          r -= b[i];
        }
        if (l & 2) {
          r += a[i];
        } else {
          r -= a[i];
        }
        cmax(dp[i + 1][j], F[i + 1 - j][l] - r);
      }
    }
  }
  cout << dp[n][k] << "\n";
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