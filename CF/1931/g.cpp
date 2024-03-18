#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
#define rep1(a) for (auto i = 0; i < a; i++)
#define rep2(i, a) for (auto i = 0; i < a; i++)
#define rep3(i, a, b) for (auto i = a; i < b; i++)
#define rep4(i, a, b, c) for (auto i = a; i < b; i += c)
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

const int N = 4e6 + 5;
const int P = 998244353;
int fac[N], ifac[N];
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

int inv(int x) { return power(x, P - 2); }

int C(int x, int y) { 
  if (x < y) {
    return 0;
  }
  return 1ll * fac[x] * ifac[y] % P * ifac[x - y] % P;
}

void solve() {
  vi c(4);
  rep(4) cin >> c[i];

  if (abs(c[0] - c[1]) > 1) {
    cout << 0 << "\n";
    return;
  }

  if (c[0] == 0 && c[1] == 0) {
    if (!c[2] || !c[3]) {
      cout << 1 << "\n";
    } else {
      cout << 0 << "\n";
    }
    return;
  }

  ll res = 0;
  if (c[0] == c[1]) {
    res += 1ll * C(c[0] + c[2], c[2]) * C(c[1] + c[3] - 1, c[3]) % P;
    res += 1ll * C(c[1] + c[3], c[3]) * C(c[0] + c[2] - 1, c[2]) % P;
    cout << res % P << "\n"; 
  } else if (c[0] == c[1] + 1) {
    res = 1ll * C(c[1] + c[2], c[2]) * C(c[1] + c[3], c[3]) % P;
    cout << res << "\n";
  } else if (c[0] == c[1] - 1) {
    res = 1ll * C(c[0] + c[2], c[2]) * C(c[0] + c[3], c[3]) % P;
    cout << res << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  fac[0] = ifac[0] = 1;
  rep(i, 1, N) {
    fac[i] = 1ll * fac[i - 1] * i % P;
    ifac[i] = inv(fac[i]);
  }
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}