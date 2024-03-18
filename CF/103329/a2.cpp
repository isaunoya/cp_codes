#include <bits/stdc++.h>
#ifndef LOCAL
#define debug(...) 42
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif
using namespace std;
using ll = long long;
ll mul(ll u, ll v, ll p) {
  return (u * v - ll((long double)u * v / p) * p + p) % p;
}
ll bin(ll x, ll n, ll mod) {
  n %= (mod - 1);
  ll ret = 1;
  for (x %= mod; n; n /= 2, x = mul(x, x, mod)) {
    if (n % 2 == 1)
      ret = mul(ret, x, mod);
  }
  return ret;
}
bool checkQ(ll a, ll n) {
  if (n == 2 || a >= n)
    return 1;
  if (n == 1 || !(n & 1))
    return 0;
  ll d = n - 1;
  while (!(d & 1))
    d /= 2;
  ll t = bin(a, d, n);
  while (d != n - 1 && t != 1 && t != n - 1) {
    t = mul(t, t, n);
    d *= 2;
  }
  return t == n - 1 || d & 1;
}

bool primeQ(ll n) {
  static vector<ll> t = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  if (n <= 1)
    return false;
  for (ll k : t)
    if (!checkQ(k, n))
      return false;
  return true;
}
ll get(ll l, ll r) { return (l + r) * (r - l + 1) / 2; }
// (l+r)=1
// (l+r)=2
// (r-l+1)=1
// (r-l+1)=2

void solve() {
  ll x;
  cin >> x;
  if (primeQ(x)) {
    cout << 1 << "\n";
    return;
  }
  if (primeQ(x + x + 1)) {
    cout << 2 << "\n";
    return;
  }
  if (primeQ(x + x - 1)) {
    cout << 2 << "\n";
    return;
  }
  if (x > 0) {
    for (ll r = x;; r++) {
      ll l = 2 - r; // l+r=2
      if (primeQ(get(l, r))) {
        cout << r - l + 1 << "\n"; // 2*r-1
        return;
      }
      l = 1 - r; // l+r=1
      if (primeQ(get(l, r))) {
        cout << r - l + 1 << "\n"; // 2*r
        return;
      }
    }
  } else {
    for (ll l = x;; l--) {
      ll r = 1 - l; // l+r=1
      if (primeQ(get(l, r))) {
        cout << r - l + 1 << "\n"; // 2-2*l
        return;
      }
      r = 2 - l; // l+r=2
      if (primeQ(get(l, r))) {
        cout << r - l + 1 << "\n"; // 3-2*l
        return;
      }
    }
  }

  assert(0);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}