#include <bits/stdc++.h>
using namespace std;
const int P = 998244353;
void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<pair<int, int>> t(n * 2);
  for (int i = 0; i < n; i++) {
    t[i + n] = make_pair(a[i], i);
  }
  for (int i = n - 1; i >= 0; i--) {
    t[i] = min(t[i * 2], t[i * 2 + 1]);
  }

  auto query = [&](int l, int r) {
    pair<int, int> res = make_pair(1e9, -1);
    for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
      if (l & 1)
        res = min(res, t[l++]);
      if (r & 1)
        res = min(res, t[--r]);
    }
    return res;
  };
  vector<int> A(n + 2);
  A[0] = 0;
  for (int i = 1; i <= n; i++)
    A[i] = A[i - 1] ^ a[i - 1];
  vector<array<int, 32>> bit(n + 2), bit0(n + 2);
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j < 32; j++) {
      bit[i + 1][j] = bit[i][j] + (A[i] >> j & 1);
      bit0[i + 1][j] = bit0[i][j] + (~A[i] >> j & 1);
    }
  }
  long long ans = 0;
  auto solve = [&](auto &solve, int l, int r) -> void {
    if (l > r) {
      return;
    }
    //    cout<<l<<" "<<r<<"\n";
    array<long long, 32> L0, L1, R0, R1;
    int m = query(l - 1, r - 1).second + 1;
    //    for(int i=l;i<=m;i++){
    //      for(int j=m;j<=r;j++){
    ////        cout<<(A[j]^A[i-1])<<" "<<t[n+m-1].first<<"\n";
    //        ans+=1ll*(A[j]^A[i-1])*t[n+m-1].first%P;
    //      }
    //    }
    for (int i = 0; i < 32; i++) {
      L1[i] = bit[m][i] - bit[l - 1][i];
      L0[i] = bit0[m][i] - bit0[l - 1][i];

      R1[i] = bit[r + 1][i] - bit[m][i];
      R0[i] = bit0[r + 1][i] - bit0[m][i];
    }
    for (int i = 0; i < 32; i++) {
      long long cnt = 0;
      cnt += L1[i] * R0[i];
      cnt %= P;
      cnt += L0[i] * R1[i];
      cnt %= P;
      ans += cnt * (1ll << i) % P * t[n + m - 1].first % P;
      if (ans >= P) {
        ans -= P;
      }
    }
    //    cout<<" "<<l<<" "<<r<<" "<<ans<<"\n";
    solve(solve, l, m - 1);
    solve(solve, m + 1, r);
  };

  solve(solve, 1, n);
  cout << ans << "\n";
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