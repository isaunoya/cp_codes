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
#define all(x) begin(x), end(x)

const int P = 998244353;
long long power(long long x, long long y) {
  long long res = 1;
  while (y) {
    if (y % 2 == 1) {
      res = res * x % P;
    }
    x = x * x % P;
    y /= 2;
  }
  return res;
}

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  rep(i, 0, n) cin >> a[i];
  long long coef = power(1ll * n * n % P, P - 2);
  vector<array<int, 2>> ch(2);
  vector<ll> sz(2);
  ch[1][0] = ch[1][1] = sz[0] = sz[1] = 0;
  auto newnode = [&]() {
    int id = ch.size();
    ch.emplace_back();
    sz.emplace_back();
    return id;
  };
  auto upd = [&](int v) {
    int p = 1;
    for (int i = 29; i >= 0; i--) {
      int c = (v >> i & 1);
      if (!ch[p][c]) {
        ch[p][c] = newnode();
      }
      p = ch[p][c];
      sz[p]++;
    }
  };

  for (int i = 0; i < n; i++) {
    upd(a[i]);
  }
  long long ans = 0;
  auto dfs = [&](auto &dfs, int p) {
    if (p == 0) {
      return;
    }
    int lc = ch[p][0];
    int rc = ch[p][1];
    ans += sz[lc] * sz[rc] % P;
    if (ans >= P) {
      ans -= P;
    }
    dfs(dfs, lc);
    ans += sz[rc] * sz[rc] % P;
    if (ans >= P) {
      ans -= P;
    }
    dfs(dfs, rc);
  };

  dfs(dfs, 1);

  ans += 1ll * n * n % P;
  if (ans >= P) {
    ans -= P;
  }
  ans = ans * coef % P;
  cout << ans << "\n";
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