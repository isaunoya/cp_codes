#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;
using vl = vector<long long>;
using ll = long long;
void solve() {
  int n, m;
  cin >> n >> m;
  vi a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  vi t(n);
  for (int i = 0; i < m; i++) {
    int r, w;
    cin >> r >> w;
    --r;
    t[r] += w;
  }
  vl T(n + 1);
  for (int i = n - 1; i >= 0; i--) {
    T[i] = T[i + 1] + t[i];
  }

  vl ans(n, 1e18);
  for (int i = 0; i < n; i++) {
    vi b(a.begin() + i + 1, a.end());
    sort(b.begin(), b.end());
    ll res = a[i] - T[i];
    ans[0] = min(ans[0], res);
    for (int j = 1; i + j < n; j++) {
      res += b[j - 1];
      ans[j] = min(ans[j], res);
    }
  }
  for (int i = 0; i < n; i++) {
    cout << ans[i] << " \n"[i + 1 == n];
  }
}
int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}