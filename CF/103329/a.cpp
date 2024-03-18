#include <bits/stdc++.h>
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

const int N = 5e7 + 5;
int isprime[N];

void pre() {
  for (int i = 2; i < N; i++)
    isprime[i] = 1;
  for (int i = 2; i < N; i++) {
    for (int j = i + i; j < N; j += i)
      isprime[j] = 0;
  }
}

// struct i {
//   bool operator[](const ll &x) {
//     return primeQ(x);
//   }
// } isprime;

void solve() {
  ll x;
  cin >> x;
  if (x >= 0 && isprime[x]) {
    cout << 1 << "\n";
    return;
  }
  if (x + x + 1 >= 0 && isprime[x + x + 1]) {
    cout << 2 << "\n";
    return;
  }
  if (x + x - 1 >= 0 && isprime[x + x - 1]) {
    cout << 2 << "\n";
    return;
  }
  if (x > 0) {
    ll ans = 2e9;
    for (ll r = x;; r++) {
      ll l = 2 - r; // l+r=2
      if (isprime[r - l + 1]) {
        ans = min(ans, r - l + 1);
        break;
      }
    }
    for (ll r = x;; r++) {
      ll l = 1 - r; // l+r=1
      if (isprime[(r - l + 1) / 2]) {
        ans = min(ans, r - l + 1);
        break;
      }
    }
    cout << ans << "\n";
    return;
  } else {
    ll ans = 2e9;
    for (ll l = x;; l--) {
      ll r = 2 - l; // l+r=2
      if (isprime[(r - l + 1)]) {
        ans = min(ans, r - l + 1);
        break;
      }
    }
    for (ll l = x;; l--) {
      ll r = 1 - l; // l+r=1
      if (isprime[(r - l + 1) / 2]) {
        ans = min(ans, r - l + 1);
        break;
      }
    }
    cout << ans << "\n";
    return;
  }

  assert(0);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  pre();

  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}