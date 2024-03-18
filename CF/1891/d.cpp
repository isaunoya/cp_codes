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
void solve() {

  auto solve = [&](ll l, ll r, ll x) {
    if (l > r) {
      return 0LL;
    }
    // debug(l, r, x);
    ll c = 0;
    __int128 p = 1;
    while (p * x <= l) {
      p = p * x;
      c += 1;
    }
    ll res = 0;
    for (ll i = l, j; i <= r; i = j + 1, p = p * x, c++) {
      // debug(i);
      ll L = i - 1, R = r + 1;
      while (R - L > 1) {
        // debug(L, R);
        ll M = (L + R) / 2;
        if (p <= M && M < p * x) {
          L = M;
        } else {
          R = M;
        }
      }
      j = L;
      // debug(i, j);
      res += 1ll * (j - i + 1) % P * c % P;
      if (res >= P) {
        res -= P;
      }
    }
    return res;
  };

  ll l, r;
  cin >> l >> r;
  ll ans = 0;
  for (int i = 0; i < 62; i++) {
    ll L = 1LL << i;
    ll R = 1LL << i + 1;
    --R;
    ans += solve(max(l, L), min(r, R), i);
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
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}