#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")

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
  int n, m;
  scanf("%d %d", &n, &m);
  vector<array<int, 7>> a(n);
  rep (i, 0, n) {
    rep (j, 0, 5) {
      double x;
      scanf("%lf", &x);
      a[i][j + 1] = x * 10;
    }
    cin >> a[i][0];
    a[i][6] = i;
  }
  sort(all(a));
  array<int, 5> b;
  while (m--) {
    rep (j, 0, 5) {
      double x;
      scanf("%lf", &x);
      b[j] = x * 10;
    }
    rep (i, 0, n) {
      bool ok = true;
      rep (j, 0, 5) if (a[i][j + 1] < b[j]) {
        ok = false;
      }
      if (ok) {
        cout << int(a[i][6]) + 1 << "\n";
        break;
      }
    }
  }
}

int main() {
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
