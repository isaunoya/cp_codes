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

const int N = 1048576;
ll fac[N], ifac[N];
const int P = 1e9 + 7;
ll power(ll x, ll y) {
  ll r = 1;
  while (y) {
    if (y % 2) {
      r = r * x % P;
    }
    x = x * x % P;
    y /= 2;
  }
  return r;
}

ll inv(ll x) { return power(x, P - 2); }

ll C(int n, int m) { return fac[n] * ifac[m] % P * ifac[n - m] % P; }

void solve() {
  int n;
  cin >> n;
  int lst;
  cin >> lst;
  lst /= 2;
  ll ans = 1;
  rep(i, 1, n) {
    int x;
    cin >> x;
    x /= 2;
    if (lst >= x) {
      ans = 1ll * ans * C(lst, x) % P;
    } else {
      ans = 1ll * ans * C(x - 1, lst - 1) % P;
    }
    lst = x;
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  fac[0] = ifac[0] = 1;
  rep(i, 1, N) fac[i] = fac[i - 1] * i % P;
  rep(i, 1, N) ifac[i] = inv(fac[i]);

  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}