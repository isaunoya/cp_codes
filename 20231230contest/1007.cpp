#include <bits/stdc++.h>

using namespace std;

// dp[H][X][Y]

const int inf = 1e9;
char a[1005][1005][5];
int ans[1005][1005][5];

void solve() {
  int n, m, K;
  cin >> n >> m >> K;
  for (int k = 0; k < K; k++) {
    int w = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> a[i][j][k];
      }
    }
  }
  int H, x, y;
  cin >> H >> x >> y;
  --x;
  --y;
  if (x + 1 == n && y + 1 == m) {
    cout << 1 << "\n";
    return;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < K; k++) {
        ans[i][j][k] = inf;
      }
    }
  }
  queue<tuple<int, int, int>> q;
  ans[n - 1][m - 1][0] = 0;
  q.emplace(n - 1, m - 1, 0);
  while (!q.empty()) {
    auto [x, y, k] = q.front();
    q.pop();
    int nk = (k + 1) % K;
    int can_jump = 0;
    if (x + 1 == n)
      can_jump = 1;
    if (x + 1 < n && a[x + 1][y][k] == '*') {
      can_jump = 1;
    }
    if (can_jump) {
      for (int h = 0; h <= H; h++) {
        if (x - h < 0)
          continue;
        if (a[x - h][y][k] != '*')
          for (int d = -1; d <= 1; d++) {
            if (a[x - h][y + d][k] != '*' && a[x - h][y + d][nk] != '*' &&
                ans[x - h][y + d][nk] == inf) {
              ans[x - h][y + d][nk] = ans[x][y][k] + 1;
              q.emplace(x - h, y + d, nk);
            }
          }
        else
          break;
      }
    } else {
      for (int d = -1; d <= 1; d++) {
        if (a[x + 1][y + d][k] != '*' && a[x + 1][y + d][nk] != '*' &&
            ans[x + 1][y + d][nk] == inf) {
          ans[x + 1][y + d][nk] = ans[x][y][k] + 1;
          q.emplace(x + 1, y + d, nk);
        }
      }
    }
  }
  int res = inf;
  for (int k = 0; k < K; k++) {
    res = min(res, ans[x][y][k]);
  }
  if (res > n * m * K)
    cout << -1 << "\n";
  else
    cout << res << "\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}