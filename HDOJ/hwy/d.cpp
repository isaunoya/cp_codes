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

const int P = 998244353;
long long power(long long x, long long y) {
  long long res = 1;
  while (y) {
    if (y & 1) {
      res = res * x % P;
    }
    x = x * x % P;
    y /= 2;
  }
  return res;
}

long long inverse(long long x) {
  return power(x, P - 2);
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  if (k == 0 || k == n) {
    cout << n << "\n";
    return;
  }
  long long ans = n;
  ans += 1ll * m * (n - k) % P * k % P * inverse(n - k + 1) % P;
  if (ans >= P) {
    ans -= P;
  }
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
