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
  vector<vector<int>> v(n);
  long long ans = 0;
  long long mn0 = 1e9;
  long long mn1 = 1e9;
  rep(i, 0, n) {
    int c;
    cin >> c;
    v[i].resize(c);
    for (auto &x : v[i]) {
      cin >> x;
    }
    sort(all(v[i]));
    ans += v[i][1];
    cmin(mn0, v[i][0]);
    cmin(mn1, v[i][1]);
  }
  cout << ans - mn1 + mn0 << "\n";
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