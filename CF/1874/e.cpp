#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep1(a) for (int i = 0; i < a; i++)
#define rep2(i, a) for (int i = 0; i < a; i++)
#define rep3(i, a, b) for (int i = a; i < b; i++)
#define rep4(i, a, b, c) for (int i = a; i < b; i += c)
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)

#define pb emplace_back
using namespace std;
template <typename T, typename T2> void cmin(T &x, const T2 &y) {
  x = x < y ? x : y;
}
template <typename T, typename T2> void cmax(T &x, const T2 &y) {
  x = x > y ? x : y;
}
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
template <class T> using vc = vector<T>;
template <class T> using pq = priority_queue<T>;
template <class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
mt19937 rng(time(NULL));
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define fi first
#define se second

const int P = 1e9 + 7;
ll power(ll x, ll y) {
  ll res = 1;
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
  int n, k;
  cin >> n >> k;
  int m = n * (n + 1) / 2 + 1;
  vector<ll> op(m + 1);
  vector<ll> fac(m + 1), ifac(m + 1);
  fac[0] = 1;
  for (int i = 1; i <= m; i++) {
    fac[i] = fac[i - 1] * i % P;
  }
  ifac[m] = power(fac[m], P - 2);
  for (int i = m - 1; i >= 0; i--) {
    ifac[i] = ifac[i + 1] * (i + 1) % P;
  }

  auto binom = [&](int x, int y) {
    return fac[x] * ifac[x - y] % P * ifac[y] % P;
  };

  for (int x = 1; x <= m; x++) {
    vector<ll> pw(n + 1);
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
      pw[i] = pw[i - 1] * x % P;
    }
    vector<ll> dp(n + 1);
    dp[0] = 1, dp[1] = x;
    for (int t = 2; t <= n; t++) {
      for (int i = 0; i < t; i++) {
        int j = t - 1 - i;
        dp[t] += dp[i] * dp[j] % P * binom(i + j, i) % P * pw[t] % P;
        if (dp[t] >= P) {
          dp[t] -= P;
        }
      }
    }
    op[x] = dp[n];
  }
  for (int i = 1; i <= m; i++) {
    op[i] = op[i] * ifac[i - 1] % P * ifac[m - i] % P;
    if ((m - i) % 2 == 1) {
      op[i] = P - op[i];
    }
  }
  vector<array<ll, 2>> f(m + 2);
  f[0][0] = 1;
  for (int i = 1; i <= m; i++) {
    vector<array<ll, 2>> g(m + 2);
    for (int j = 0; j <= i; j++) {
      g[j][1] += f[j][0] * op[i] % P;
      g[j][1] += f[j][1] * (P - i) % P;
      g[j][1] %= P;
      g[j + 1][1] += f[j][1];
      if (g[j + 1][1] >= P) {
        g[j + 1][1] -= P;
      }
      g[j][0] += f[j][0] * (P - i) % P;
      if (g[j][0] >= P) {
        g[j][0] -= P;
      }
      g[j + 1][0] += f[j][0];
      if (g[j + 1][0] >= P) {
        g[j + 1][0] -= P;
      }
    }
    f.swap(g);
  }
  ll ans = 0;
  for (int i = k; i <= m; i++) {
    ans += f[i][1];
    if (ans >= P) {
      ans -= P;
    }
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}