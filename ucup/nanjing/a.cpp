#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...)
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
using namespace std;

void solve() {
  int n, m, k;
  string s;
  cin >> n >> m >> k >> s;
  int len = s.size();
  int mnx = 0, mny = 0;
  int mxx = 0, mxy = 0;
  int x = 0, y = 0;
  for (int i = 0; i < len; i++) {
    if (s[i] == 'L')
      --y;
    if (s[i] == 'R')
      ++y;
    if (s[i] == 'U')
      --x;
    if (s[i] == 'D')
      ++x;
    mnx = min(mnx, x);
    mxx = max(mxx, x);
    mny = min(mny, y);
    mxy = max(mxy, y);
  }
  mnx = -mnx + 1, mxx = n - mxx;
  mny = -mny + 1, mxy = m - mxy;
  if (mnx <= mxx && mny <= mxy) {
    int all = (mxy - mny + 1) * (mxx - mnx + 1);
    int ans = 0;
    vector<vector<int>> a(n * 2 + 3, vector<int>(m * 2 + 3, 0));
    auto add = [&](int x0, int y0) {
      int sx = mnx - x0;
      int sy = mny - y0;
      int ex = mxx - x0;
      int ey = mxy - y0;
      sx = max(sx, 1);
      sy = max(sy, 1);
      ex = min(ex, n);
      ey = min(ey, m);
      if (sx > ex) {
        return;
      }
      if (sy > ey) {
        return;
      }
      a[sx][sy] += 1;
      a[sx][ey + 1] -= 1;
      a[ex + 1][sy] -= 1;
      a[ex + 1][ey + 1] += 1;
    };
    x = 0, y = 0;
    vector<pair<int, int>> b;
    b.emplace_back(0, 0);
    for (int i = 0; i < len; i++) {
      if (s[i] == 'L')
        --y;
      if (s[i] == 'R')
        ++y;
      if (s[i] == 'U')
        --x;
      if (s[i] == 'D')
        ++x;
      b.emplace_back(-x, -y);
    }
    sort(b.begin(), b.end());
    b.resize(unique(b.begin(), b.end()) - b.begin());
    debug(b);
    for (auto [x, y] : b) {
      add(x, y);
    }
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        a[i][j] += a[i - 1][j];
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        a[i][j] += a[i][j - 1];
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int ned = all - k;
        int now = a[i][j];
        debug(ned, now);

        if (now == ned) {
          debug(i, j);
          ans += 1;
        }
      }
    }
    cout << ans << "\n";
  } else {
    if (k == 0) {
      cout << n * m << "\n";
    } else {
      cout << 0 << "\n";
    }
  }
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