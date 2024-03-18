#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
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
  string x, y;
  cin >> n >> x >> y;
  int c = 0;
  rep (i, 0, n) if (x[i] == '1') ++c;
  rep (i, 0, n) if (y[i] == '1') ++c;
  if (c <= n) {
    rep (i, 0, c) cout << 1;
    rep (i, 0, n - c) cout << 0;
  } else {
    c = 2 * n - c;
    rep (i, 0, c) cout << 1;
    rep (i, 0, n - c) cout << 0;
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
