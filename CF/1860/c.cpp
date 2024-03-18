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
  cin >> n;
  vector<int> p(n);
  rep(i, 0, n) {
    cin >> p[i];
    --p[i];
  }
  vector<int> stk(n + 1), f(n, -1);
  int top = 0;
  for (int i = 0; i < n; i++) {
    while (top && p[stk[top]] > p[i]) {
      top -= 1;
    }
    if (top)
      f[i] = stk[top];
    stk[++top] = i;
  }
  vector<int> t(n * 2, -inf);
  auto upd = [&](int x, int v) {
    x += n;
    t[x] = v;
    while (x >>= 1) {
      t[x] = max(t[x * 2], t[x * 2 + 1]);
    }
  };

  auto query = [&](int l, int r) {
    int ans = -inf;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) {
        cmax(ans, t[l++]);
      }
      if (r & 1) {
        cmax(ans, t[--r]);
      }
    }
    return ans;
  };

  int res = 0;
  for (int i = 0; i < n; i++) {
    if (query(0, p[i]) == -1) {
      res += 1;
    }
    upd(p[i], f[i]);
  }
  cout << res << "\n";
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
