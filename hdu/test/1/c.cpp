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

const int P = 998244353;
int power(int x, int y) {
  int r = 1;
  while (y) {
    if (y % 2 == 1) {
      r = 1ll * r * x % P;
    }
    x = 1ll * x * x % P;
    y /= 2;
  }
  return r;
}

int inv(const int &x) { return power(x, P - 2); }

void md(int &x) {
  if (x >= P) {
    x -= P;
  }
}

using ull = unsigned long long;
void solve() {
  int n, m;
  cin >> n >> m;
  vi a(n);
  rep(i, n) cin >> a[i];
  sort(all(a));
  vi fac(m + 1), ifac(m + 1);
  fac[0] = ifac[0] = 1;
  rep(i, 1, m + 1) {
    fac[i] = 1ll * fac[i - 1] * i % P;
    ifac[i] = inv(fac[i]);
  }

  unordered_map<ull, int> lb;
  rep(i, 55) lb[1ull << i] = i;
  auto check = [&](ull state, int j, int rem) {
    while (true) {
      ull t = (state + 2) & (~state);
      if (t > state) {
        return true;
      }
      int i = lb[t];
      if (j == n) {
        return false;
      } else {
        rem -= a[j++] - i;
        if (rem < 0) {
          return false;
        }
      }
      state += t;
    }
  };
  vc<unordered_map<ull, int>> dp(m + 1);
  dp[0][0] = 1;
  rep(c, n) {
    int x = a[c];
    vc<unordered_map<ull, int>> ndp(m + 1);
    rep(i, m + 1) {
      for (int j = 0; i + j <= m; j++) {
        if (x - j > n || x - j <= 0) {
          continue;
        }
        ll val = 1uLL << x - j;
        for (auto [k, v] : dp[i]) {
          if (check(k | val, c + 1, m - i - j)) {
            md(ndp[i + j][k | val] += 1ll * v * ifac[j] % P);
          }
        }
      }
    }
    dp.swap(ndp);
  }
  int all = power(n, m);
  int ans = 0;
  rep(i, n + 2) md(ans += dp[m][(1LL << i) - 2]);
  cout << 1ll * fac[m] * ans % P * inv(all) % P << "\n";
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