#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, m, a[N][N], b[N][N];
const int M = N * N;
pair<int, int> bb[M];
int down[N][N], rig[N][N];
int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> b[i][j];
      bb[b[i][j]] = make_pair(i, j);
    }
  }
  for (int j = 1; j <= m; j++) {
    down[n][j] = 1;
  }
  for (int i = n - 1; i >= 1; i--) {
    for (int j = m; j >= 1; j--) {
      int X = a[i][j];
      auto [x, y] = bb[X];
      if (a[i + 1][j] == b[x + 1][y])
        down[i][j] = down[i + 1][j] + 1;
      else
        down[i][j] = 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    rig[i][m] = 1;
  }
  for (int j = m - 1; j >= 1; j--) {
    for (int i = 1; i <= n; i++) {
      int X = a[i][j];
      auto [x, y] = bb[X];
      if (a[i][j + 1] == b[x][y + 1])
        rig[i][j] = rig[i][j + 1] + 1;
      else
        rig[i][j] = 1;
    }
  }
  int ans = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int w = down[i][j];
      for (int len = 1; len <= rig[i][j]; len++) {
        ans = max(ans, len * w);
        w = min(w, down[i][j + len]);
      }
    }
  }
  cout << ans << "\n";
  return 0;
}