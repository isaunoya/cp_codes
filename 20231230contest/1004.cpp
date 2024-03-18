#include <bits/stdc++.h>
using namespace std;
bitset<505> f;
int cnt[505];
void solve() {
  int n, C;
  cin >> n >> C;
  memset(cnt, 0, sizeof cnt);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    cnt[x] += 1;
  }
  int ans = 1e9;
  for (int l = 1; l <= C; l++) {
    f.reset();
    f[0] = 1;
    for (int r = l; r <= C; r++) {
      int t = cnt[r];
      for (int i = 0; i < 17; i++) {
        if (t >= (1 << i)) {
          int val = r * (1 << i);
          //          cout<<l<<" "<<r<<" "<<val<<"\n";
          if (val <= C)
            f |= f << val;
          t -= (1 << i);
        }
      }
      if (t) {
        int val = r * t;
        if (val <= C)
          f |= f << val;
      }
      if (f[C]) {
        ans = min(ans, r - l);
      }
    }
  }
  if (ans > C) {
    cout << -1 << "\n";
  } else {
    cout << ans << "\n";
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