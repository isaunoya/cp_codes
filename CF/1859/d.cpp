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
  vector<array<int, 2>> v(n);
  for (int i = 0; i < n; i++) {
    int l, r, a, b;
    cin >> l >> r >> a >> b;
    v[i] = array<int, 2>{l, b};
  }
  sort(all(v));
  // debug(v);
  vector<array<int, 2>> ans;
  for (int i = 0; i < n; i++) {
    if (ans.empty()) {
      ans.emplace_back(v[i]);
    } else {
      if (ans.back()[1] >= v[i][0]) {
        cmax(ans.back()[1], v[i][1]);
      } else {
        ans.emplace_back(v[i]);
      }
    }
  }
  // debug(ans);
  int q;
  cin >> q;
  while (q--) {
    int x;
    cin >> x;
    int p = upper_bound(all(ans), array<int, 2>{x, inf}) - ans.begin();
    --p;
    // debug(x, p);
    if (p >= 0) {
      cout << max(x, ans[p][1]) << " ";
    } else {
      cout << x << " ";
    }
  }
  cout << "\n";
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