#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#ifndef LOCAL
#define debug(...) 42
#endif
#define rep(i, x, y) for (int i = x; i < y; i++)
#define rp(i, n) rep(i, 0, n)
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

const ll U = (1LL << 61) - 1;
void solve() {
  int n;
  cin >> n;
  vc<ll> a(n);
  rp(i, n) cin >> a[i];
  if (n == 1) {
    cout << 1 << "\n";
    return;
  }

  vc<ll> b(n + 1), l(n), r(n);
  b[0] = 0;
  rp(i, n) b[i + 1] = b[i] ^ a[i], l[i] = r[i] = 0;
  if (b[n] == 0)
    l[0] = r[n - 1] = U;
  else
    l[0] = r[n - 1] = 1LL << __lg(b[n]);
  for (int len = n - 1; len >= 1; len--) {
    for (int L = 0, R = len - 1; R < n; L += 1, R += 1) {
      ll val = b[R + 1] ^ b[L];
      bool ok = false;
      if (l[L] & val)
        ok = true;
      if (l[L] == U)
        ok = true;
      if (r[R] & val)
        ok = true;
      if (r[R] == U)
        ok = true;
      ll hb = __lg(val);
      if (ok) {
        if (val == 0) {
          l[L] = r[R] = U;
        } else {
          l[L] |= 1LL << hb;
          r[R] |= 1LL << hb;
        }
      }
      if (len == 1) {
        cout << (ok ? '1' : '0');
      }
    }
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