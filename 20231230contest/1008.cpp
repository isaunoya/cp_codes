#include <bits/stdc++.h>
using namespace std;
void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  long long k;
  cin >> k;
  sort(a.begin(), a.end());
  auto check = [&](int x) { // <=x count
    long long res = 0;
    for (int i = 0; i < n; i++) {
      int l = i, r = n;
      while (r - l > 1) {
        int m = (l + r) / 2;
        if (a[i] + a[m] <= x) {
          l = m;
        } else {
          r = m;
        }
      }
      res += l - i;
    }
    //    cout << x << " " << res << "\n";
    return res >= k;
  };
  int l = -1, r = 2e9 + 1;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (check(m)) {
      r = m;
    } else {
      l = m;
    }
  }
  cout << r << "\n";
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